#include <QtWidgets>
#include <QBoxLayout>
#include <QSettings>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>

#include "mainwindow.h"
#include "dbwizard.h"
#include "config.h"

DbWizard::DbWizard(QWidget *parent) : QWizard(parent)
{
    addPage(new IntroPage);
    addPage(new DbConfigPage);
    addPage(new ConclusionPage);

    setWindowTitle(QString(APP_NAME).replace("_"," "));
}

void DbWizard::accept(){
    Config conf;
    int selDriver = field("driver").toInt();
    QString host = field("hostname").toString();
    QString db = field("database").toString();
    QString user = field("username").toString();
    QString pass = field("password").toString();
    //  qDebug() << __func__ << host << db << user << pass;
    switch (selDriver) {
    case 1:
        conf.writeConfig(KEY_DRIVER,"QMYSQL");
        break;
    case 2:
        conf.writeConfig(KEY_DRIVER,"QSQLITE");
    default:
        break;
    }

    conf.writeConfig(KEY_HOST,host);
    conf.writeConfig(KEY_DB,db);
    conf.writeConfig(KEY_USER,user);
    conf.writeConfig(KEY_PWD,pass);
    QDialog::accept();
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    label = new QLabel(tr("It seems that the configuration does not work "
                          " or is incorrect. "
                          "Fill in the fields on the next wizard page"
                          " and try the connection to the database."));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

DbConfigPage::DbConfigPage(QWidget *parent):QWizardPage(parent){
    setTitle(tr("Database configuration"));
    setSubTitle(tr("Specify information on how to connect to db"));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));

    //Read qsettings file for DB connection
    Config conf;
    QString driver = conf.loadConfig(KEY_DRIVER);
    QString host = conf.loadConfig(KEY_HOST);
    QString dbs = conf.loadConfig(KEY_DB);
    QString user = conf.loadConfig(KEY_USER);
    QString pass = conf.loadConfig(KEY_PWD);

    driverLabel = new QLabel(tr("Database driver:"));
    driverComboBox = new QComboBox;
    QStringList drivers;
    drivers << driver << "QMYSQL" << "QSQLITE";
    driverComboBox->addItems(drivers);
    driverLabel->setBuddy(driverComboBox);
    if (driver.isEmpty())
    {
        driverComboBox->setCurrentIndex(1);
    }

    hostnameLabel = new QLabel(tr("&Hostname:"));
    hostnameLineEdit = new QLineEdit;
    hostnameLabel->setBuddy(hostnameLineEdit);
    if (host.isEmpty()){
        hostnameLineEdit->setPlaceholderText("www.example.com or 192.168.10.1");
    }
    hostnameLineEdit->setText(host);

    databaseLabel = new QLabel(tr("&Database:"));
    databaseLineEdit = new QLineEdit;
    databaseLabel->setBuddy(databaseLabel);
    if (dbs.isEmpty()){
        databaseLineEdit->setPlaceholderText("MyDB");
    }
    databaseLineEdit->setText(dbs);

    usernameLabel = new QLabel(tr("&User name:"));
    usernameLineEdit = new QLineEdit;
    if (!user.isEmpty()){
        usernameLineEdit->setText(user);
    }
    usernameLabel->setBuddy(usernameLabel);

    passwordLabel = new QLabel(tr("&Password:"));
    passwordLineEdit = new QLineEdit;
    showPassCheck = new QCheckBox("&Show password");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    if (!pass.isEmpty()){
        passwordLineEdit->setText(pass);
    }
    passwordLabel->setBuddy(passwordLabel);

    QString connStatus = "Connection status";
    connectionStatusLabel = new QLabel(connStatus);
    testConnection = new QPushButton(tr("&Test"));

    QString dbStatus = "DB status";
    dbStatusLabel = new QLabel(dbStatus);
    createDB = new QPushButton(tr("&Create DB"));
    createDB->setDisabled(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(driverLabel,0,0);
    layout->addWidget(driverComboBox,0,1);
    layout->addWidget(hostnameLabel, 1,0);
    layout->addWidget(hostnameLineEdit,1,1);
    layout->addWidget(databaseLabel,2,0);
    layout->addWidget(databaseLineEdit,2,1);
    layout->addWidget(usernameLabel,3,0);
    layout->addWidget(usernameLineEdit,3,1);
    layout->addWidget(passwordLabel,4,0);
    layout->addWidget(passwordLineEdit,4,1);
    layout->addWidget(showPassCheck,4,2);
    layout->addWidget(connectionStatusLabel,5,1);
    layout->addWidget(testConnection,5,2);
    layout->addWidget(dbStatusLabel,6,1);
    layout->addWidget(createDB,6,2);
    setLayout(layout);

    registerField("driver",driverComboBox);
    registerField("hostname", hostnameLineEdit);
    registerField("database", databaseLineEdit);
    registerField("username", usernameLineEdit);
    registerField("password", passwordLineEdit);

    connect(showPassCheck,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(on_showPassCheck_stateChanged()));

    connect(testConnection,
            SIGNAL(pressed()),
            this,
            SLOT(on_testConnection_pressed()));

    connect(createDB,
            SIGNAL(pressed()),
            this,
            SLOT(on_createDB_pressed()));
}

