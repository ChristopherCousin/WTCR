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
    configQTableWidgets();
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

        if (j.find("employees") != j.end())
        {
            if(j.at("employees").is_array())
            {
                json employee;
                employee = j.at("employees").at(0);
                employee.at("Action").get_to(action);
            }
        }
        else if (j.find("logs") != j.end())
        {
            if(j.at("logs").is_array())
            {
                json log;
                log = j.at("logs").at(0);
                log.at("Action").get_to(action);
            }
        }



    } catch(int e) {
        qDebug() << "JSON NO VALID";
    }

    if(action == "employeeDetails")
    {
        updateAllEmployees(jso);
    }
    if(action == "logsDetails")
    {
        updateAllLogs(jso);
    }
}

void MainWindow::on_pushButton_clicked()
{
    m_webSocket->sendTextMessage(loginJson(ui->lineEdit->text(), ui->lineEdit_2->text()));
}

void MainWindow::configQTableWidgets()
{
    int columnCountEmployees{10};
    int columnCountLogs{5};

    ui->tableWidget->setColumnCount(columnCountEmployees);
    ui->tableWidget_logs->setColumnCount(columnCountLogs);

    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("name"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Surname 1"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Surname 2"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Birth Date"));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Identity Type"));
    ui->tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("Identity Num"));
    ui->tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem("Serial Type ID"));
    ui->tableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem("Serial ID"));
    ui->tableWidget->setHorizontalHeaderItem(9, new QTableWidgetItem("Is Working?"));

    ui->tableWidget_logs->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    ui->tableWidget_logs->setHorizontalHeaderItem(1, new QTableWidgetItem("Serial ID"));
    ui->tableWidget_logs->setHorizontalHeaderItem(2, new QTableWidgetItem("Date"));
    ui->tableWidget_logs->setHorizontalHeaderItem(3, new QTableWidgetItem("Hour"));
    ui->tableWidget_logs->setHorizontalHeaderItem(4, new QTableWidgetItem("Action ID"));

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
    ui->tableWidget->setRowCount(employeesTxt.size());

    for(int i{0}; i < employeesTxt.size(); i++)
    {
        json employeeTxt = employeesTxt.at(i);
        QTableWidgetItem *idItem = new QTableWidgetItem(QString::fromStdString(employeeTxt["id"]));
        ui->tableWidget->setItem(i,0,idItem);
        QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(employeeTxt["name"]));
        ui->tableWidget->setItem(i,1,nameItem);
        QTableWidgetItem *surname1Item = new QTableWidgetItem(QString::fromStdString(employeeTxt["surname1"]));
        ui->tableWidget->setItem(i,2,surname1Item);
        QTableWidgetItem *surname2Item = new QTableWidgetItem(QString::fromStdString(employeeTxt["surname2"]));
        ui->tableWidget->setItem(i,3,surname2Item);
        QTableWidgetItem *birthdateItem = new QTableWidgetItem(QString::fromStdString(employeeTxt["birthdate"]));
        ui->tableWidget->setItem(i,4,birthdateItem);
        QTableWidgetItem *identitytypeItem = new QTableWidgetItem(QString::fromStdString(employeeTxt["identitytype"]));
        ui->tableWidget->setItem(i,5,identitytypeItem);
        QTableWidgetItem *identitynumItem = new QTableWidgetItem(QString::fromStdString(employeeTxt["identitynum"]));
        ui->tableWidget->setItem(i,6,identitynumItem);
        QTableWidgetItem *serialtypeidItem = new QTableWidgetItem(QString::fromStdString(employeeTxt["serialtypeid"]));
        ui->tableWidget->setItem(i,7,serialtypeidItem);
        QTableWidgetItem *serialidItem = new QTableWidgetItem(QString::fromStdString(employeeTxt["serialid"]));
        ui->tableWidget->setItem(i,8,serialidItem);
        QTableWidgetItem *isworkingItem = new QTableWidgetItem(QString::fromStdString(employeeTxt["isworking"]));
        ui->tableWidget->setItem(i,9,isworkingItem);
    }
}

void MainWindow::updateAllLogs(json jso)
{
    json logsTxt = jso["logs"];
    ui->tableWidget_logs->setRowCount(logsTxt.size());


    for(int i{0}; i < logsTxt.size(); i++)
    {
        json logTxt = logsTxt.at(i);
        QTableWidgetItem *idItem = new QTableWidgetItem(QString::fromStdString(logTxt["id"]));
        ui->tableWidget_logs->setItem(i,0,idItem);
        QTableWidgetItem *serialidItem = new QTableWidgetItem(QString::fromStdString(logTxt["serialid"]));
        ui->tableWidget_logs->setItem(i,1,serialidItem);
        QTableWidgetItem *dateItem = new QTableWidgetItem(QString::fromStdString(logTxt["date"]));
        ui->tableWidget_logs->setItem(i,2,dateItem);
        QTableWidgetItem *hourItem = new QTableWidgetItem(QString::fromStdString(logTxt["hour"]));
        ui->tableWidget_logs->setItem(i,3,hourItem);
        QTableWidgetItem *actionidItem = new QTableWidgetItem(QString::fromStdString(logTxt["actionid"]));
        ui->tableWidget_logs->setItem(i,4,actionidItem);
    }
}
