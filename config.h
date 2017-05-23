#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>

#define KEY_DB "db_connection"
#define KEY_DBDRIVER "driver"
#define KEY_DBNAME "database"
#define KEY_DBHOST "hostname"
#define KEY_DBUSER "username"
#define KEY_DBPWD "password"

class Config
{
public:
    Config();
    QString loadConfig(QString key);
    QString configPath();
    void writeConfig(QString key, QString val);
};

#endif // CONFIG_H
