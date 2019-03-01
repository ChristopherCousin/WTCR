#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "json.h"
#include <string>
#include <iostream>

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer::singleShot(0, this, SLOT(go()));
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->tabBar()->setCurrentIndex(0);
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
    std::string action{""};
    std::string stateOfEmployee{""};

    try {
        auto j = json::parse(message.toStdString());
        j.at("Action").get_to(action);
        j.at("message").get_to(stateOfEmployee);

    } catch(int e) {
        qDebug() << "JSON NO VALID";
    }

    if(action == "EAN13checked")
    {
        if(stateOfEmployee == "working")
        {
            ui->tabWidget->tabBar()->setCurrentIndex(1);
        }
        else if(stateOfEmployee == "notworking")
        {
            ui->tabWidget->tabBar()->setCurrentIndex(2);
        }
        else if(stateOfEmployee == "inbreaktime")
        {
            ui->tabWidget->tabBar()->setCurrentIndex(1);
        }
        else if(stateOfEmployee == "finishbreaktime")
        {
            ui->tabWidget->tabBar()->setCurrentIndex(1);
        }
    }
}

void MainWindow::pinReaded()
{
   QString toSend = jsonManager.toString(ui->lineEdit->text());
   m_webSocket->sendTextMessage(toSend);
}

void MainWindow::on_pushButton_clicked()
{
    pinReaded();
}

void MainWindow::on_pushButton_3_clicked()
{

}

QString MainWindow::writeJson(QString message)
{
    json j2 = {
      {"action", "EAN13checked"},
      {"message", message.toStdString()}
    };
    std::string json = j2.dump();
    return QString::fromStdString(json);
}
