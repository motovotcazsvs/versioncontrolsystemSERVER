#include <QCoreApplication>
#include "tcpipastm.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    tcpipastm obj_startserver;
    DataBase database;
    database.connectToDataBase();
    database.test1();

    return a.exec();
}
