#include "mainwindow.h"
#include "dbwizard.h"

#include <QApplication>
#include <QSettings>
#include <QSqlDatabase>
#include <QDebug>
#include <QDialog>
#include <QDesktopWidget>

#define KEY "db_connection"
#define KEY_HOST "hostname"
#define KEY_DB "database"
#define KEY_USER "username"
#define KEY_PWD "password"

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
    QSettings settings;
    settings.beginGroup(KEY);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(settings.value(KEY_HOST).toString());
    db.setDatabaseName(settings.value(KEY_DB).toString());
    db.setUserName(settings.value(KEY_USER).toString());
    db.setPassword(settings.value(KEY_PWD).toString());
    settings.endGroup();

    // TODO write down a testing config file
    settings.beginGroup(KEY);
    settings.setValue(KEY_HOST, "freebsdserver2");
    settings.setValue(KEY_DB, "testdb");
    settings.setValue(KEY_USER, "gallochri");
    settings.setValue(KEY_PWD, "password");
    settings.endGroup();

    //Test DB connection
    if (!db.open()){
        qDebug() << "Problem with DB connection";

        //Start DB config wizard
        DbWizard *wizard = new DbWizard(mainWin);
        //Center the wizard dialog
        QSize mSize = wizard->sizeHint();
        const QRect screenRect = QApplication::desktop()->screenGeometry();
        wizard->move(QPoint(screenRect.width()/3 - mSize.width()/2,
                              screenRect.height()/2 - mSize.height()/2 ) );
        wizard->show();
    }
    db.close();
    return app.exec();
}
