/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLineEdit *lineEdit_2;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget_users;
    QWidget *tab_3;
    QTableWidget *tableWidget;
    QLineEdit *lineEdit_3;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QComboBox *comboBox_2;
    QPushButton *pushButton_3;
    QWidget *tab_4;
    QGridLayout *gridLayout_4;
    QTableWidget *tableWidget_logs;
    QWidget *tab_5;
    QTableWidget *tableWidget_2;
    QLineEdit *lineEdit_adduser_username;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_adduser_password;
    QPushButton *pushButton_addUser;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *comboBox;
    QLabel *label_8;
    QLineEdit *lineEdit_adduser_username_2;
    QPushButton *pushButton_searchUser;
    QWidget *tab_6;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(799, 580);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setAutoFillBackground(false);
        tabWidget->setStyleSheet(QStringLiteral(""));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tab->setStyleSheet(QLatin1String("QWidget {\n"
"background-image: url(:/home/chris/wtcr_c/WTCR/build-management-Desktop-Debug/Resources/);\n"
"\n"
"}"));
        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(90, 50, 401, 51));
        lineEdit->setStyleSheet(QLatin1String("QLineEdit{ background-color:rgb(202, 255, 227);\n"
"border: 2px solid gray;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;}\n"
"QLineEdit:focus { background-color:rgb(192, 192, 255);}"));
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(170, 210, 231, 51));
        QFont font;
        font.setPointSize(20);
        pushButton->setFont(font);
        pushButton->setStyleSheet(QStringLiteral(""));
        lineEdit_2 = new QLineEdit(tab);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(90, 130, 401, 51));
        lineEdit_2->setStyleSheet(QLatin1String("QLineEdit{ background-color:rgb(202, 255, 227);\n"
"border: 2px solid gray;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;}\n"
"QLineEdit:focus { background-color:rgb(192, 192, 255);}"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget_users = new QTabWidget(tab_2);
        tabWidget_users->setObjectName(QStringLiteral("tabWidget_users"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tableWidget = new QTableWidget(tab_3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(2, 6, 751, 311));
        lineEdit_3 = new QLineEdit(tab_3);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(250, 344, 451, 32));
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 350, 81, 18));
        QFont font1;
        font1.setPointSize(12);
        label_9->setFont(font1);
        label_10 = new QLabel(tab_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(0, 330, 711, 101));
        label_10->setStyleSheet(QLatin1String("QLabel {\n"
"border: 1px solid #CBC8C8;\n"
"border-radius: 15px;\n"
"}"));
        label_11 = new QLabel(tab_3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 320, 61, 18));
        label_11->setStyleSheet(QLatin1String("QLabel{\n"
"background: solid black;\n"
"color: white;\n"
"}"));
        comboBox_2 = new QComboBox(tab_3);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(110, 344, 121, 32));
        pushButton_3 = new QPushButton(tab_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(367, 390, 161, 34));
        tabWidget_users->addTab(tab_3, QString());
        label_10->raise();
        tableWidget->raise();
        lineEdit_3->raise();
        label_9->raise();
        label_11->raise();
        comboBox_2->raise();
        pushButton_3->raise();
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_4 = new QGridLayout(tab_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tableWidget_logs = new QTableWidget(tab_4);
        tableWidget_logs->setObjectName(QStringLiteral("tableWidget_logs"));

        gridLayout_4->addWidget(tableWidget_logs, 0, 0, 1, 1);

        tabWidget_users->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        tableWidget_2 = new QTableWidget(tab_5);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(10, 60, 381, 361));
        lineEdit_adduser_username = new QLineEdit(tab_5);
        lineEdit_adduser_username->setObjectName(QStringLiteral("lineEdit_adduser_username"));
        lineEdit_adduser_username->setGeometry(QRect(510, 90, 211, 32));
        pushButton_2 = new QPushButton(tab_5);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(287, 13, 101, 41));
        label = new QLabel(tab_5);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(420, 60, 321, 201));
        label->setStyleSheet(QLatin1String("QLabel {\n"
"border: 1px solid #CBC8C8;\n"
"border-radius: 15px;\n"
"}"));
        label_2 = new QLabel(tab_5);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(440, 50, 61, 18));
        label_2->setStyleSheet(QLatin1String("QLabel{\n"
"background: solid black;\n"
"color: white;\n"
"}"));
        lineEdit_adduser_password = new QLineEdit(tab_5);
        lineEdit_adduser_password->setObjectName(QStringLiteral("lineEdit_adduser_password"));
        lineEdit_adduser_password->setGeometry(QRect(510, 130, 211, 32));
        pushButton_addUser = new QPushButton(tab_5);
        pushButton_addUser->setObjectName(QStringLiteral("pushButton_addUser"));
        pushButton_addUser->setGeometry(QRect(560, 210, 101, 34));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        pushButton_addUser->setFont(font2);
        label_3 = new QLabel(tab_5);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(430, 96, 81, 20));
        QFont font3;
        font3.setPointSize(11);
        label_3->setFont(font3);
        label_4 = new QLabel(tab_5);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(430, 136, 81, 20));
        label_4->setFont(font3);
        label_5 = new QLabel(tab_5);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(410, 280, 321, 141));
        label_5->setStyleSheet(QLatin1String("QLabel {\n"
"border: 1px solid #CBC8C8;\n"
"border-radius: 15px;\n"
"}"));
        label_6 = new QLabel(tab_5);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(430, 270, 81, 18));
        label_6->setStyleSheet(QLatin1String("QLabel{\n"
"background: solid black;\n"
"color: white;\n"
"}"));
        label_7 = new QLabel(tab_5);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(430, 176, 71, 20));
        label_7->setFont(font3);
        comboBox = new QComboBox(tab_5);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(510, 170, 211, 32));
        label_8 = new QLabel(tab_5);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(430, 316, 81, 20));
        label_8->setFont(font3);
        lineEdit_adduser_username_2 = new QLineEdit(tab_5);
        lineEdit_adduser_username_2->setObjectName(QStringLiteral("lineEdit_adduser_username_2"));
        lineEdit_adduser_username_2->setGeometry(QRect(510, 310, 211, 32));
        pushButton_searchUser = new QPushButton(tab_5);
        pushButton_searchUser->setObjectName(QStringLiteral("pushButton_searchUser"));
        pushButton_searchUser->setGeometry(QRect(560, 360, 101, 34));
        pushButton_searchUser->setFont(font2);
        tabWidget_users->addTab(tab_5, QString());
        label->raise();
        tableWidget_2->raise();
        lineEdit_adduser_username->raise();
        pushButton_2->raise();
        label_2->raise();
        lineEdit_adduser_password->raise();
        pushButton_addUser->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        label_6->raise();
        label_7->raise();
        comboBox->raise();
        label_8->raise();
        lineEdit_adduser_username_2->raise();
        pushButton_searchUser->raise();
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        tabWidget_users->addTab(tab_6, QString());

        gridLayout_2->addWidget(tabWidget_users, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 799, 30));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);
        tabWidget_users->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("MainWindow", "root", Q_NULLPTR));
        lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "Usuario", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Conectar", Q_NULLPTR));
        lineEdit_2->setText(QApplication::translate("MainWindow", "root", Q_NULLPTR));
        lineEdit_2->setPlaceholderText(QApplication::translate("MainWindow", "Contrase\303\261a", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Search by:", Q_NULLPTR));
        label_10->setText(QString());
        label_11->setText(QApplication::translate("MainWindow", "Add User", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "DNI", Q_NULLPTR)
         << QApplication::translate("MainWindow", "NIE", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Name", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Surname1", Q_NULLPTR)
        );
        pushButton_3->setText(QApplication::translate("MainWindow", "Search", Q_NULLPTR));
        tabWidget_users->setTabText(tabWidget_users->indexOf(tab_3), QApplication::translate("MainWindow", "Employees", Q_NULLPTR));
        tabWidget_users->setTabText(tabWidget_users->indexOf(tab_4), QApplication::translate("MainWindow", "Logs", Q_NULLPTR));
        lineEdit_adduser_username->setPlaceholderText(QApplication::translate("MainWindow", "Username", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Refresh", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Add User", Q_NULLPTR));
        lineEdit_adduser_password->setPlaceholderText(QApplication::translate("MainWindow", "Password", Q_NULLPTR));
        pushButton_addUser->setText(QApplication::translate("MainWindow", "Add", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Username:", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Password:", Q_NULLPTR));
        label_5->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "Search User", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Privilege", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "3", Q_NULLPTR)
        );
        label_8->setText(QApplication::translate("MainWindow", "Username:", Q_NULLPTR));
        lineEdit_adduser_username_2->setPlaceholderText(QApplication::translate("MainWindow", "Username", Q_NULLPTR));
        pushButton_searchUser->setText(QApplication::translate("MainWindow", "Search", Q_NULLPTR));
        tabWidget_users->setTabText(tabWidget_users->indexOf(tab_5), QApplication::translate("MainWindow", "Users", Q_NULLPTR));
        tabWidget_users->setTabText(tabWidget_users->indexOf(tab_6), QApplication::translate("MainWindow", "Add Employee", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "Fi&le", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
