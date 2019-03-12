#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QWebSocket>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QUrl>


class Websocket : public QObject
{
    Q_OBJECT
public:
    Websocket(QUrl uri, QObject *parent = nullptr);
    void sendTextMessage(QString message);

public slots:
    void onConnected();
    void processTextMessage(QString message);
    bool isValid();

signals:
     void textMessageArrived(QString message);

private:
    QWebSocket *m_webSocket{};
    QUrl m_uri{};

};

#endif // WEBSOCKET_H
