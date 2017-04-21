#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qApp->setApplicationVersion(APP_VERSION);
    qApp->setApplicationName(QString(APP_NAME).replace("_"," "));
    qApp->setOrganizationName("gallochri.com");
    qApp->setOrganizationDomain("www.gallochri.com");

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("freebsdserver");
    db.setDatabaseName("metel");
    db.setUserName("metel");
    db.setPassword("metel");

    if (db.open()){
        qDebug() << "DB connection successfull";
        db.close();
        MainWindow *mainWin = new MainWindow;
        mainWin->setWindowTitle (QString(APP_NAME).replace("_"," "));
        mainWin->show();
    } else {
        qDebug() << "Problem with DB connection";
    }
    return app.exec();
}
