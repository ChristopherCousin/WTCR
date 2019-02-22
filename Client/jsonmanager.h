#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

class JsonManager
{
public:
    JsonManager();
    QString toString(QString EAN13);
};

#endif // JSONMANAGER_H
