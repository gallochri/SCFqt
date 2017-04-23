#include "dbwizard.h"

#include <QBoxLayout>

DbWizard::DbWizard(QWidget *parent) : QWizard(parent)
{
    addPage(new IntroPage);
//    addPage(new DbInfoPage);
//    addPage(new ConclusionPage);

    setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.jpg"));

    setWindowTitle(QString(APP_NAME).replace("_"," "));
}

void DbWizard::accept(){
//    QByteArray hostname = field("hostName").toByteArray();
//    QByteArray database = field("database").toByteArray();
//    QByteArray username = field("username").toByteArray();
//    QByteArray password = field("password").toByteArray();
    //TODO code for store in settings file
    QDialog::accept();
}

IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.jpg"));

    label = new QLabel(tr("This wizard will generate a skeleton C++ class "
                          "definition, including a few functions. You simply "
                          "need to specify the class name and set a few "
                          "options to produce a header file and an "
                          "implementation file for your new C++ class."));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

