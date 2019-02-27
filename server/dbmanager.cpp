#include <string>
#include "dbmanager.h"


Dbmanager::Dbmanager()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setDatabaseName("wtcr");
    db.setUserName("usuario");
    db.setPassword("usuario");
    bool ok = db.open();
    if (!ok)
    {

    }
}


bool Dbmanager::checkEAN13(std::string ean13)
{
    bool isworking = false;
    QSqlQuery query;
    query.prepare("SELECT isworking_employees from employees where ean13_employees = ?;");

    query.bindValue(0, ean13);
    query.exec();

    if (!query.lastError().isValid())
    {
        qDebug() << "Error en consulta: " << query.lastError();
    }
    return isworking;
}


void Dbmanager::checkIn(std::string ean13)
{
    QSqlQuery query;
    query.prepare("INSERT INTO logs(ean13_logs,checkindate_logs) values (?,current_timestamp);");

    query.bindValue(0, ean13);
    query.exec();

    if (!query.lastError().isValid())
    {
        qDebug() << "Error en consulta: " << query.lastError();
    }
}

void Dbmanager::changeIsWorkingState(std::string ean13,bool isworking)
{
    QSqlQuery query;
    query.prepare("UPDATE employees set isworking_employees = ? where ean13_employees = ?;");

    query.bindValue(0, ean13);
    query.bindValue(1, isworking);
    query.exec();

    if (!query.lastError().isValid())
    {
        qDebug() << "Error en consulta: " << query.lastError();
    }
}
