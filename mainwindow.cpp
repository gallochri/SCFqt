#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QSettings>
#include <QSqlDatabase>

#define KEY "db_connection"
#define KEY_HOST "hostname"
#define KEY_DB "database"
#define KEY_USER "username"
#define KEY_PWD "password"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings settings;
    settings.beginGroup(KEY);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(settings.value(KEY_HOST).toString());
    db.setDatabaseName(settings.value(KEY_DB).toString());
    db.setUserName(settings.value(KEY_USER).toString());
    db.setPassword(settings.value(KEY_PWD).toString());

    settings.endGroup();
    if (!db.open()){
            qDebug() << "Problem with DB connection";
//            return;
        }
    qDebug() << "DB connection successfull";
    db.close();
    setupView();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupView(){
    listini = new DataListini();
    ui->tableView->setModel(listini);
}