void DbConfigPage::on_showPassCheck_stateChanged(){
    passwordLineEdit->setEchoMode(showPassCheck->checkState() == Qt::Checked ?
                                      QLineEdit::Normal : QLineEdit::Password );
}

void DbConfigPage::on_testConnection_pressed()
{
    {//Create test connection with edited fields
        QString driver = driverComboBox->currentText();
        QSqlDatabase db = QSqlDatabase::addDatabase(driver,"testConnection");
        db.setHostName(field("hostname").toString());
        db.setDatabaseName(field("database").toString());
        db.setUserName(field("username").toString());
        db.setPassword(field("password").toString());

        //Test connection to DB with edited fields
        if (!db.open()){
            qDebug() << __func__ << ":Connection problem!";
            testConnection->setStyleSheet(
                        "QPushButton { background-color : red;}");
            connectionStatusLabel->setText("<b>Connection problem!</b>");
        } else {
            testConnection->setStyleSheet(
                        "QPushButton { background-color : green;}");
            connectionStatusLabel->setText("<b>Connection successfull!</b>");
            //Connection to DB ok, now test DB tables
            //TODO add more tables tests
            if (db.tables().contains("testata_listino")){
                createDB->setStyleSheet(
                            "QPushButton { background-color : green;}");
                dbStatusLabel->setText("<b>DB tables OK!</b>");
            } else {
                createDB->setStyleSheet(
                            "QPushButton { background-color : red;}");
                dbStatusLabel->setText("<b>Tables not present!</b>");
                createDB->setDisabled(false);
            }
        }
        //Close DB and destroy connection
        db.close();
    }
    QSqlDatabase::removeDatabase("testConnection");
}

void DbConfigPage::on_createDB_pressed()
{
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","buildConnection");
        db.setHostName(field("hostname").toString());
        db.setDatabaseName(field("database").toString());
        db.setUserName(field("username").toString());
        db.setPassword(field("password").toString());
        if (db.open()){
            qDebug() << __func__ << ":db_opened";
            QSqlQuery *query = new QSqlQuery(db);
            QFile *file = new QFile(":/sql/create_tables.sql");
            DbConfigPage::executeQueriesFromFile(file,query);
        }
        //Close DB and destroy connection
        db.close();
    }
    QSqlDatabase::removeDatabase("testConnection");
    //Repeat DB connection and tables tests
    DbConfigPage::on_testConnection_pressed();
}

void DbConfigPage::executeQueriesFromFile(QFile *file, QSqlQuery *query)
{
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << __func__ << ":problem with file";
    }
    while (!file->atEnd()){
        QByteArray readLine="";
        QString cleanedLine;
        QString line="";
        bool finished=false;
        while(!finished){
            readLine = file->readLine();
            cleanedLine=readLine.trimmed();
            // remove comments at end of line
            QStringList strings=cleanedLine.split("--");
            cleanedLine=strings.at(0);

            // remove lines with only comment, and DROP lines
            if(!cleanedLine.startsWith("--")
                    && !cleanedLine.startsWith("DROP")
                    && !cleanedLine.isEmpty()){
                line+=cleanedLine;
            }
            if(cleanedLine.endsWith(";")){
                break;
            }
            if(cleanedLine.startsWith("COMMIT")){
                finished=true;
            }
        }

        if(!line.isEmpty()){
            query->exec(line);
        }
        if(!query->isActive()){
            qDebug() << QSqlDatabase::drivers();
            qDebug() <<  query->lastError();
            qDebug() << "test executed query:"<< query->executedQuery();
            qDebug() << "test last query:"<< query->lastQuery();
        }
    }
}

ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Conclusion"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    label = new QLabel;
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

void ConclusionPage::initializePage()
{
    QString finishText = wizard()->buttonText(QWizard::FinishButton);
    finishText.remove('&');
    label->setText(tr("Setup wizard is terminated. Click %1 to start"
                      " using your connection configuration.")
                   .arg(finishText));
}
