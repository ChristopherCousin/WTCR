#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include <QString>

struct Employee {
    QString id{""};
    QString name{""};
    QString surname1{""};
    QString surname2{""};
    QString birthdate{""};
    QString identitytype{""};
    QString identitynum{""};
    QString serialtypeid{""};
    QString serialid{""};
    QString isworking{""};
};

#endif // EMPLOYEE_H
