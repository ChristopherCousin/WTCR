#include <string>
#include <QString>
#include <iostream>
#include <tuple>
#include <QVector>
#include "dbmanager.h"
#include "employee.h"
#include "log.h"
#include "user.h"

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


QVector<Employee> Dbmanager::employeeDetails(std::string searchBy, std::string toSearch)
{
    QVector<Employee> employee;
    QSqlQuery query;

    if(searchBy == "Serial Code")
    {
        query.prepare("select t.id,name,surname1,surname2,birthdate,identitytype,"
                      "identitynum,serialtypeid,serialid,isworking from employee t "
                      "INNER JOIN serialstorage ON serialstorage.ID = t.serialid "
                      "WHERE serialstorage.serial = ?;");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "name")
    {
        query.prepare("select * from employee WHERE name = ?");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "surname1")
    {
        query.prepare("select * from employee WHERE surname1 = ?");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "Identity Number (DNI/NIE)")
    {
        query.prepare("select * from employee WHERE identitynum = ?");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "surname2")
    {
        query.prepare("select * from employee WHERE surname2 = ?");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "Identity Type")
    {
        query.prepare("select * from employee WHERE identitytype = ?");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "is Working?")
    {
        query.prepare("select * from employee WHERE isworking = true");
        query.exec();
    }
    while (query.next())
    {
        if (query.isValid())
        {
            Employee e;
            e.id = query.value(0).toString();
            e.name = query.value(1).toString();
            e.surname1 = query.value(2).toString();
            e.surname2 = query.value(3).toString();
            e.birthdate = query.value(4).toString();
            e.identitytype = query.value(5).toString();
            e.identitynum = query.value(6).toString();
            e.serialtypeid = query.value(7).toString();
            e.serialid = query.value(8).toString();
            e.isworking = query.value(9).toString();

            employee.push_back(e);
        }
        else
        {
        }
    }

    return employee;

}

QVector<Employee> Dbmanager::allEmployeeDetails()
{
    QVector<Employee> employee{};
    QSqlQuery query;
    query.prepare("SELECT * from employee;");
    query.exec();

    while (query.next())
    {
        if (query.isValid())
        {

            Employee e;
            e.id = query.value(0).toString();
            e.name = query.value(1).toString();
            e.surname1 = query.value(2).toString();
            e.surname2 = query.value(3).toString();
            e.birthdate = query.value(4).toString();
            e.identitytype = query.value(5).toString();
            e.identitynum = query.value(6).toString();
            e.serialtypeid = query.value(7).toString();
            e.serialid = query.value(8).toString();
            e.isworking = query.value(9).toString();

            employee.push_back(e);
        }
        else
        {
        }
    }
    return employee;
}

QVector<Log> Dbmanager::allLogs()
{
    QVector<Log> log{};
    QSqlQuery query;
    query.prepare("SELECT * from history;");
    query.exec();

    while (query.next())
    {
        if (query.isValid())
        {

            Log e;
            e.id = query.value(0).toString();
            e.serialid = query.value(1).toString();
            e.date = query.value(2).toString();
            e.hour = query.value(3).toString();
            e.actionid = query.value(4).toString();

            log.push_back(e);
        }
        else
        {
        }
    }
    return log;
}

QVector<User> Dbmanager::allUsers()
{
    QVector<User> user{};
    QSqlQuery query;
    query.prepare("SELECT * from users;");
    query.exec();

    while (query.next())
    {
        if (query.isValid())
        {

            User e;
            e.id = query.value(0).toString();
            e.username = query.value(1).toString();
            e.password = query.value(2).toString();
            e.privilege = query.value(3).toString();

            user.push_back(e);
        }
        else
        {
        }
    }
    return user;
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


