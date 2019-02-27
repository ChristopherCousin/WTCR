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
    bool checkEAN13(std::string ean13);
    void changeIsWorkingState(std::string ean13,bool isworking);

private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
