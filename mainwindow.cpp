#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>

#include "mainwindow.h"
#include "dbwizard.h"
#include "ui_mainwindow.h"
#include "config.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
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
    msg += QString(tr("<p><b>Qt Version:</b> %1</p>"))
            .arg(QT_VERSION_STR);
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
    DataListini *listino = new DataListini(this,db);
    ui->tableView->setModel(listino);
}


void MainWindow::on_import_Metel_triggered()
{
    QString selFilter = tr("TXT(*.txt *.TXT)");
    QString metelFile = QFileDialog::getOpenFileName(this,
                                                     tr("Open Metell® File"),
                                                     "",
                                                     selFilter
                                                     );
    if (metelFile.isEmpty()) return;
    QFile file(metelFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << __func__ << "Can't read file";
        qDebug() << __func__ << metelFile;
        return;
    }
    qDebug() << __func__ << metelFile;
    while (!file.atEnd()) {
            QByteArray line = file.readLine();
            qDebug() << __func__ << line;
        }

}
