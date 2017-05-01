#ifndef DATALISTINI_H
#define DATALISTINI_H

#include <QSqlTableModel>

class DataListini : public QSqlTableModel
{
    Q_OBJECT
public:
    DataListini(QObject *parent, QSqlDatabase);
private:
    void setupModel();
};

#endif // DATALISTINI_H
