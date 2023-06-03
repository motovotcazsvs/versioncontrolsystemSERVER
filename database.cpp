#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
//#include <QDate>

#define TABLE "Repositories.db3"

//Первая колонка содержит Autoincrement ID
#define TABLE_NAME "RepositoriesTable"//название таблицы
#define TABLE_COLUMN2 "Repositories"//вторая колонка

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{
    db.close();
}

void DataBase::connectToDataBase()
{
/*Перед подключением к базе данных производим проверку на её существование.
В зависимости от результата производим открытие базы данных или её восстановление*/
    if(!QFile(TABLE).exists()) this->restoreDataBase();
    else this->openDataBase();
}

bool DataBase::restoreDataBase()
{
    // Если база данных открылась ...
    if(this->openDataBase()){
        // Производим восстановление базы данных
        return (this->createTable()) ? true : false;
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

bool DataBase::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "dbnum1");
    db.setDatabaseName(TABLE);
    if(db.open()) return true;
    else return false;
}

void DataBase::closeDataBase()
{
    db.close();
}

bool DataBase::createTable()
{
    QSqlQuery query(db);
    if(!query.exec("CREATE TABLE " TABLE_NAME " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    TABLE_COLUMN2 " VARCHAR(255)"
                                            " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE_NAME;
        qDebug() << query.lastError().text();
        return false;
    }
    else return true;

    return false;
}

void DataBase::pullRecord(QStringList &records, QString enter, QString step)
{
    QString str_query;
    str_query.append("SELECT * FROM ");
    str_query.append(TABLE_NAME);
    str_query.append(" ORDER BY id ASC LIMIT " + enter + ", " + step);
    QSqlQuery query(db);
    query.setForwardOnly(true); //для ускорения
    query.exec(str_query);
    while(query.next()){
        records.append(query.value(1).toString());
    }

}

void DataBase::pullRecordDOWN(QStringList &records, QString enter, QString step)
{
    QString str_query;
    str_query.append("SELECT * FROM ");
    str_query.append(TABLE_NAME);
    str_query.append(" ORDER BY id DESC LIMIT " + enter + ", " + step);
    QSqlQuery query(db);
    query.setForwardOnly(true); //для ускорения
    query.exec(str_query);
    while(query.next()){
        records.append(query.value(1).toString());
    }
}

void DataBase::pushRecord(const QStringList &record)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO " TABLE_NAME "(" TABLE_COLUMN2 ")"
                  "VALUES(:table_column2)"
                  );
    query.bindValue(":table_column2", record[0]);
    query.exec();
}

void DataBase::test1()
{
    QStringList l;
    for(int i = 0; i < 50; i++){
        QString str("repository");
        str += QString::number(i + 1);
        l.append(str);
        //pushRecord(l);
        l.clear();
    }
}


