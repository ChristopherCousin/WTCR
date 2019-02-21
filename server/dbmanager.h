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
    void newOrder(QString phone, QString repair, QString idorder);

private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
