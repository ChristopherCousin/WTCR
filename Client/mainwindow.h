#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QTimer>
#include "websocket.h"
#include "jsonmanager.h"
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

private:
    Ui::MainWindow *ui;
    Websocket *m_webSocket{};
    JsonManager jsonManager;

private slots:
    void textMessageArrived(QString message);
    void go();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
