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
    void updateAllLogs(json jso);
    void configQTableWidgets();
    void updateAllUsers(json jso);
    void startConfig(bool startConfig);

private slots:
    void on_pushButton_clicked();
    void go();
    void textMessageArrived(QString message);

    void on_tabWidget_users_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    Websocket *m_webSocket{};
};

#endif // MAINWINDOW_H
