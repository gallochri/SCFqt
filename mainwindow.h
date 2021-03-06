#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QSqlError>
#include <QDate>
#include <QElapsedTimer>
#include <QTextCodec>

#include "ui_mainwindow.h"
#include "datalistini.h"
#include "listino.h"
#include "dbwizard.h"
#include "config.h"

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startWizard(MainWindow *mainWin);
    void setupView();

    bool lineToTestataListino(QSqlDatabase db, QString dbName, QFile *file);
    bool linesToListinoPrezzi(QSqlDatabase db, QString dbName, QFile *file,
                              int totalLines);

    int linesCounter(QFile *file);
    
protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_action_About_triggered();
    void on_actionAbout_Qt_triggered();
    void on_action_Wizard_triggered();
    void on_import_Metel_triggered();
    void on_pushButtonFinder_clicked();

private:
    Ui::MainWindow *ui;
    DataListini *listini;
    QSqlDatabase viewConnection();
    QLabel productImport;
    QLabel timeImport;
};

#endif // MAINWINDOW_H
