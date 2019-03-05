#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "websocket.h"
#include "json.h"

using json = nlohmann::json;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString loginJson(QString user, QString password);
    void updateAllEmployees(json jso);

private slots:
    void on_pushButton_clicked();
    void go();
    void textMessageArrived(QString message);

private:
    Ui::MainWindow *ui;
    Websocket *m_webSocket{};
};

#endif // MAINWINDOW_H
