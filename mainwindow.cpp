#include <QMessageBox>
#include <QApplication>

#include "mainwindow.h"
#include "dbwizard.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    setupView();
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

void MainWindow::setupView()
{
    listini = new DataListini();
    ui->tableView->setModel(listini);
}

