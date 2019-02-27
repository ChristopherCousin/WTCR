#include "jsonmanager.h"

JsonManager::JsonManager()
{

}


QString JsonManager::toString(QString EAN13)
{
    QJsonObject recordObject;
    QVariant ean13Data(EAN13);
    recordObject.insert("EAN13", QJsonValue::fromVariant(ean13Data));
    recordObject.insert("Action", QJsonValue::fromVariant("checkEAN13"));
    QJsonDocument doc(recordObject);
    return doc.toJson();
}
