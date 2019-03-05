#include "server.h"
#include "json.h"
#include <QJsonDocument>
#include <string>
#include <iostream>
#include <QVector>

using json = nlohmann::json;

TestServer::TestServer(quint16 port)
    : m_pWebSocketServer(new QWebSocketServer(
          QStringLiteral("Test Server"), QWebSocketServer::NonSecureMode, this))
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server iniciado en puerto:" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this,
            &TestServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &TestServer::closed);
    } // end if
}

TestServer::~TestServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}


void TestServer::onNewConnection()
{
    QWebSocket* pSocket = m_pWebSocketServer->nextPendingConnection();
    qDebug() << "Socket conectado:" << pSocket;

    connect(pSocket, &QWebSocket::textMessageReceived, this, &TestServer::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &TestServer::socketDisconnected);

    m_clients << pSocket;

}


void TestServer::processTextMessage(QString message)
{
    std::string action{""};
    std::string jsonMessage{""};
    json json;
    pClient = qobject_cast<QWebSocket*>(sender());
    qDebug() << "De:" << pClient << "Mensaje recibido:" << message;
    try {
        auto j = json::parse(message.toStdString());
        json = j;
        j.at("Action").get_to(action);
        if(action == "checkSerial")
        {
            j.at("Serial").get_to(serial);
        }
        else if(action == "serialChecked")
        {
            j.at("message").get_to(jsonMessage);
        }

    } catch(int e) {
        qDebug() << "JSON NO VALID";
    }

    if(action == "checkSerial")
    {
        auto employeInfo = dbManager.getEmployeeStatus(serial);
        QString isWorking = std::get<1>(employeInfo);
        QString name = std::get<0>(employeInfo);
        qDebug() << isWorking;
        if(isWorking == "true" || isWorking == "TRUE")
        {
            QString jsonToSend = createSerialCheckedJson("working", name);
            pClient->sendTextMessage(jsonToSend);
        }
        else if(isWorking == "false" || isWorking == "FALSE")
        {
            QString jsonToSend = createSerialCheckedJson("notworking", name);
            pClient->sendTextMessage(jsonToSend);
        } else {
            QString jsonToSend = createSerialCheckedJson("doesnotexist", name);
            pClient->sendTextMessage(jsonToSend);
        }
    }
    else if(action == "serialChecked")
    {
        if(jsonMessage == "finishWork")
        {
            dbManager.addLog(serial,2);
            dbManager.changeIsWorkingState(serial, false);
        }
        else if(jsonMessage == "startwork")
        {
            dbManager.addLog(serial,1);
            dbManager.changeIsWorkingState(serial, true);
        }
        else if(jsonMessage == "startBreakTime")
        {
            dbManager.addLog(serial,3);
        }
        else if(jsonMessage == "startwork")
        {
            dbManager.addLog(serial,1);
            dbManager.changeIsWorkingState(serial, true);
        }
        else if(jsonMessage == "finishBreakTime")
        {
            dbManager.addLog(serial,4);
        }
    }
    else if(action == "Login")
    {
        std::string user = {""};
        std::string password = {""};
        json.at("user").get_to(user);
        json.at("password").get_to(password);
        qDebug() << dbManager.login(QString::fromStdString(user),QString::fromStdString(password));
        allEmployeeDetailsJson();

    }


}


void TestServer::socketDisconnected()
{
    QWebSocket* pClient = qobject_cast<QWebSocket*>(sender());
    qDebug() << "Socket desconectado:" << pClient;

    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    } // end if
}

QString TestServer::createSerialCheckedJson(QString message, QString employeeName)
{
    QString toReturn{""};
    try
    {
        json j2 = {
      {"Action", "SerialChecked"},
      {"message", message.toStdString()},
      {"name", employeeName.toStdString()}
    };
    std::string json = j2.dump();
    toReturn = QString::fromStdString(json);
    } catch(int e){

    }
    return toReturn;
}
QString TestServer::employeeDetailsJson(QString serial)
{
    QString toReturn{""};
    auto employeeDetails = dbManager.employeeDetails(serial.toStdString());
    try
    {
        json j2 = {
      {"Action", "employeeDetails"},
      {"name", "asd"}
    };
    std::string json = j2.dump();
    toReturn = QString::fromStdString(json);
    } catch(int e){

    }
    return toReturn;
}

void TestServer::allEmployeeDetailsJson()
{
    auto employeeDetails = dbManager.allEmployeeDetails();
    QVector<QString> id = std::get<0>(employeeDetails);
    QVector<QString> name = std::get<1>(employeeDetails);
    QVector<QString> surname1 = std::get<2>(employeeDetails);
    QVector<QString> surname2 = std::get<3>(employeeDetails);
    QVector<QString> birthdate = std::get<4>(employeeDetails);
    QVector<QString> identitytype = std::get<5>(employeeDetails);
    QVector<QString> identitynum = std::get<6>(employeeDetails);
    QVector<QString> serialtypeid = std::get<7>(employeeDetails);
    QVector<QString> serialid = std::get<8>(employeeDetails);
    QVector<QString> isworking = std::get<9>(employeeDetails);
    for(int x = 0; x <= id.count() -1; x++)
    {
        try
        {
            json j2 = {

          {"Action", "employeeDetails"},
          {"id", id.at(x).toStdString()},
          {"name", name.at(x).toStdString()},
          {"surname1", surname1.at(x).toStdString()},
          {"surname2", surname2.at(x).toStdString()},
          {"birthdate", birthdate.at(x).toStdString()},
          {"identitytype", identitytype.at(x).toStdString()},
          {"identitynum", identitynum.at(x).toStdString()},
          {"serialtypeid", serialtypeid.at(x).toStdString()},
          {"serialid", serialid.at(x).toStdString()},
          {"isworking", isworking.at(x).toStdString()}

        };
        std::string json = j2.dump();
        pClient->sendTextMessage(QString::fromStdString(json));
        } catch(int e){

        }
    }

}
