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
    //Ponerlo en dll y encriptado
    // crear usuario que solo pueda utilizar funciones
    db.setUserName("usuario");
    db.setPassword("usuario");
    bool ok = db.open();
    if (!ok)
    {

    }
}


std::tuple<QString, bool, bool, int, QString, QString, QString, QString, QString> Dbmanager::employeeDetails(std::string serial)
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

std::tuple<QString, QString> Dbmanager::getEmployeeStatus(std::string serial)
{
    QString name{""};
    QString isWorking{""};

    QSqlQuery query;
    query.prepare("select * from getEmployeeStatus(?);");

    query.bindValue(0, QString::fromStdString(serial));
    query.exec();
    query.next();
    if(query.isValid())
    {
        name = query.value(0).toString();
        isWorking = query.value(1).toString();
    } else {

    }

    return std::make_tuple(name, isWorking);

}

void Dbmanager::addLog(std::string ean13, int action)
{
    QSqlQuery query;
    query.prepare("SELECT * from addLog(?,?);");

    query.bindValue(0, QString::fromStdString(ean13));
    query.bindValue(1, action);
    query.exec();

}

void Dbmanager::changeIsWorkingState(std::string serial,bool isworking)
{
    QSqlQuery query;
    query.prepare("SELECT * from setisworkingstate(?,?);");

    query.bindValue(0, QString::fromStdString(serial));
    query.bindValue(1, isworking);
    query.exec();
    query.next();
    if(query.isValid())
    {


    } else {

    }
}


