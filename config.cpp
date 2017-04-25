#include "config.h"

#define KEY "db_connection"
#define KEY_HOST "hostname"
#define KEY_DB "database"
#define KEY_USER "username"
#define KEY_PWD "password"

Config::Config()
{
    QSettings settings;
    if (!QFile(QSettings().fileName()).exists()){
        settings.beginGroup(KEY);
        settings.setValue(KEY_HOST, "");
        settings.setValue(KEY_DB, "");
        settings.setValue(KEY_USER, "");
        settings.setValue(KEY_PWD, "");
        settings.endGroup();
    }
}

QString Config::loadConfig(QString key)
{
    QSettings settings;
    settings.beginGroup(KEY);

    QString configValue = settings.value(key).toString();
    settings.endGroup();
    return configValue;
}



