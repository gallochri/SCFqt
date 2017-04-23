#ifndef DBWIZARD_H
#define DBWIZARD_H

#include <QWidget>
#include <QWizard>

class DbWizard : public QWizard
{
    Q_OBJECT

public:
    DbWizard(QWidget *parent = 0);
    void accept() override;

signals:

public slots:
};

#endif // DBWIZARD_H
