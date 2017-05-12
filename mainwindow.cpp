#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QSqlError>
#include <QDate>

#include "mainwindow.h"
#include "dbwizard.h"
#include "ui_mainwindow.h"
#include "config.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startWizard(MainWindow *mainWin)
{
    DbWizard *wizard = new DbWizard(mainWin);
    wizard->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QString title = qApp->applicationName();
    int res;
    res = QMessageBox::question(this, title, tr("Would you like to close?"),
                                QMessageBox::Ok,
                                QMessageBox::Cancel);
    if (res == QMessageBox::Cancel){
        event->ignore();
        return;
    }
    event->accept();
}

void MainWindow::on_action_About_triggered()
{
    QString title = "About" + qApp->applicationName();
    QString msg = QString("<h1>%1</h1>").arg(qApp->applicationName());
    msg += QString(tr("<p><b>Version:</b> %1</p>"))
            .arg(qApp->applicationVersion());
    msg += QString(tr("<p><b>Qt Version:</b> %1</p>")).arg(QT_VERSION_STR);
    QMessageBox::about(this, title, msg);
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_action_Wizard_triggered()
{
    startWizard(this);
}

QSqlDatabase MainWindow::viewConnection()
{
    Config conf;
    QString host = conf.loadConfig(KEY_HOST);
    QString dbs = conf.loadConfig(KEY_DB);
    QString user = conf.loadConfig(KEY_USER);
    QString pass = conf.loadConfig(KEY_PWD);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "viewConnection");
    db.setHostName(host);
    db.setDatabaseName(dbs);
    db.setUserName(user);
    db.setPassword(pass);
    db.open();
    return db;
}

void MainWindow::setupView()
{
    QSqlDatabase db = viewConnection();
    //    DataListini *listino = new DataListini(this,db);
    Listino *listino = new Listino(this);
    ui->tableView->setModel(listino);
    ui->tableView->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::ResizeToContents);

}


void MainWindow::lineToTestataListino( QSqlDatabase db, QString dbName,
                                       QFile *file)
{
    QByteArray firstLine = file->readLine();
    QString queryString = "INSERT INTO " + dbName + ".testata_listino VALUES (";
    int tab[2][12] = {{0,20,23,34,40,48,56,86,125,128,136,152},
                      {20,3,11,6,8,8,30,39,3,8,16,81}};
    for (int i=0; i<=11; i++){
        QString val;
        val = QString::fromLatin1(firstLine.mid(tab[0][i],tab[1][i]));
        queryString += "'" + val + "', ";

        /**Print values
        int a = tab[0][i];
        int b = tab[1][i];
        qDebug() << __func__ << a << "-" << b << val;
        **/
    }
    queryString = queryString.left(queryString.length() - 2);
    queryString += ")";
    /**Print queryString
    qDebug() << __func__ << queryString;
    **/
    QSqlQuery query = QSqlQuery(db);

    if (query.exec(queryString)){
        qDebug() << __func__ << ":Query ok!";
    } else {
        qDebug() << __func__ << query.lastError();
        qDebug() << __func__ << "test last query:"<< query.lastQuery();
    }
}

void MainWindow::linesToListinoPrezzi(QSqlDatabase db, QString dbName,
                                      QFile *file)
{
    while (!file->atEnd()) {
        QByteArray line = file->readLine();
        QString queryString = "INSERT INTO " + dbName
                + ".listino_prezzi VALUES (";
        int tab[2][19] = {
            {0,3,19,32,75,80,85,90,96,97,108,119,125,128,131,132,133,141,159},
            {3,16,13,43,5,5,5,6,1,11,11,6,3,3,1,1,8,18,18}};
        for (int i=0; i<=18; i++){
            QString val;
            val = QString::fromLatin1(line.mid(tab[0][i],tab[1][i]));
            queryString += "'" + val + "', ";

            /**Print values
            int a = tab[0][i];
            int b = tab[1][i];
            qDebug() << __func__ << a << "-" << b << val;
            **/
        }
        queryString = queryString.left(queryString.length() - 2);
        queryString += ")";
        /**Print queryString
        qDebug() << __func__ << queryString;
        **/
        QSqlQuery query = QSqlQuery(db);

        if (query.exec(queryString)){
            qDebug() << __func__ << ":Query ok!";
        } else {
            qDebug() << __func__ << query.lastError();
            qDebug() << __func__ << "test last query:"<< query.lastQuery();
        }
    }
}

