#include "dbwizard.h"

DbWizard::DbWizard(QWidget *parent) : QWizard(parent)
{
    addPage(new IntroPage);
    addPage(new DbInfoPage);
    addPage(new ConclusionPage);

    setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.jpg"));

    setWindowTitle(QString(APP_NAME).replace("_"," "));

}

void DbWizard::accept(){
    QByteArray hostname = field("hostName").toByteArray();
    QByteArray database = field("database").toByteArray();
    QByteArray username = field("username").toByteArray();
    QByteArray password = field("password").toByteArray();
}
