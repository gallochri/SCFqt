#include "config.h"

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

void Config::writeConfig(QString key, QString val)
{
    QSettings settings;
    settings.beginGroup(KEY);
    settings.setValue(key,val);
    settings.endGroup();
}



