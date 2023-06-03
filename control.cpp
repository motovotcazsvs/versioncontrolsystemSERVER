#include "control.h"
#include <QDebug>

#define delimiter '`'//розделитель

QString parsingNumDelimiter(QString, int);//парсим данные до разделителя(не включая код действия) по счету от 1 и тд

Control::Control(QObject *parent) : QObject(parent)
{
    obj_database = new DataBase;
    obj_database->connectToDataBase();
    obj_database->test1();
    obj_tcpip = new tcpipastm;

    //если пришел запрос на получение репозиториив
    QObject::connect(obj_tcpip, &tcpipastm::requestGetRepositories, this, &Control::slotGetRepositories);
    QObject::connect(obj_tcpip, &tcpipastm::requestGetRepositoriesUP, this, &Control::slotGetRepositoriesUP);
    QObject::connect(obj_tcpip, &tcpipastm::requestGetRepositoriesDOWN, this, &Control::slotGetRepositoriesDOWN);

}


void Control::slotGetRepositories()
{
    qDebug() << "beru repi";
    QString str = obj_tcpip->getDataReceived();
    bool latest_repositories = false;
    if(str.contains("0307")){//если нужно показать последние репозитории
        latest_repositories = true;
    }
    str = str.mid(4);
    QString enter(parsingNumDelimiter(str, 1));
    QString step(parsingNumDelimiter(str, 2));
    QStringList records;
    if(latest_repositories) obj_database->pullRecordDOWN(records, enter, step);
    else obj_database->pullRecord(records, enter, step);
    QByteArray repositories("0302");
    int count_repositories = records.count();
    QString str_countrepositories = QString::number(count_repositories);
    repositories.append(str_countrepositories);
    repositories.append("`");
    foreach (QString record, records) {
        repositories.append(record);
        repositories.append("`");
    }
    obj_tcpip->writeFrame(repositories);
}

void Control::slotGetRepositoriesUP()
{
    qDebug() << "beru repi";
    QString str = obj_tcpip->getDataReceived();
    str = str.mid(4);
    QString enter(parsingNumDelimiter(str, 1));
    QString step(parsingNumDelimiter(str, 2));
    QStringList records;
    obj_database->pullRecord(records, enter, step);
    QByteArray repositories("0304");
    int count_repositories = records.count();
    QString str_countrepositories = QString::number(count_repositories);
    repositories.append(str_countrepositories);
    repositories.append("`");
    foreach (QString record, records) {
        repositories.append(record);
        repositories.append("`");
    }
    obj_tcpip->writeFrame(repositories);
}

void Control::slotGetRepositoriesDOWN()
{
    qDebug() << "beru repi";
    QString str = obj_tcpip->getDataReceived();
    str = str.mid(4);
    QString enter(parsingNumDelimiter(str, 1));
    QString step(parsingNumDelimiter(str, 2));
    QStringList records;
    obj_database->pullRecordDOWN(records, enter, step);
    QByteArray repositories("0306");
    int count_repositories = records.count();
    QString str_countrepositories = QString::number(count_repositories);
    repositories.append(str_countrepositories);
    repositories.append("`");
    foreach (QString record, records) {
        repositories.append(record);
        repositories.append("`");
    }
    obj_tcpip->writeFrame(repositories);
}

QString parsingNumDelimiter(QString str, int num)//парсим данные до разделителя(не включая код действия) по счету от 1 и тд
{
    //"2`15.89`7.5`";
    int i = 1;
    QString temp_str;
    foreach (QChar s, str){
        if(s == delimiter && i == num){
            break;
        }
        else if(s == delimiter){
            i++;
            temp_str = "";
        }
        else temp_str += s;
    }
    return temp_str;
}

