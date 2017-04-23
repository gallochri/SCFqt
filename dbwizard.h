#ifndef DBWIZARD_H
#define DBWIZARD_H

#include <QWidget>
#include <QWizard>
#include <QLabel>

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


#endif // DBWIZARD_H
