#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QFile>

#define KEY "db_connection"
#define KEY_DRIVER "driver"
#define KEY_DB "database"
#define KEY_HOST "hostname"
#define KEY_USER "username"
#define KEY_PWD "password"

class Config
{
public:
    Config();
    QString loadConfig(QString key);
    void writeConfig(QString key, QString val);
};

#endif // CONFIG_H
