#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSql>
#include <QSqlError>
#include <iostream>
#include <QSqlQuery>
#include <QString>
#include <QDebug>


class Dbmanager
{
public:
    Dbmanager();
    QString checkEAN13(std::string ean13);
    void changeIsWorkingState(std::string ean13,bool isworking);
    void addLog(std::string ean13, std::string action);

private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
