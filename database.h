#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlDatabase>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    void connectToDataBase();
    void pushRecord(const QStringList &);
    void pullRecord(QStringList &, QString, QString);
    void pullRecordDOWN(QStringList &, QString, QString);
    //void dataSearch();
    //void controlNextPrevious();
    void closeDataBase();

    void test1();

signals:

public slots:

private:
    QSqlDatabase db;

private:
    bool openDataBase();//Открытие базы данных
    bool restoreDataBase();//Восстановление базы данных
    bool createTable();//Создание базы таблицы в базе данных

};

#endif // DATABASE_H
