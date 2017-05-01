#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

#include "datalistini.h"

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
protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_action_About_triggered();
    void on_actionAbout_Qt_triggered();
    void on_action_Wizard_triggered();

private:

    Ui::MainWindow *ui;
    DataListini *listini;
    QSqlDatabase viewConnection();
};

#endif // MAINWINDOW_H
