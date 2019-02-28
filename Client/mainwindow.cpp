#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer::singleShot(0, this, SLOT(go()));
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
    qDebug() << message;
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
