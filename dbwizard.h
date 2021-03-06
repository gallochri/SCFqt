#ifndef DBWIZARD_H
#define DBWIZARD_H

#include <QWidget>
#include <QWizard>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QFile>
#include <QSqlQuery>


class DbWizard : public QWizard
{
    Q_OBJECT

public:
    DbWizard(QWidget *parent = 0);
    void accept() override;
};

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

private:
    QLabel *label;
};

class DbConfigPage : public QWizardPage{
    Q_OBJECT
public:
    DbConfigPage(QWidget *parent = 0);
private:
    QLabel *hostnameLabel;
    QLineEdit *hostnameLineEdit;

    QLabel *databaseLabel;
    QLineEdit *databaseLineEdit;

    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;

    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;

    QCheckBox *showPassCheck;
    QLabel *connectionStatusLabel;
    QPushButton *testConnection;

    QLabel *dbStatusLabel;
    QPushButton *createDB;

    void executeQueriesFromFile(QFile *file, QSqlQuery *query);

private slots:
    void on_showPassCheck_stateChanged();
    void on_testConnection_pressed();
    void on_createDB_pressed();

};

class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

protected:
    void initializePage() override;

private:
    QLabel *label;
};

#endif // DBWIZARD_H
