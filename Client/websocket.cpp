#include "websocket.h"


Websocket::Websocket(QUrl uri, QObject *parent) :
    QObject(parent)
{
    m_uri = uri;
    m_webSocket = new QWebSocket();
    connect(m_webSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(processTextMessage(QString)));
    m_webSocket->open(m_uri);
}


void Websocket::onConnected()
{
    qDebug() << "WebSocket connected";
}


void Websocket::processTextMessage(QString message)
{
    emit textMessageArrived(message);
}

void Websocket::sendTextMessage(QString message)
{
    m_webSocket->sendTextMessage(QString(message));
}

bool Websocket::isValid() {
    return m_webSocket->isValid();
}
