#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>

#include <config.h>

static bool createConnection()
{
    {
        //Read qsettings file for DB connection
        Config conf;
        QString driver = conf.loadConfig(KEY_DRIVER);
        QString host = conf.loadConfig(KEY_HOST);
        QString dbs = conf.loadConfig(KEY_DB);
        QString user = conf.loadConfig(KEY_USER);
        QString pass = conf.loadConfig(KEY_PWD);

        QSqlDatabase db = QSqlDatabase::addDatabase(driver, "mainConnection");
        db.setHostName(host);
        db.setDatabaseName(dbs);
        db.setUserName(user);
        db.setPassword(pass);
        if (!db.open()) {
            QMessageBox::critical(0, qApp->tr("Cannot open database"),
                                  qApp->tr("Unable to establish a database"
                                           "connection.\n"
                                           "Click Ok to start config Wizard."),
                                  QMessageBox::Ok);
            return false;
        }
        db.close();
    }
    QSqlDatabase::removeDatabase("mainConnection");
    return true;
}

#endif // CONNECTION_H
