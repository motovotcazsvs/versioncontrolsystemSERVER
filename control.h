#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include "tcpipastm.h"
#include "database.h"

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);


signals:

public slots:

private slots:
    void slotGetRepositories();
    void slotGetRepositoriesUP();
    void slotGetRepositoriesDOWN();


private:
    tcpipastm *obj_tcpip;
    DataBase *obj_database;
};

#endif // CONTROL_H
