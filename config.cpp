#include "config.h"

Config::Config()
{
    QSettings settings;
    if (!QFile(QSettings().fileName()).exists())
    {
        settings.beginGroup(KEY_DB);
        settings.setValue(KEY_DBDRIVER, "");
        settings.setValue(KEY_DBHOST, "");
        settings.setValue(KEY_DBNAME, "");
        settings.setValue(KEY_DBUSER, "");
        settings.setValue(KEY_DBPWD, "");
        settings.endGroup();
    }
}

QString Config::loadConfig(QString key)
{
    QSettings settings;
    settings.beginGroup(KEY_DB);
    QString configValue = settings.value(key).toString();
    settings.endGroup();
    return configValue;
}

QString Config::configPath()
{
    QSettings settings;
    QFileInfo file(settings.fileName());
    QString path = file.absolutePath();
    return path;
}

void Config::writeConfig(QString key, QString val)
{
    QSettings settings;
    settings.beginGroup(KEY_DB);
    settings.setValue(key,val);
    settings.endGroup();
}



