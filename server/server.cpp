#include "server.h"
#include "json.h"
#include <QJsonDocument>
#include <string>
#include <iostream>
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
    pClient = qobject_cast<QWebSocket*>(sender());
    qDebug() << "De:" << pClient << "Mensaje recibido:" << message;
    try {
        auto j = json::parse(message.toStdString());
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
    try
    {
        json j2 = {
      {"Action", "SerialChecked"},
      {"message", message.toStdString()},
      {"name", employeeName.toStdString()}
    };
    std::string json = j2.dump();
    return QString::fromStdString(json);
    } catch(int e){

    }
}
