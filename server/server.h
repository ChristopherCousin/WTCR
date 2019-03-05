#ifndef SERVER_H
#define SERVER_H

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <iostream>
#include <QCoreApplication>
#include <tuple>
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include "dbmanager.h"



class QWebSocketServer;
class QWebSocket;


class TestServer : public QObject
{
    Q_OBJECT

public:
    explicit TestServer(quint16 port);
    ~TestServer();
    QWebSocket* pClient;
    QString createSerialCheckedJson(QString message, QString employeeName);
    QString employeeDetailsJson(QString serial);
    void allEmployeeDetailsJson();


signals:
    void closed();

private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    Dbmanager dbManager;
    std::string serial{""};

};

#endif
