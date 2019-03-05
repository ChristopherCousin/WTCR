#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "json.h"
#include <string>
#include <iostream>
#include <QTime>
#include <QTimer>
#include <QRegExp>
#include <QRegExpValidator>
#include <QVector>
#include <QTableWidgetItem>

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer::singleShot(0, this, SLOT(go()));
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::go()
{
    m_webSocket = new Websocket(QUrl("ws://localhost:3344"));
    connect(m_webSocket, SIGNAL(textMessageArrived(QString)), this, SLOT(textMessageArrived(QString)));
}

void MainWindow::textMessageArrived(QString message)
{
    json jso;
    std::string action{""};
    qDebug() << message;
    try {
        auto j = json::parse(message.toStdString());
        jso = j;
        j.at("Action").get_to(action);

    } catch(int e) {
        qDebug() << "JSON NO VALID";
    }

    if(action == "employeeDetails")
    {
        updateAllEmployees(jso);
    }
}

void MainWindow::on_pushButton_clicked()
{
    m_webSocket->sendTextMessage(loginJson(ui->lineEdit->text(), ui->lineEdit_2->text()));
}

QString MainWindow::loginJson(QString user, QString password)
{
    QString txtToReturn{""};

    try
    {
        json j2 = {
          {"Action", "Login"},
          {"user", user.toStdString()},
          {"password", password.toStdString()}
        };
        std::string json = j2.dump();
        txtToReturn =  QString::fromStdString(json);
    } catch(int e) {

    }
    return txtToReturn;
}

void MainWindow::updateAllEmployees(json jso)
{
    QVector<std::string> employeeDetails;

    std::string id{""};
    std::string name{""};
    std::string surname1{""};
    std::string surname2{""};
    std::string birthdate{""};
    std::string identitytype{""};
    std::string identitynum{""};
    std::string serialtypeid{""};
    std::string serialid{""};
    std::string isworking{""};

    jso.at("id").get_to(id);
    jso.at("name").get_to(name);
    jso.at("surname1").get_to(surname1);
    jso.at("surname2").get_to(surname2);
    jso.at("birthdate").get_to(birthdate);
    jso.at("identitytype").get_to(identitytype);
    jso.at("identitynum").get_to(identitynum);
    jso.at("serialtypeid").get_to(serialtypeid);
    jso.at("serialid").get_to(serialid);
    jso.at("isworking").get_to(isworking);

    employeeDetails.append(id);
    employeeDetails.append(name);
    employeeDetails.append(surname1);
    employeeDetails.append(surname2);
    employeeDetails.append(birthdate);
    employeeDetails.append(identitytype);
    employeeDetails.append(identitynum);
    employeeDetails.append(serialtypeid);
    employeeDetails.append(serialid);
    employeeDetails.append(isworking);

    for(int x = 0; x <= 9; x++)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(QString::fromStdString(employeeDetails.at(x)));
         ui->tableWidget->setItem(0,x, newItem);
    }


}
