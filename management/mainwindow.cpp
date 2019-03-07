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
    json employeesTxt = jso["employees"];

    for(int i{0}; i < employeeTxt.size(); i++)
    {
        json employeeTxt = employeesTxt.at(i);
        ui->tableWidget->setItem();
    }
}
