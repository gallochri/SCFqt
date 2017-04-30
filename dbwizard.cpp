#include <QtWidgets>
#include <QBoxLayout>
#include <QSettings>
#include <QDebug>

#include "dbwizard.h"
#include "config.h"

DbWizard::DbWizard(QWidget *parent) : QWizard(parent)
{
    addPage(new IntroPage);
    addPage(new DbConfigPage);
    addPage(new ConclusionPage);

    setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png"));
    setPixmap(QWizard::BackgroundPixmap, QPixmap(":/images/background.png"));

    setWindowTitle(QString(APP_NAME).replace("_"," "));
}

void DbWizard::accept(){
    Config conf;

    QString host = field("hostname").toString();
    QString db = field("database").toString();
    QString user = field("username").toString();
    QString pass = field("password").toString();
//  qDebug() << __func__ << host << db << user << pass;

    conf.writeConfig(KEY_HOST,host);
    conf.writeConfig(KEY_DB,db);
    conf.writeConfig(KEY_USER,user);
    conf.writeConfig(KEY_PWD,pass);
    QDialog::accept();
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
    QString host = conf.loadConfig(KEY_HOST);
    QString dbs = conf.loadConfig(KEY_DB);
    QString user = conf.loadConfig(KEY_USER);
    QString pass = conf.loadConfig(KEY_PWD);

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

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(hostnameLabel, 0,0);
    layout->addWidget(hostnameLineEdit,0,1);
    layout->addWidget(databaseLabel,1,0);
    layout->addWidget(databaseLineEdit,1,1);
    layout->addWidget(usernameLabel,2,0);
    layout->addWidget(usernameLineEdit,2,1);
    layout->addWidget(passwordLabel,3,0);
    layout->addWidget(passwordLineEdit,3,1);
    layout->addWidget(showPassCheck,3,2);
    setLayout(layout);

    registerField("hostname", hostnameLineEdit);
    registerField("database", databaseLineEdit);
    registerField("username", usernameLineEdit);
    registerField("password", passwordLineEdit);

    connect(showPassCheck,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(on_showPassCheck_stateChanged())
            );
}

void DbConfigPage::on_showPassCheck_stateChanged(){
    passwordLineEdit->setEchoMode(showPassCheck->checkState() == Qt::Checked ?
                                      QLineEdit::Normal : QLineEdit::Password );
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
