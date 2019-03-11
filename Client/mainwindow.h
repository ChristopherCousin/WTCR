#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QTimer>
#include "websocket.h"
#include "clineedit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void pinReaded();
    QString writeJson(QString message);
    void successfullyEnterOrExit(QString action, QString name, int hour);
    QString calculateMessageByHour(QString action, QString name, int time24);


private:
    Ui::MainWindow *ui;
    Websocket *m_webSocket{};
    int timerId{};

private slots:
    void textMessageArrived(QString message);
    void go();
    void on_pushButton_Aceptar_clicked();
    void on_pushButton_TiempoDescanso_clicked();
    void on_pushButton_SalirTrabajo_clicked();
    void on_pushButton_FinDescanso_clicked();
    void on_lineEdit_returnPressed();
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
