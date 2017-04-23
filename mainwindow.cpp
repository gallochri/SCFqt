#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbwizard.h"

#include <QDebug>

#include <QSettings>
#include <QSqlDatabase>
#include <QInputDialog>

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
    // Testing code
    settings.beginGroup(KEY);
    settings.setValue(KEY_HOST, "freebsdserver2");
    settings.setValue(KEY_DB, "testdb");
    settings.setValue(KEY_USER, "gallochri");
    settings.setValue(KEY_PWD, "password");
    settings.endGroup();

    if (!db.open()){
            qDebug() << "Problem with DB connection";
            DbWizard *wizard = new DbWizard;
            wizard->show();
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
