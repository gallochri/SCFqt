#include "dbwizard.h"
#include <QtWidgets>
#include <QBoxLayout>
#include <QSettings>
#include <QDebug>

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
    QByteArray hostname = field("hostname").toString();
    QByteArray database = field("database").toByteArray();
    QByteArray username = field("username").toByteArray();
    QByteArray password = field("password").toByteArray();
//    qDebug() << __func__ << hostname << database << username << password;
    //TODO code for store in settings file
    QSettings *settings;
    settings->beginGroup(KEY);
    settings->setValue(hostname, hostname);
    QDialog::accept();
}

IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    label = new QLabel(tr("It seems that the database configuration does not exist"
                          " or is incorrect. "
                          "Fill in the fields on the next tab to retry the connection"
                          " to the database."));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

DbConfigPage::DbConfigPage(QWidget *parent):QWizardPage(parent){
    setTitle(tr("Database configuration"));
    setSubTitle(tr("Specify information on how to connect to db"));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));

    hostnameLabel = new QLabel(tr("&Hostname:"));
    hostnameLineEdit = new QLineEdit;
    hostnameLabel->setBuddy(hostnameLineEdit);
    hostnameLineEdit->setPlaceholderText("www.example.com or 192.168.10.1");

    databaseLabel = new QLabel(tr("&Database:"));
    databaseLineEdit = new QLineEdit;
    databaseLabel->setBuddy(databaseLabel);
    databaseLineEdit->setPlaceholderText("MyDB");

    usernameLabel = new QLabel(tr("&User name:"));
    usernameLineEdit = new QLineEdit;
    usernameLabel->setBuddy(usernameLabel);

    passwordLabel = new QLabel(tr("&Password:"));
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);
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
    setLayout(layout);

    registerField("hostname", hostnameLineEdit);
    registerField("database", databaseLineEdit);
    registerField("username", usernameLineEdit);
    registerField("password", passwordLineEdit);

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
    label->setText(tr("Click %1 to generate the class skeleton.")
                   .arg(finishText));
}

