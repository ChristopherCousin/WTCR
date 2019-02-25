#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include "clineedit.h"


CLineEdit::CLineEdit(QWidget *parent) : QLineEdit{parent}
{
    connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(algo(const QString &)));
}

void CLineEdit::algo(const QString &arg1)
{
    QKeyEvent * event;
    if(event->key() == Qt::Key_U)
    {
        qDebug() << "asd";
    }
}
