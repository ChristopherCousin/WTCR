#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSql>
#include <QSqlError>
#include <iostream>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QVector>
#include "employee.h"
#include "log.h"
#include "user.h"
class Dbmanager
{
public:
    Dbmanager();
    QVector<Employee> employeeDetails(std::string searchBy, std::string toSearch);
    QVector<Employee> allEmployeeDetails();
    QVector<Log> getLogs(std::string searchBy, std::string toSearch);
    QVector<User> getUsers(std::string searchBy, std::string toSearch);
    void changeIsWorkingState(std::string serial,bool isworking);
    void addLog(std::string ean13, int action);
    std::tuple<QString, QString> getEmployeeStatus(std::string serial);
    QString login(QString user, QString password);

private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
