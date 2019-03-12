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
    void updateAllSerials(json jso);
    void configQTableWidgets();
    void updateAllUsers(json jso);
    void startConfig(bool startConfig);
    QString searchEmployeesJson(QString searchBy, QString toSearch);
    QString searchLogsJson(QString searchBy, QString toSearch);
    void setEmployeesFounded(json jso);
    void moveWindowToTheCenter();
    QString searchAllEmployesJson();
    QString searchSerialsJson(QString searchBy, QString toSearch);
    QString serialAction(QString action, QString id);

private slots:
    void on_pushButton_clicked();
    void go();
    void textMessageArrived(QString message);

    void on_tabWidget_users_currentChanged(int index);

    void on_pushButton_searchEmployee_clicked();

    void on_pushButton_searchAllEmployees_clicked();

    void on_comboBox_searchByEmployee_currentIndexChanged(int index);

    void on_pushButton_searchLogs_clicked();

    void on_pushButton_searchLogs_2_clicked();

    void on_pushButton_searchLogs_3_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_pushButton_searchLogs_6_clicked();

    void on_tableWidget_serials_clicked(const QModelIndex &index);

    void on_pushButton_deactivateSerial_clicked();

    void on_pushButton_activateSerial_clicked();

private:
    Ui::MainWindow *ui;
    Websocket *m_webSocket{};
};

#endif // MAINWINDOW_H
