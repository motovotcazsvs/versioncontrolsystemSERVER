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

void DataBase::pullRecord(QStringList &record)
{
    QString str_query;
    str_query.append("SELECT * FROM ");
    str_query.append(TABLE_NAME);
    str_query.append(" ORDER BY id DESC LIMIT 10");
/*
    maximum_count_string = 0;
    QSqlQuery query(db);
    query.setForwardOnly(true); //для ускорения
    //query.exec("SELECT id, "TABLE_DATE_Y", "TABLE_DATE_M", "TABLE_DATE_D", "TABLE_TIME_H", "TABLE_TIME_M", "TABLE_NUMBERPATIENT", "TABLE_BARCODE", "TABLE_GL", "TABLE_LC", "TABLE_TYPEMEASUREMENT" FROM "TABLE_NAME"");
    //query.exec("SELECT * FROM "TABLE_NAME" ORDER BY id ASC LIMIT 0, 10");
    //query.exec("SELECT * FROM "TABLE_NAME" WHERE "TABLE_BARCODE" IS NULL");
    query.exec(str_query);
    while(query.next()){
        arr_id[maximum_count_string] = query.value(0).toString();
        arr_date_y[maximum_count_string] = query.value(1).toString();
        arr_date_m[maximum_count_string] = query.value(2).toString();
        arr_date_d[maximum_count_string] = query.value(3).toString();
        arr_time_h[maximum_count_string] = query.value(4).toString();
        arr_time_m[maximum_count_string] = query.value(5).toString();
        arr_patient[maximum_count_string] = query.value(6).toString();
        arr_barcode[maximum_count_string] = query.value(7).toString();
        arr_gl[maximum_count_string] = query.value(8).toString();
        arr_lc[maximum_count_string] = query.value(9).toString();
        arr_typemeasurement[maximum_count_string] = query.value(10).toString();

        qDebug() << "setArr()" << arr_id[maximum_count_string] << arr_date_y[maximum_count_string] << arr_date_m[maximum_count_string] << arr_date_d[maximum_count_string] << arr_time_h[maximum_count_string]
                 << arr_time_m[maximum_count_string] << arr_patient[maximum_count_string] << arr_barcode[maximum_count_string] << arr_gl[maximum_count_string] << arr_lc[maximum_count_string] << arr_typemeasurement[maximum_count_string];

        if(maximum_count_string == count_array - 1) break;
        maximum_count_string++;
    }
    */
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
        str += QString::number(i);
        l.append(str);
        //pushRecord(l);
        l.clear();
    }
}


