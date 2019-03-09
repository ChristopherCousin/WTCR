#include "server.h"
#include "json.h"
#include <QJsonDocument>
#include <string>
#include <iostream>
#include <QVector>
#include "employee.h"
#include "log.h"
#include "user.h"

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
        if (j.find("Action") != j.end())
        {
            j.at("Action").get_to(action);
            qDebug() << "El Action de:" << pClient << " Es: " << QString::fromStdString(action);
        } else {
            qDebug() << "No se ha podido encontrar el Action del JSON";
        }


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
        } //end if
    }// end if
    else if(action == "Login")
    {
        std::string user = {""};
        std::string password = {""};
        json.at("user").get_to(user);
        json.at("password").get_to(password);
        QString login = dbManager.login(QString::fromStdString(user),QString::fromStdString(password));
        if(login == "Valid")
        {
            allEmployeeDetailsJson();
            allLogsJson();
            allUserJson();
        } else {
            QString toSend = loginFailedJson();
            pClient->sendTextMessage(toSend);
        }

    }
    else if(action == "searchEmployee")
    {
        std::string searchBy = {""};
        std::string toSearch = {""};

        if (json.find("searchBy") != json.end())
        {
            json.at("searchBy").get_to(searchBy);
        }
        if (json.find("toSearch") != json.end())
        {
            json.at("toSearch").get_to(toSearch);
            employeeFoundedJson(searchBy, toSearch);
        }
    }
    else if(action == "searchAllEmployees")
    {
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

QString TestServer::loginFailedJson()
{
    QString toReturn{""};
    try
    {
        json j2 = {
      {"Action", "loginFailed"}
    };
    std::string json = j2.dump();
    toReturn = QString::fromStdString(json);
    } catch(int e){

    }
    return toReturn;
}

void TestServer::allEmployeeDetailsJson()
{
    QVector<Employee> employeeDetails = dbManager.allEmployeeDetails();
    json document;
    json employeesJSON;
    for (int i{ 0 }; i < employeeDetails.count(); i++)
    {
        Employee employee{ employeeDetails.at(i) };
        json employeeJSON;
        employeeJSON["Action"] = "employeesDetails";
        employeeJSON["id"] = employee.id.toStdString();
        employeeJSON["name"] = employee.name.toStdString();
        employeeJSON["surname1"] = employee.surname1.toStdString();
        employeeJSON["surname2"] = employee.surname2.toStdString();
        employeeJSON["birthdate"] = employee.birthdate.toStdString();
        employeeJSON["identitynum"] = employee.identitynum.toStdString();
        employeeJSON["identitytype"] = employee.identitytype.toStdString();
        employeeJSON["serialtypeid"] = employee.serialtypeid.toStdString();
        employeeJSON["serialid"] = employee.serialid.toStdString();
        employeeJSON["isworking"] = employee.isworking.toStdString();
        employeesJSON.push_back(employeeJSON);
    } // end for

    document["employees"] = employeesJSON;
    std::string message = document.dump();
    pClient->sendTextMessage(QString::fromStdString(message));
}

void TestServer::allLogsJson()
{
    QVector<Log> logsDetails = dbManager.allLogs();
    json document;
    json logsJSON;
    for (int i{ 0 }; i < logsDetails.count(); i++)
    {
        Log log{ logsDetails.at(i) };
        json employeeJSON;
        employeeJSON["Action"] = "logsDetails";
        employeeJSON["id"] = log.id.toStdString();
        employeeJSON["serialid"] = log.serialid.toStdString();
        employeeJSON["date"] = log.date.toStdString();
        employeeJSON["hour"] = log.hour.toStdString();
        employeeJSON["actionid"] = log.actionid.toStdString();
        logsJSON.push_back(employeeJSON);
    } // end for

    document["logs"] = logsJSON;
    std::string message = document.dump();
    pClient->sendTextMessage(QString::fromStdString(message));
}

void TestServer::allUserJson()
{
    QVector<User> usersDetails = dbManager.allUsers();
    json document;
    json usersJSON;
    for (int i{ 0 }; i < usersDetails.count(); i++)
    {
        User user{ usersDetails.at(i) };
        json userJSON;
        userJSON["Action"] = "usersDetails";
        userJSON["id"] = user.id.toStdString();
        userJSON["username"] = user.username.toStdString();
        userJSON["password"] = user.password.toStdString();
        userJSON["privilege"] = user.privilege.toStdString();
        usersJSON.push_back(userJSON);
    } // end for

    document["users"] = usersJSON;
    std::string message = document.dump();
    pClient->sendTextMessage(QString::fromStdString(message));
}

void TestServer::employeeFoundedJson(std::string searchBy, std::string toSearch)
{
    Employee employee = dbManager.employeeDetails(searchBy, toSearch);
    json document;

    document["Action"] = "employeeDetails";
    document["id"] = employee.id.toStdString();
    document["name"] = employee.name.toStdString();
    document["surname1"] = employee.surname1.toStdString();
    document["surname2"] = employee.surname2.toStdString();
    document["birthdate"] = employee.birthdate.toStdString();
    document["identitynum"] = employee.identitynum.toStdString();
    document["identitytype"] = employee.identitytype.toStdString();
    document["serialtypeid"] = employee.serialtypeid.toStdString();
    document["serialid"] = employee.serialid.toStdString();
    document["isworking"] = employee.isworking.toStdString();

    std::string message = document.dump();
    pClient->sendTextMessage(QString::fromStdString(message));
}
