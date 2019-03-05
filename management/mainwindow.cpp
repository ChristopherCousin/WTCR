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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

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
