#include <string>
#include <QString>
#include <iostream>
#include <tuple>
#include <QVector>
#include "dbmanager.h"
#include "employee.h"
#include "log.h"
#include "user.h"
#include "serials.h"

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

QVector<Log> Dbmanager::getLogs(std::string searchBy, std::string toSearch)
{
    QVector<Log> log{};
    QSqlQuery query;
    if(searchBy == "all")
    {
        query.prepare("select t.id, employee.name,surname1,identitynum,date,hour,actions.name"
                      " from history t INNER JOIN employee ON t.serialid = employee.serialid"
                      " INNER JOIN serialstorage ON employee.serialid = serialstorage.ID INNER"
                      " JOIN actions ON t.actionid = actions.id ORDER BY t.id DESC;");
        query.exec();
    }
    else if(searchBy == "ID")
    {
        query.prepare("select t.id, employee.name,surname1,identitynum,date,hour,actions.name"
                      " from history t INNER JOIN employee ON t.serialid = employee.serialid"
                      " INNER JOIN serialstorage ON employee.serialid = serialstorage.ID INNER"
                      " JOIN actions ON t.actionid = actions.id WHERE t.id = ? ORDER BY t.id DESC;");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "openLogs")
    {
        query.prepare("select t.id, employee.name,surname1,identitynum,date,hour,actions.name"
                      " from history t INNER JOIN employee ON t.serialid = employee.serialid"
                      " INNER JOIN serialstorage ON employee.serialid = serialstorage.ID INNER"
                      " JOIN actions ON t.actionid = actions.id WHERE t.id = ? ORDER BY t.id DESC;");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "Identity Number")
    {
        query.prepare("select t.id, employee.name,surname1,identitynum,date,hour,actions.name"
                      " from history t INNER JOIN employee ON t.serialid = employee.serialid"
                      " INNER JOIN serialstorage ON employee.serialid = serialstorage.ID INNER"
                      " JOIN actions ON t.actionid = actions.id WHERE serialstorage.serial = ? ORDER BY t.id DESC;");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "Date")
    {
        query.prepare("select t.id, employee.name,surname1,identitynum,date,hour,actions.name"
                      " from history t INNER JOIN employee ON t.serialid = employee.serialid"
                      " INNER JOIN serialstorage ON employee.serialid = serialstorage.ID INNER"
                      " JOIN actions ON t.actionid = actions.id WHERE t.date = ? ORDER BY t.id DESC;");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "Hour")
    {
        query.prepare("select t.id, employee.name,surname1,identitynum,date,hour,actions.name"
                      " from history t INNER JOIN employee ON t.serialid = employee.serialid"
                      " INNER JOIN serialstorage ON employee.serialid = serialstorage.ID INNER"
                      " JOIN actions ON t.actionid = actions.id WHERE t.hour = ? ORDER BY t.id DESC;");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "Name")
    {
        query.prepare("select t.id, employee.name,surname1,identitynum,date,hour,actions.name"
                      " from history t INNER JOIN employee ON t.serialid = employee.serialid"
                      " INNER JOIN serialstorage ON employee.serialid = serialstorage.ID INNER"
                      " JOIN actions ON t.actionid = actions.id WHERE employee.name = ? ORDER BY t.id DESC;");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "First surname")
    {
        query.prepare("select t.id, employee.name,surname1,identitynum,date,hour,actions.name"
                      " from history t INNER JOIN employee ON t.serialid = employee.serialid"
                      " INNER JOIN serialstorage ON employee.serialid = serialstorage.ID INNER"
                      " JOIN actions ON t.actionid = actions.id WHERE employee.surname1 = ? ORDER BY t.id DESC;");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }

    while (query.next())
    {
        if (query.isValid())
        {

            Log e;
            e.id = query.value(0).toString();
            e.name = query.value(1).toString();
            e.surname1 = query.value(2).toString();
            e.identitynum = query.value(3).toString();
            e.date = query.value(4).toString();
            e.hour = query.value(5).toString();
            e.actionName = query.value(6).toString();
            log.push_back(e);
        }
        else
        {
        }
    }
    return log;
}

QVector<Serial> Dbmanager::getSerials(std::string searchBy, std::string toSearch)
{
    QVector<Serial> serials{};
    QSqlQuery query;
    if(searchBy == "all")
    {
        query.prepare("SELECT t.id,serialtype.name,serial,active,expired"
                      " from serialstorage t INNER JOIN serialtype ON t.typeid = serialtype.id;");
        query.exec();
    }

    while (query.next())
    {
        if (query.isValid())
        {

            Serial e;
            e.id = query.value(0).toString();
            e.type = query.value(1).toString();
            e.serial = query.value(2).toString();
            e.active = query.value(3).toString();
            e.expired = query.value(4).toString();
            serials.push_back(e);
        }
        else
        {

        }
    }
    return serials;
}

bool Dbmanager::serialAction(QString messsage, QString id)
{
    bool valid = {false};
    QSqlQuery query;
    if(messsage == "deactivate")
    {
        query.prepare("UPDATE serialstorage set active = false where id = ?");
        query.bindValue(0, id);
        query.exec();
    }
    else if(messsage == "activate")
    {
        query.prepare("UPDATE serialstorage set active = true where id = ?");
        query.bindValue(0, id);
        query.exec();
    }

    if (query.lastError().type() == QSqlError::NoError)
    {
        valid = true;
    } else {
        valid = false;
    }
    return valid;
}
QVector<User> Dbmanager::getUsers(std::string searchBy, std::string toSearch)
{
    QVector<User> user{};
    QSqlQuery query;
    if(searchBy == "all")
    {
        query.prepare("SELECT * from users;");
        query.exec();
    }
    else if(searchBy == "id")
    {
        query.prepare("SELECT * from users where id = ?;");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "username")
    {
        query.prepare("SELECT * from users where username = ?;");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }
    else if(searchBy == "privilege")
    {
        query.prepare("SELECT * from users where privilege = ?;");
        query.bindValue(0, QString::fromStdString(toSearch));
        query.exec();
    }

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

bool Dbmanager::addLog(std::string ean13, int action)
{
    QSqlQuery query;
    query.prepare("SELECT * from addLog(?,?);");
    bool valid = {false};

    query.bindValue(0, QString::fromStdString(ean13));
    query.bindValue(1, action);
    query.exec();

    if (query.lastError().type() == QSqlError::NoError)
    {
         qDebug() <<"ok2";
        valid = true;
    } else {
        valid = false;
    }
    return valid;
}

bool Dbmanager::changeIsWorkingState(std::string serial,bool isworking)
{
    QSqlQuery query;
    bool valid = {false};
    query.prepare("SELECT * from setisworkingstate(?,?);");

    query.bindValue(0, QString::fromStdString(serial));
    query.bindValue(1, isworking);
    query.exec();
    query.next();
    if (query.lastError().type() == QSqlError::NoError)
    {
        qDebug() <<"ok1";
        valid = true;
    } else {
        valid = false;
    }
    return valid;
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


