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

class Dbmanager
{
public:
    Dbmanager();
    std::tuple<QString, bool, bool, int, QString, QString, QString, QString, QString> employeeDetails(std::string serial);
    QVector<Employee> allEmployeeDetails();
    void changeIsWorkingState(std::string serial,bool isworking);
    void addLog(std::string ean13, int action);
    std::tuple<QString, QString> getEmployeeStatus(std::string serial);
    QString login(QString user, QString password);

private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
