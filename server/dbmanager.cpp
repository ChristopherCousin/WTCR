#include <string>
#include <QString>
#include <iostream>
#include <tuple>
#include <QVector>
#include "dbmanager.h"
#include "employee.h"

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

QVector<Employee> Dbmanager::allEmployeeDetails()
{
    QVector<Employee> employee{};
    QSqlQuery query;
    query.prepare("SELECT * from employee;");
    query.exec();

    while(query.next())
    {
        if(query.isValid())
        {

            Employee e{query.value(0).toString(), query.value(1).toString(), query.value(2).toString(),
                      query.value(3).toString(), query.value(4).toString(), query.value(5).toString(),
                      query.value(6).toString(), query.value(7).toString(), query.value(8).toString(),
                      query.value(9).toString()};
            employee.push_back(e);

        } else {

        }
    }
    return employee;

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

QString Dbmanager::login(QString user, QString password)
{
    QString toReturn = {""};
    QSqlQuery query;
    query.prepare("SELECT * from users where username = ? AND password = ?;");

    query.bindValue(0, user);
    query.bindValue(1, password);
    query.exec();
    query.next();
    if(query.isValid())
    {
        toReturn = "Valid";

    } else {
        toReturn = "Dosn't Exist";
    }
    return toReturn;
}


