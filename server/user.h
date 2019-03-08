#ifndef USER_H
#define USER_H

#include <iostream>
#include <QString>

struct User {
    QString id{""};
    QString username{""};
    QString password{""};
    QString privilege{""};
};

#endif // USER_H
