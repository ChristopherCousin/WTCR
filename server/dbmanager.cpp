#include <string>
#include <QString>
#include <iostream>
#include <tuple>
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


std::tuple<QString, bool, bool, int, QString, QString, QString, QString, QString> Dbmanager::checkSerial(std::string serial)
{
    QString serialID{""};
    bool active{false};
    bool expired{false};
    int _TypeID;

    QString name{""};
    QString surname1{""};
    QString surname2{""};
    QString birthdate{""};
    QString isWorking{false};

    QSqlQuery query;
    query.prepare("SELECT * from serialstorage where serial = ?;");

    query.bindValue(0, QString::fromStdString(serial));
    query.exec();
    query.next();
    if(query.isValid())
    {
        serialID = query.value(0).toString();
        active = query.value(3).toBool();
        expired = query.value(4).toBool();
        _TypeID = query.value(1).toInt();
    } else {

    }

    query.prepare("SELECT * from employee where serialid = ?;");

    query.bindValue(0, serialID);
    query.exec();
    query.next();
    if(query.isValid())
    {
        name = query.value(1).toString();
        surname1 = query.value(2).toString();
        surname2 = query.value(3).toString();
        birthdate = query.value(4).toString();
        isWorking = query.value(9).toString();
    } else {

    }
    return std::make_tuple(serialID, active, expired, _TypeID, name, surname1, surname2, birthdate, isWorking);

}


void Dbmanager::addLog(std::string ean13, std::string action)
{
    QSqlQuery query;
    query.prepare("INSERT INTO logs(ean13_logs,date_logs,hour_logs,action_logs) values (?,current_timestamp,current_timestamp,?);");

    query.bindValue(0, QString::fromStdString(ean13));
    query.bindValue(1, QString::fromStdString(action));
    query.exec();

    if (!query.lastError().isValid())
    {
        qDebug() << "Error en consulta: " << query.lastError();
    }
}

void Dbmanager::changeIsWorkingState(std::string serial,bool isworking)
{
    QString serialID{""};
    QSqlQuery query;
    query.prepare("SELECT * from serialstorage where serial = ?;");

    query.bindValue(0, QString::fromStdString(serial));
    query.exec();
    query.next();
    if(query.isValid())
    {
        serialID = query.value(0).toString();

        query.prepare("UPDATE employee set isWorking = ? where serialid = ?;");
        query.bindValue(0, isworking);
        query.bindValue(1, serialID);
        query.exec();

        if (!query.lastError().isValid())
        {
            qDebug() << "Error en consulta: " << query.lastError();
        }

    } else {

    }
}


