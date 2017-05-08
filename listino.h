#ifndef LISTINO_H
#define LISTINO_H

#include <QSqlQueryModel>

class Listino : public QSqlQueryModel
{
    Q_OBJECT
public:
    Listino(QObject *parent);
private:
    void setupModel();
};

#endif // LISTINO_H
