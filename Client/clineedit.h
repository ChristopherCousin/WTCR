#ifndef CLINEEDIT_H
#define CLINEEDIT_H

#include <QLineEdit>

class CLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    CLineEdit(QWidget *parent = nullptr);

public slots:
     void algo(const QString &arg1);

};


#endif // CLINEEDIT_H
