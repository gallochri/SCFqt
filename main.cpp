#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("freebsdserver");
    db.setDatabaseName("metel");
    db.setUserName("metel");
    db.setPassword("metel");

    if (db.open()){
        qDebug() << "DB connection successfull";
        db.close();
        MainWindow *mainWin = new MainWindow;
        mainWin->setWindowTitle (QObject::tr("SCF QT"));
        mainWin->show();
    } else {
        qDebug() << "Problem with DB connection";
    }
    return app.exec();
}
