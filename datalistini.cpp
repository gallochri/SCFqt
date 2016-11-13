#include "datalistini.h"

DataListini::DataListini(QObject *parent):QSqlTableModel(parent)
{
    setupModel();
}

void DataListini::setupModel(){
    setTable("Listini");
    setSort(0,Qt::AscendingOrder);
    setHeaderData(0,Qt::Horizontal, trUtf8("Codice"));
    setHeaderData(1,Qt::Horizontal, trUtf8("Descrizione"));
    setHeaderData(2,Qt::Horizontal, trUtf8("Prezzo"));
    setHeaderData(3,Qt::Horizontal, trUtf8("Unità di misura"));
    setHeaderData(4,Qt::Horizontal, trUtf8("Codice EAN"));
    setHeaderData(5,Qt::Horizontal, trUtf8("Multi"));
    setHeaderData(6,Qt::Horizontal, trUtf8("Data"));
    setHeaderData(7,Qt::Horizontal, trUtf8("Famiglia Sconto"));
    setHeaderData(8,Qt::Horizontal, trUtf8("Famiglia Statistica"));
    select();

}
