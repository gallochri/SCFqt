#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QDialog>
#include <QDesktopWidget>
#include <QtSql>
#include <QtWidgets>

#include "mainwindow.h"
#include "dbwizard.h"
#include "connection.h"

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

    //Test DB connection
    if (!createConnection()){
        qDebug() << __func__ << ":Connection problem!";
        //Start DB config wizard
        mainWin->startWizard(mainWin);
    } else {
        qDebug() << __func__ <<":Connection successfull!";
    }
    return app.exec();
}
