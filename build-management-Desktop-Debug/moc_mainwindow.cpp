/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../management/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[499];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 2), // "go"
QT_MOC_LITERAL(4, 37, 18), // "textMessageArrived"
QT_MOC_LITERAL(5, 56, 7), // "message"
QT_MOC_LITERAL(6, 64, 33), // "on_tabWidget_users_currentCha..."
QT_MOC_LITERAL(7, 98, 5), // "index"
QT_MOC_LITERAL(8, 104, 36), // "on_pushButton_searchEmployee_..."
QT_MOC_LITERAL(9, 141, 40), // "on_pushButton_searchAllEmploy..."
QT_MOC_LITERAL(10, 182, 48), // "on_comboBox_searchByEmployee_..."
QT_MOC_LITERAL(11, 231, 32), // "on_pushButton_searchLogs_clicked"
QT_MOC_LITERAL(12, 264, 34), // "on_pushButton_searchLogs_2_cl..."
QT_MOC_LITERAL(13, 299, 34), // "on_pushButton_searchLogs_3_cl..."
QT_MOC_LITERAL(14, 334, 22), // "on_tableWidget_clicked"
QT_MOC_LITERAL(15, 357, 34), // "on_pushButton_searchLogs_6_cl..."
QT_MOC_LITERAL(16, 392, 30), // "on_tableWidget_serials_clicked"
QT_MOC_LITERAL(17, 423, 38), // "on_pushButton_deactivateSeria..."
QT_MOC_LITERAL(18, 462, 36) // "on_pushButton_activateSerial_..."

    },
    "MainWindow\0on_pushButton_clicked\0\0go\0"
    "textMessageArrived\0message\0"
    "on_tabWidget_users_currentChanged\0"
    "index\0on_pushButton_searchEmployee_clicked\0"
    "on_pushButton_searchAllEmployees_clicked\0"
    "on_comboBox_searchByEmployee_currentIndexChanged\0"
    "on_pushButton_searchLogs_clicked\0"
    "on_pushButton_searchLogs_2_clicked\0"
    "on_pushButton_searchLogs_3_clicked\0"
    "on_tableWidget_clicked\0"
    "on_pushButton_searchLogs_6_clicked\0"
    "on_tableWidget_serials_clicked\0"
    "on_pushButton_deactivateSerial_clicked\0"
    "on_pushButton_activateSerial_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    1,   91,    2, 0x08 /* Private */,
       6,    1,   94,    2, 0x08 /* Private */,
       8,    0,   97,    2, 0x08 /* Private */,
       9,    0,   98,    2, 0x08 /* Private */,
      10,    1,   99,    2, 0x08 /* Private */,
      11,    0,  102,    2, 0x08 /* Private */,
      12,    0,  103,    2, 0x08 /* Private */,
      13,    0,  104,    2, 0x08 /* Private */,
      14,    1,  105,    2, 0x08 /* Private */,
      15,    0,  108,    2, 0x08 /* Private */,
      16,    1,  109,    2, 0x08 /* Private */,
      17,    0,  112,    2, 0x08 /* Private */,
      18,    0,  113,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->go(); break;
        case 2: _t->textMessageArrived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->on_tabWidget_users_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_searchEmployee_clicked(); break;
        case 5: _t->on_pushButton_searchAllEmployees_clicked(); break;
        case 6: _t->on_comboBox_searchByEmployee_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_pushButton_searchLogs_clicked(); break;
        case 8: _t->on_pushButton_searchLogs_2_clicked(); break;
        case 9: _t->on_pushButton_searchLogs_3_clicked(); break;
        case 10: _t->on_tableWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 11: _t->on_pushButton_searchLogs_6_clicked(); break;
        case 12: _t->on_tableWidget_serials_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 13: _t->on_pushButton_deactivateSerial_clicked(); break;
        case 14: _t->on_pushButton_activateSerial_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
