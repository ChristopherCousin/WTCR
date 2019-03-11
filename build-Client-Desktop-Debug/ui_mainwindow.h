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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <clineedit.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *widget;
    QPushButton *pushButton_Aceptar;
    CLineEdit *lineEdit;
    QLabel *label;
    QWidget *working;
    QPushButton *pushButton_SalirTrabajo;
    QPushButton *pushButton_TiempoDescanso;
    QPushButton *pushButton_FinDescanso;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(482, 354);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        widget = new QWidget();
        widget->setObjectName(QStringLiteral("widget"));
        pushButton_Aceptar = new QPushButton(widget);
        pushButton_Aceptar->setObjectName(QStringLiteral("pushButton_Aceptar"));
        pushButton_Aceptar->setGeometry(QRect(170, 170, 88, 34));
        pushButton_Aceptar->setAutoDefault(false);
        lineEdit = new CLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 110, 391, 32));
        lineEdit->setStyleSheet(QLatin1String("QLineEdit{\n"
"border: 2px solid gray;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"selection-background-color: darkgray;\n"
"font-size: 16px;}\n"
"QLineEdit:focus { background-color:rgb(202, 255, 227);}"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 402, 111));
        QFont font;
        font.setFamily(QStringLiteral("Source Serif Pro Semibold"));
        font.setPointSize(16);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral(""));
        label->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(widget, QString());
        label->raise();
        pushButton_Aceptar->raise();
        lineEdit->raise();
        working = new QWidget();
        working->setObjectName(QStringLiteral("working"));
        pushButton_SalirTrabajo = new QPushButton(working);
        pushButton_SalirTrabajo->setObjectName(QStringLiteral("pushButton_SalirTrabajo"));
        pushButton_SalirTrabajo->setGeometry(QRect(130, 160, 191, 61));
        pushButton_TiempoDescanso = new QPushButton(working);
        pushButton_TiempoDescanso->setObjectName(QStringLiteral("pushButton_TiempoDescanso"));
        pushButton_TiempoDescanso->setGeometry(QRect(130, 70, 191, 61));
        pushButton_FinDescanso = new QPushButton(working);
        pushButton_FinDescanso->setObjectName(QStringLiteral("pushButton_FinDescanso"));
        pushButton_FinDescanso->setGeometry(QRect(130, 70, 191, 61));
        tabWidget->addTab(working, QString());
        pushButton_FinDescanso->raise();
        pushButton_SalirTrabajo->raise();
        pushButton_TiempoDescanso->raise();

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        pushButton_Aceptar->setDefault(false);
        pushButton_SalirTrabajo->setDefault(true);
        pushButton_TiempoDescanso->setDefault(true);
        pushButton_FinDescanso->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButton_Aceptar->setText(QApplication::translate("MainWindow", "Aceptar", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Escribe tu PIN", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(widget), QApplication::translate("MainWindow", "Tab 1", Q_NULLPTR));
        pushButton_SalirTrabajo->setText(QApplication::translate("MainWindow", "Salir del trabajo", Q_NULLPTR));
        pushButton_TiempoDescanso->setText(QApplication::translate("MainWindow", "Tiempo de descanso", Q_NULLPTR));
        pushButton_FinDescanso->setText(QApplication::translate("MainWindow", "Fin de descanso", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(working), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
