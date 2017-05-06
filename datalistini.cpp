#include "datalistini.h"

DataListini::DataListini(QObject *parent, QSqlDatabase db)
    :QSqlTableModel(parent, db)
{
    setupModel();
}

void DataListini::setupModel(){
    setTable("testata_listino");
    setSort(0,Qt::AscendingOrder);
    setHeaderData(0,Qt::Horizontal, tr("Codice"));
    setHeaderData(1,Qt::Horizontal, tr("Descrizione"));
    setHeaderData(2,Qt::Horizontal, tr("Prezzo"));
    setHeaderData(3,Qt::Horizontal, tr("Unità di misura"));
    setHeaderData(4,Qt::Horizontal, tr("Codice EAN"));
    setHeaderData(5,Qt::Horizontal, tr("Multi"));
    setHeaderData(6,Qt::Horizontal, tr("Data"));
    setHeaderData(7,Qt::Horizontal, tr("Famiglia Sconto"));
    setHeaderData(8,Qt::Horizontal, tr("Famiglia Statistica"));
    select();

}
