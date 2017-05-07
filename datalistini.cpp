#include "datalistini.h"

DataListini::DataListini(QObject *parent, QSqlDatabase db)
    :QSqlTableModel(parent, db)
{
    setupModel();
}

void DataListini::setupModel(){
    setTable("listino_prezzi");
    setHeaderData(0,Qt::Horizontal, tr("Marca"));
    setHeaderData(1,Qt::Horizontal, tr("Codice"));
    setHeaderData(2,Qt::Horizontal, tr("Codice EAN"));
    setHeaderData(3,Qt::Horizontal, tr("Descrizione"));
    setHeaderData(4,Qt::Horizontal, tr("Cartone"));
    setHeaderData(5,Qt::Horizontal, tr("Multi Ordine"));
    setHeaderData(6,Qt::Horizontal, tr("Min Ordine"));
    setHeaderData(7,Qt::Horizontal, tr("Max Ordine"));
    setHeaderData(8,Qt::Horizontal, tr("Lead Time"));
    setHeaderData(9,Qt::Horizontal, tr("Prezzo Rivenditore"));
    setHeaderData(10,Qt::Horizontal, tr("Prezzo Pubblico"));
    setHeaderData(11,Qt::Horizontal, tr("Moltiplicatore"));
    setHeaderData(12,Qt::Horizontal, tr("Valuta"));
    setHeaderData(13,Qt::Horizontal, tr("Unità di Misura"));
    setHeaderData(14,Qt::Horizontal, tr("Prodotto Composto"));
    setHeaderData(15,Qt::Horizontal, tr("Stato del Prodotto"));
    setHeaderData(16,Qt::Horizontal, tr("Data Variazione"));
    setHeaderData(17,Qt::Horizontal, tr("Famiglia Sconto"));
    setHeaderData(18,Qt::Horizontal, tr("Famiglia Statistica"));
//    setSort(3,Qt::AscendingOrder);
    select();
}
