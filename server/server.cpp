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
    std::string ean13{""};
    pClient = qobject_cast<QWebSocket*>(sender());
    qDebug() << "De:" << pClient << "Mensaje recibido:" << message;
    try {
        auto j = json::parse(message.toStdString());
        j.at("Action").get_to(action);
        j.at("EAN13").get_to(ean13);

    } catch(int e) {
        qDebug() << "JSON NO VALID";
    }

    if(action == "checkEAN13")
    {
        QString isworking = dbManager.checkEAN13(ean13);
        if(isworking == "true" || isworking == "TRUE")
        {
            QString jsonToSend = createEAN13checkedJson("working");
            pClient->sendTextMessage(jsonToSend);
        }
        else if(isworking == "false" || isworking == "FALSE")
        {
            QString jsonToSend = createEAN13checkedJson("notworking");
            pClient->sendTextMessage(jsonToSend);
        } else {
            QString jsonToSend = createEAN13checkedJson("doesnotexist");
            pClient->sendTextMessage(jsonToSend);
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

QString TestServer::createEAN13checkedJson(QString message)
{
    json j2 = {
      {"action", "EAN13checked"},
      {"message", message.toStdString()}
    };
    std::string json = j2.dump();
    return QString::fromStdString(json);
}
