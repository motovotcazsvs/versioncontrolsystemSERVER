#include <QCoreApplication>
#include "tcpipastm.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    tcpipastm obj_startserver;

    return a.exec();
}
