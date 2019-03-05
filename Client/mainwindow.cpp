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
            successfullyEnterOrExit("enter");
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
   try
   {
       json j2 = {
         {"Action", "checkSerial"},
         {"Serial", ui->lineEdit->text().toStdString()}
       };
       std::string jsonTxt = j2.dump();
       m_webSocket->sendTextMessage(QString::fromStdString(jsonTxt));
   } catch(int e) {
        qDebug() << "Error reading the PIN";
   }
}

void MainWindow::successfullyEnterOrExit(QString action)
{
    QTime dieTime= QTime::currentTime().addSecs(3);
    int forOneShot = {0};
    while (QTime::currentTime() < dieTime)
    {
        forOneShot++;
        if(forOneShot == 1)
        {
            ui->label->setGeometry(ui->label->x(), ui->label->y() +50, ui->label->width(), ui->label->height());
            ui->label->setStyleSheet("QLabel{margin-left: 10px; border-radius: 25px; background: white; color: #4A0C46;}");
            ui->label->setText(calculateMessageByHour(action));
            ui->lineEdit->clear();
            ui->lineEdit->setVisible(false);
            ui->pushButton_Aceptar->setVisible(false);
            ui->label->repaint();
        }
    }
    ui->label->setGeometry(ui->label->x(), ui->label->y() -50, ui->label->width(), ui->label->height());
    ui->label->setStyleSheet("");
    ui->label->setText("Introduce tu PIN");
    ui->label->repaint();
    ui->lineEdit->setVisible(true);
    ui->pushButton_Aceptar->setVisible(true);
    forOneShot = 0;
}

QString MainWindow::writeJson(QString message)
{
    QString messageTxt{""};
    try
    {
        json j2 = {
          {"Action", "serialChecked"},
          {"message", message.toStdString()}
        };
        std::string json = j2.dump();
        messageTxt = QString::fromStdString(json);
    } catch(int e) {

    }
    return messageTxt;
}

QString MainWindow::calculateMessageByHour(QString action)
{
    QTime time;
    QString message{""};
    if(time.currentTime().hour() > 12 && time.currentTime().hour() < 5)
    {
        if(action == "enter")
        {
            message = "Buenos días \n Has registrado tu ENTRADA \n sin ningun problema";
        }
        else if (action == "exit")
        {
            message = "Buenos días \n Has registrado tu SALIDA \n sin ningun problema";
        }
    }
    else if(time.currentTime().hour() > 14 && time.currentTime().hour() < 20)
    {
        if(action == "enter")
        {
            message = "Buenas tardes \n Has registrado tu ENTRADA \n sin ningun problema";
        }
        else if (action == "exit")
        {
            message = "Buenas tardes \n Has registrado tu SALIDA \n sin ningun problema";
        }
    }
    else if(time.currentTime().hour() > 20 && time.currentTime().hour() < 5)
    {
        if(action == "enter")
        {
            message = "Buenas noches \n Has registrado tu ENTRADA \n sin ningun problema";
        }
        else if (action == "exit")
        {
            message = "Buenas noches \n Has registrado tu SALIDA \n sin ningun problema";
        }
    }
    return message;

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
     successfullyEnterOrExit("exit");
}

void MainWindow::on_pushButton_FinDescanso_clicked()
{
    m_webSocket->sendTextMessage(writeJson("finishBreakTime"));
    ui->pushButton_TiempoDescanso->setVisible(true);
    ui->tabWidget->tabBar()->setCurrentIndex(0);
    ui->lineEdit->clear();
}
