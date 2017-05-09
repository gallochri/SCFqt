#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QSqlError>

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
    QString selFilter = tr("TXT(*.txt *.TXT)");
    QString metelFile =QFileDialog::getOpenFileName(this,
                                         tr("Open Metel® File"),
                                         "",
                                         selFilter);
    if (metelFile.isEmpty()) return;
    QFile *file = new QFile(metelFile);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << __func__ << "Can't read file";
        qDebug() << __func__ << metelFile;
        return;
    }
    qDebug() << __func__ << metelFile;

    QSqlDatabase db = QSqlDatabase::database("viewConnection");
    QString dbName = db.databaseName();

    //First line to "testata_listino"
    lineToTestataListino(db, dbName, file);

    //The Rest file to "listino_prezzi"
    linesToListinoPrezzi(db, dbName, file);

    qDebug() << __func__ << "DONE!";

}
