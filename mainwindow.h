#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

#include "datalistini.h"
#include "listino.h"

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

    void lineToTestataListino(QSqlDatabase db, QString dbName, QFile *file);
    void linesToListinoPrezzi(QSqlDatabase db, QString dbName, QFile *file);

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
};

#endif // MAINWINDOW_H
