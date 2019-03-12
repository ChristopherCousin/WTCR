#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "json.h"
#include <string>
#include <iostream>
#include <QTime>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer::singleShot(0, this, SLOT(go()));
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->tabBar()->setCurrentIndex(0);
    ui->lineEdit->setFocus();
    ui->pushButton_Aceptar->setDefault(true);
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
void MainWindow::timerEvent(QTimerEvent *event)
{
    ui->label->setGeometry(ui->label->x(), ui->label->y() -50, ui->label->width(), ui->label->height());
    ui->label->setStyleSheet("");
    ui->label->setText("Introduce tu PIN");
    ui->label->repaint();
    ui->lineEdit->setVisible(true);
    ui->pushButton_Aceptar->setVisible(true);
    killTimer(timerId);
}

void MainWindow::textMessageArrived(QString message)
{
    std::string action{""};
    std::string stateOfEmployee{""};
    qDebug() << message;
    json jso;

    try {
        auto j = json::parse(message.toStdString());
        jso = j;
        if (j.find("Action") != j.end())
        {
            j.at("Action").get_to(action);
        }
        if (j.find("message") != j.end())
        {
            j.at("message").get_to(stateOfEmployee);
        }

    } catch(int e) {
        qDebug() << "JSON NO VALID";
    }

    if(action == "SerialChecked")
    {
        std::string name{""};
        int hour{};
        if (jso.find("name") != jso.end())
        {
            jso.at("name").get_to(name);
        }
        if (jso.find("hour") != jso.end())
        {
            jso.at("hour").get_to(hour);
        }
        if(stateOfEmployee == "working")
        {
            ui->pushButton_TiempoDescanso->setText("Tiempo de descanso");
            ui->tabWidget->tabBar()->setCurrentIndex(1);
        }
        else if(stateOfEmployee == "notworking")
        {
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
        else if(stateOfEmployee == "doesnotexist")
        {
            QMessageBox msgBoxError;
            msgBoxError.setText("No existe ningun empleado con este codigo");
            msgBoxError.exec();
        }
    }
    else if(action == "actionChecked")
    {
        QMessageBox msgBoxError;
        msgBoxError.setText("Ha habido un problema con el servidor, avisa al tecnico");


        std::string actionName{""};
        std::string employeeName{""};
        int hour{};
        if (jso.find("actionName") != jso.end())
        {
            jso.at("actionName").get_to(actionName);
        }
        if (jso.find("employeeName") != jso.end())
        {
            jso.at("employeeName").get_to(employeeName);
        }
        if (jso.find("hour") != jso.end())
        {
            jso.at("hour").get_to(hour);
        }

        if(actionName == "startWorkValid")
        {
            successfullyEnterOrExit("enter", QString::fromStdString(employeeName), hour);
        }
        else if(actionName == "finishWorkValid")
        {
            ui->tabWidget->tabBar()->setCurrentIndex(0);
            ui->lineEdit->clear();
            successfullyEnterOrExit("exit",QString::fromStdString(employeeName),hour);
        }
        else if(actionName == "startBreakTimeValid")
        {
            successfullyEnterOrExit("breakTime",QString::fromStdString(employeeName),hour);
            ui->lineEdit->clear();
            ui->pushButton_TiempoDescanso->setVisible(false);
            ui->tabWidget->tabBar()->setCurrentIndex(0);
        }
        else if(actionName == "finishBreakTimeValid")
        {
            successfullyEnterOrExit("stopBreakTime",QString::fromStdString(employeeName),hour);
            ui->pushButton_TiempoDescanso->setVisible(true);
            ui->tabWidget->tabBar()->setCurrentIndex(0);
            ui->lineEdit->clear();
        }
        else if(actionName == "startWorkNoValid")
        {
                    msgBoxError.exec();
        }
        else if(actionName == "finishWorkNoValid")
        {
                    msgBoxError.exec();
        }
        else if(actionName == "startBreakTimeNoValid")
        {
                    msgBoxError.exec();
        }
        else if(actionName == "finishBreakTimeNoValid")
        {
                    msgBoxError.exec();
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

void MainWindow::successfullyEnterOrExit(QString action, QString name, int hour)
{
            ui->label->setGeometry(ui->label->x(), ui->label->y() +50, ui->label->width(), ui->label->height());
            ui->label->setStyleSheet("QLabel{margin-left: 10px; border-radius: 25px; background: white; color: #4A0C46;}");
            ui->label->setText(calculateMessageByHour(action, name, hour));
            ui->lineEdit->clear();
            ui->lineEdit->setVisible(false);
            ui->pushButton_Aceptar->setVisible(false);
            ui->label->repaint();
            timerId = startTimer(4000);
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

QString MainWindow::calculateMessageByHour(QString action, QString name, int time24)
{
    qDebug() << time24;
    QString message{""};

        if(time24 >= 6 && time24 <= 14)
        {
            if(action == "enter")
            {
                message = "Buenos días "+name+ "\n Has registrado tu ENTRADA";
            }
            else if (action == "exit")
            {
                message = "Buenos días "+name+"\n Has registrado tu SALIDA";
            }
            else if (action == "breakTime")
            {
                message = "Has registrado tu DESCANSO";
            }
            else if (action == "stopBreakTime")
            {
                message = "Has registrado tu FIN DE DESCANSO";
            }
        }
        else if(time24 >= 14 && time24 <= 20)
        {
            if(action == "enter")
            {
                message = "Buenas tardes "+name+"\n Has registrado tu ENTRADA";
            }
            else if (action == "exit")
            {
                message = "Buenas tardes "+name+"\n Has registrado tu SALIDA";
            }
            else if (action == "breakTime")
            {
                message = "Has registrado tu DESCANSO";
            }
            else if (action == "stopBreakTime")
            {
                message = "Has registrado tu FIN DE DESCANSO";
            }
        }
        else if(time24 >= 20 && time24 <= 23 || time24 >= 0 && time24 <= 5)
        {
            if(action == "enter")
            {
                message = "Buenas noches "+name+"\n Has registrado tu ENTRADA";
            }
            else if (action == "exit")
            {
                message = "Buenas noches "+name+"\n Has registrado tu SALIDA";
            }
            else if (action == "breakTime")
            {
                message = "Has registrado tu DESCANSO";
            }
            else if (action == "stopBreakTime")
            {
                message = "Has registrado tu FIN DE DESCANSO";
            }
        } else {
                message = "Hola, Has registrado correctamente\nPero avisa al tecnico ha\N habido un Problema.";
        } // fin IF

    return message;

}
void MainWindow::on_pushButton_Aceptar_clicked()
{
    if(!m_webSocket->isValid())
    {
        QMessageBox msg;
                msg.setText("No estás conectado al servidor");
                msg.exec();
    } else {
        if(checkEmployeeInfo())
        {
                pinReaded();
        }
    }
}

bool MainWindow::checkEmployeeInfo()
{
    QString serial = ui->lineEdit->text();

        // EAN13 must be numbers
        for (int i = 0; i < serial.length(); i++) {
            if (!serial.at(i).isDigit()) {
                qDebug() << "deben ser numeros";
                return false;
            }
        }

        // must have 13 chars
            if (serial.length() != 13)
            {
                qDebug() << "Tienen que ser 13 characteres";
                return false;
            }

        // last digit is for validation
                if (serial.at(serial.length()-1) != checkSumDigit()) {
                    qDebug() << "No es un ean13 Valido!";
                    return false;
                }

                return true;

}

QString MainWindow::checkSumDigit()
{
    int sum{0};
    QString serial = ui->lineEdit->text();

    for (int i = 0; i < serial.length()-1; i++) {
        sum += serial.mid(i, 1).toInt() * ((i%2 == 0) ? 1 : 3);
    }

    int mod = sum%10;
    return QString::number((mod == 0) ? 0 : 10 - mod);
}


void MainWindow::on_pushButton_TiempoDescanso_clicked()
{
    m_webSocket->sendTextMessage(writeJson("startBreakTime"));
}

void MainWindow::on_pushButton_SalirTrabajo_clicked()
{
     m_webSocket->sendTextMessage(writeJson("finishWork"));
}

void MainWindow::on_pushButton_FinDescanso_clicked()
{
    m_webSocket->sendTextMessage(writeJson("finishBreakTime"));
}

void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_Aceptar_clicked();
}
