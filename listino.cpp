#include "listino.h"
#include "mainwindow.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

Listino::Listino(QObject *parent): QSqlQueryModel(parent)
{
    setupModel();
}

void Listino::setupModel(){
    QSqlDatabase db = QSqlDatabase::database("viewConnection");
    QSqlQuery query(db);
    query.prepare("SELECT CONCAT(sigla_marchio,codice_prodotto) AS Codice,"
                  "descrizione_prodotto AS Descrizione,"
                  "pz_rivenditore/moltiplicatore/100 AS 'Prezzo Riv',"
                  "pz_pubblico/moltiplicatore/100 AS 'Prezzo Pub',"
                  "unita_misura AS UM,"
                  "moltiplicatore AS Moltiplicatore,"
                  "qta_cartone AS Cartone "
                  "FROM listino_prezzi "
                  "ORDER BY sigla_marchio ASC "
                  "LIMIT 20");

    if (query.exec()){
        qDebug() << __func__ << ":Query ok!";
    } else {
        qDebug() << __func__ << query.lastError();
        qDebug() << __func__ << "test last query:"<< query.lastQuery();
    }
    setQuery(query);
}
