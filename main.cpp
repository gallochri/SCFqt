#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QDialog>
#include <QDesktopWidget>

#include "mainwindow.h"
#include "dbwizard.h"
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qApp->setApplicationVersion(APP_VERSION);
    qApp->setApplicationName(QString(APP_NAME).replace("_"," "));
    qApp->setOrganizationName("gallochri.com");
    qApp->setOrganizationDomain("www.gallochri.com");

    MainWindow *mainWin = new MainWindow;
    mainWin->setWindowTitle (QString(APP_NAME).replace("_"," "));
    mainWin->show();

    //Read qsettings file for DB connection
    Config conf;
    QString host = conf.loadConfig(KEY_HOST);
    QString dbs = conf.loadConfig(KEY_DB);
    QString user = conf.loadConfig(KEY_USER);
    QString pass = conf.loadConfig(KEY_PWD);

    {//Set DB connection
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "mainDB");
        db.setHostName(host);
        db.setDatabaseName(dbs);
        db.setUserName(user);
        db.setPassword(pass);

        //Test DB connection
        if (!db.open()){
            qDebug() << __func__ << ":Connection problem!";
            //Start DB config wizard
            mainWin->startWizard(mainWin);
        } else {
            qDebug() << __func__ <<":Connection successfull!";
        }
    }
    QSqlDatabase::removeDatabase("mainDB");
    return app.exec();
}
