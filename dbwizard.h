#ifndef DBWIZARD_H
#define DBWIZARD_H

#include <QWidget>
#include <QWizard>
#include <QLabel>
#include <QLineEdit>

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
