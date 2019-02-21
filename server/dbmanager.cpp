#include "dbmanager.h"


Dbmanager::Dbmanager()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setDatabaseName("phoneshop");
    db.setUserName("usuario");
    db.setPassword("usuario");
    bool ok = db.open();
    if (!ok)
    {
    }
}


void Dbmanager::newOrder(QString phone, QString repair, QString idorder)
{

    QSqlQuery query;
    query.prepare("INSERT INTO "
                    "orders(statusorders,phoneorders,repairorders,"
                    "orderidorders,dateorders) values('On the way of the technician',"
            "?,?,?,current_timestamp);");

    query.bindValue(0, phone);
    query.bindValue(1, repair);
    query.bindValue(2, idorder);
    query.exec();

    if (!query.lastError().isValid())
    {
        qDebug() << "Error en consulta: " << query.lastError();
    }
}
