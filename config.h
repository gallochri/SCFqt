#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QFile>

class Config
{
public:
    Config();
    QString loadConfig(QString key);
};

#endif // CONFIG_H
