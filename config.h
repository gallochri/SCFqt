#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QFile>

class Config
{
public:
    Config();
    QString loadConfig(QString key);
    void writeConfig(QString key, QString val);
};

#endif // CONFIG_H