void MainWindow::on_import_Metel_triggered()
{
    //Select metel file QFileDialog
    QString selFilter = tr("TXT(*.txt *.TXT)");
    QString metelFile = QFileDialog::getOpenFileName(this,
                                                     tr("Open Metel® File"),
                                                     "",
                                                     selFilter);
    if (metelFile.isEmpty()){
        return;
    }

    QFile *file = new QFile(metelFile);

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << __func__ << "Can't read file";
        return;
    }

    //Get file name
    QFileInfo fileInfo(file->fileName());
    QString metelFileName = fileInfo.fileName();

    //Get listino Information from first line
    QByteArray firstLine = file->readLine();
    QString listinoInitial, listinoNumber, listinoDate, listinoDescription;

    listinoInitial = QString::fromLatin1(firstLine.mid(20,3));
    listinoNumber = QString::fromLatin1(firstLine.mid(34,6));
    //TODO try to improve date conversion
    listinoDate = QString::fromLatin1(firstLine.mid(40,8));
    QDate Date = QDate::fromString(listinoDate,"yyyyMMdd");
    listinoDate = Date.toString("dd MMMM yyyy");
    listinoDescription = QString::fromLatin1(firstLine.mid(56,30));
    //Count lines
    int lineNr = 0;
    while (!file->atEnd()){
        QByteArray line = file->readLine();
        ++lineNr;
    }

    QString msg = QString(
                "<p><b>File name:</b> %1<br>"
                "<b>Description:</b> %2<br>"
                "<b>Number of products:</b> %3<br>"
                "<b>Initial:</b> %4<br>"
                "<b>Number:</b> %5 <br>"
                "<b>Effective:</b> %6</p>"
                "<p><b>Import the file?</b></p>")
            .arg(metelFileName)
            .arg(listinoDescription)
            .arg(lineNr)
            .arg(listinoInitial)
            .arg(listinoNumber)
            .arg(listinoDate);

    QMessageBox metelFileInfo;
    int ret = metelFileInfo.information(
                this,
                qApp->tr("Metel File Import Information"),
                msg,
                QMessageBox::Ok,
                QMessageBox::Cancel);
    metelFileInfo.setDefaultButton(QMessageBox::Ok);

    switch (ret) {
    case QMessageBox::Ok:
        qDebug() << "Ok pressed";
        break;
    case QMessageBox::Cancel:
        qDebug() << "Cancel pressed";
        break;
    default:
        qDebug() << "Nothing pressed";
        break;
    }

    return;

    QSqlDatabase db = QSqlDatabase::database("viewConnection");
    QString dbName = db.databaseName();

    //First line to "testata_listino"
    lineToTestataListino(db, dbName, file);

    //The Rest file to "listino_prezzi"
    linesToListinoPrezzi(db, dbName, file);

    qDebug() << __func__ << "DONE!";

}

void MainWindow::on_pushButtonFinder_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("viewConnection");
    QSqlQuery query(db);
    QString word = ui->lineEditFinder->text();
    query.prepare("SELECT CONCAT(sigla_marchio,codice_prodotto) AS Codice,"
                  "descrizione_prodotto AS Descrizione,"
                  "pz_rivenditore/moltiplicatore/100 AS 'Prezzo Riv',"
                  "pz_pubblico/moltiplicatore/100 AS 'Prezzo Pub',"
                  "unita_misura AS UM,"
                  "moltiplicatore AS Moltiplicatore,"
                  "qta_cartone AS Cartone "
                  "FROM listino_prezzi "
                  "WHERE CONCAT_WS('|',sigla_marchio,codice_prodotto,"
                  "descrizione_prodotto) LIKE '%" + word + "%'");
    if (query.exec()){
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(query);
        ui->tableView->setModel(model);
        qDebug() << __func__ << "test last query:"<< query.lastQuery();
    } else {
        qDebug() << __func__ << query.lastError();
        qDebug() << __func__ << "test last query:"<< query.lastQuery();
    }
}
