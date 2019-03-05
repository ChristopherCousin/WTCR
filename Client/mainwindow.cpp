#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "json.h"
#include <string>
#include <iostream>
#include <QTime>

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
    qDebug() << message;

    try {
        auto j = json::parse(message.toStdString());
        j.at("Action").get_to(action);
        j.at("message").get_to(stateOfEmployee);

    } catch(int e) {
        qDebug() << "JSON NO VALID";
    }

    if(action == "SerialChecked")
    {
        if(stateOfEmployee == "working")
        {
            ui->pushButton_TiempoDescanso->setText("Tiempo de descanso");
            ui->tabWidget->tabBar()->setCurrentIndex(1);
        }
        else if(stateOfEmployee == "notworking")
        {
            welcome();
            m_webSocket->sendTextMessage(writeJson("startwork"));

        }
        else if(stateOfEmployee == "inbreaktime")
        {
            ui->tabWidget->tabBar()->setCurrentIndex(1);
            ui->pushButton_TiempoDescanso->setText("Empezar a trabajar");
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

void MainWindow::welcome()
{
    QTime dieTime= QTime::currentTime().addSecs(3);
    while (QTime::currentTime() < dieTime)
    {
        ui->label->setText("Bienvenido ");
        ui->label->repaint();
        ui->lineEdit->clear();
        ui->lineEdit->setVisible(false);
        ui->pushButton_Aceptar->setVisible(false);
    }
    ui->label->setText("Introduce tu PIN");
    ui->label->repaint();
    ui->lineEdit->setVisible(true);
    ui->pushButton_Aceptar->setVisible(true);
}

QString MainWindow::writeJson(QString message)
{
    try
    {
        json j2 = {
          {"Action", "serialChecked"},
          {"message", message.toStdString()}
        };
        std::string json = j2.dump();
        return QString::fromStdString(json);
    } catch(int e) {

    }

}


void MainWindow::on_pushButton_Aceptar_clicked()
{
    pinReaded();
}

void MainWindow::on_pushButton_TiempoDescanso_clicked()
{
    m_webSocket->sendTextMessage(writeJson("startBreakTime"));
    ui->lineEdit->clear();
    ui->pushButton_TiempoDescanso->setVisible(false);
    ui->tabWidget->tabBar()->setCurrentIndex(0);
}

void MainWindow::on_pushButton_SalirTrabajo_clicked()
{
     m_webSocket->sendTextMessage(writeJson("finishWork"));
     ui->tabWidget->tabBar()->setCurrentIndex(0);
     ui->lineEdit->clear();
}

void MainWindow::on_pushButton_FinDescanso_clicked()
{
    m_webSocket->sendTextMessage(writeJson("finishBreakTime"));
    ui->pushButton_TiempoDescanso->setVisible(true);
    ui->tabWidget->tabBar()->setCurrentIndex(0);
    ui->lineEdit->clear();
}
