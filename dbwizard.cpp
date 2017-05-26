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
    switch (selDriver) {
    case 0:
    {
        conf.writeConfig(KEY_DBDRIVER,"QMYSQL");
        conf.writeConfig(KEY_DBNAME,db);
        conf.writeConfig(KEY_DBHOST,host);
        conf.writeConfig(KEY_DBUSER,user);
        conf.writeConfig(KEY_DBPWD,pass);
        break;
    }
    case 1:
    {
        conf.writeConfig(KEY_DBDRIVER,"QSQLITE");
        conf.writeConfig(KEY_DBNAME,db);
        conf.writeConfig(KEY_DBHOST,"");
        conf.writeConfig(KEY_DBUSER,"");
        conf.writeConfig(KEY_DBPWD,"");
        break;
    }
    default:
        break;
    }
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
    QString driver = conf.loadConfig(KEY_DBDRIVER);
    QString host = conf.loadConfig(KEY_DBHOST);
    QString dbs = conf.loadConfig(KEY_DBNAME);
    QString user = conf.loadConfig(KEY_DBUSER);
    QString pass = conf.loadConfig(KEY_DBPWD);

    driverLabel = new QLabel(tr("Database driver:"));
    driverComboBox = new QComboBox;
    QStringList drivers;
    drivers << "QMYSQL" << "QSQLITE";
    int driverIndex = drivers.indexOf(driver);
    driverComboBox->addItems(drivers);
    driverComboBox->setCurrentIndex(driverIndex);
    driverLabel->setBuddy(driverComboBox);
    if (driver.isEmpty())
    {
        driverComboBox->setCurrentIndex(1);
    }

    hostnameLabel = new QLabel(tr("&Hostname:"));
    hostnameLineEdit = new QLineEdit;
    hostnameLabel->setBuddy(hostnameLineEdit);
    if (host.isEmpty())
    {
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
    setField("driver",driverIndex);
    registerField("hostname", hostnameLineEdit);
    registerField("database", databaseLineEdit);
    registerField("username", usernameLineEdit);
    registerField("password", passwordLineEdit);

    on_driverComboBox_currentIndexChanged();

    connect(driverComboBox,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(on_driverComboBox_currentIndexChanged()));

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
        Config conf;
        QString driver = driverComboBox->currentText();
        QString database = field("database").toString();
        database = conf.configPath()+"/"+database;
        QSqlDatabase db = QSqlDatabase::addDatabase(driver,"testConnection");
        db.setHostName(field("hostname").toString());
        db.setDatabaseName(database);
        db.setUserName(field("username").toString());
        db.setPassword(field("password").toString());

        //Test connection to DB with edited fields
        if (!db.open() || database.isEmpty()){
            qDebug() << __func__ << ":Connection problem!";
            testConnection->setStyleSheet(
                        "QPushButton { background-color : red;}");
            connectionStatusLabel->setText("<b>Connection problem!</b>");
        } else {
            testConnection->setStyleSheet(
                        "QPushButton { background-color : green;}");
            connectionStatusLabel->setText("<b>Connection successfull!</b>");
            if (driverComboBox->currentIndex() == 1){
                Config conf;
                QString dbFilePath = conf.configPath() + "/" + database;
                QFileInfo dbFile(dbFilePath);
                if (!dbFile.isFile()){
                    QFile *dbFile = new QFile(dbFilePath);
                    dbFile->open(QIODevice::ReadWrite | QIODevice::Text);
                    dbFile->close();
                }
            }
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
        Config conf;
        QString driver = driverComboBox->currentText();
        QString database = field("database").toString();
        database = conf.configPath()+"/"+database;
        qDebug() << __func__ << database;
        QSqlDatabase db = QSqlDatabase::addDatabase(driver,"buildConnection");
        db.setHostName(field("hostname").toString());
        db.setDatabaseName(database);
        db.setUserName(field("username").toString());
        db.setPassword(field("password").toString());
        if (db.open()){
            qDebug() << __func__ << ":db_opened";
            //TODO code for SQLite DB
            QSqlQuery *query = new QSqlQuery(db);

            if (driverComboBox->currentIndex() == 1)
            {
                qDebug() << __func__ << ":Executing queries";
                query->prepare("create table listino_prezzi("
                               "sigla_marchio varchar(3) not null,"
                               "codice_prodotto varchar(16) not null,"
                               "codice_EAN varchar(13) not null,"
                               "descrizione_prodotto varchar(43) not null,"
                               "qta_cartone int(5) not null,"
                               "qta_multipla_ordinazione int(5) not null,"
                               "qta_minima_ordinazione int(5) not null,"
                               "qta_massima_ordinazione int(6) not null,"
                               "lead_time varchar(1) not null,"
                               "pz_rivenditore float not null,"
                               "pz_pubblico float not null,"
                               "moltiplicatore int(6) not null,"
                               "codice_valuta varchar(3) not null,"
                               "unita_misura varchar(3) not null,"
                               "prodotto_composto varchar(1) not null,"
                               "stato_del_prodotto varchar(1) not null,"
                               "data_variazione date not null,"
                               "famiglia_sconto varchar(18) not null,"
                               "famiglia_statistica varchar(18) not null,"
                               "constraint sigla_marchio"
                               "unique (sigla_marchio, codice_prodotto));");
                query->exec();
                query->prepare("create table testata_listino("
                               "id_tracciato char(20) not null,"
                               "sigla_azienda char(3) not null,"
                               "partita_iva char(11) not null,"
                               "numero char(6) not null,"
                               "decorrenza date not null,"
                               "data_variazione date not null,"
                               "descrizione char(30) not null,"
                               "filler char(39) not null,"
                               "versione_tracciato char(3) not null,"
                               "data_decorrenza_gr char(8) not null,"
                               "isopartita char(16) not null,"
                               "filler2 char(81) not null,"
                               "constraint sigla_azienda"
                               "unique (sigla_azienda, numero));");
                query->exec();
            } else {
                QFile *file = new QFile(":/sql/create_tables_"+driver+".sql");
                DbConfigPage::executeQueriesFromFile(file,query);
            }
        }
        //Close DB and destroy connection
        db.close();
    }
    QSqlDatabase::removeDatabase("buildConnection");
    //Repeat DB connection and tables tests
    DbConfigPage::on_testConnection_pressed();
}

void DbConfigPage::on_driverComboBox_currentIndexChanged()
{
    if (driverComboBox->currentIndex() == 1)
    {
        hostnameLineEdit->setDisabled(1);
        usernameLineEdit->setDisabled(1);
        passwordLineEdit->setDisabled(1);
        showPassCheck->setDisabled(1);
    } else {
        hostnameLineEdit->setEnabled(1);
        usernameLineEdit->setEnabled(1);
        passwordLineEdit->setEnabled(1);
        showPassCheck->setEnabled(1);
    }
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
//            qDebug() << QSqlDatabase::drivers();
            qDebug() << __func__ <<  ":last Error:" << query->lastError();
//            qDebug() << __func__ << ":test executed query:"<< query->executedQuery();
            qDebug() << __func__ << ":test last query:"<< query->lastQuery();
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
