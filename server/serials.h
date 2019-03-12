#ifndef SERIALS_H
#define SERIALS_H

#include <QString>

struct Serial {
    QString id{""};
    QString type{""};
    QString serial{""};
    QString active{""};
    QString expired{""};
};

#endif // SERIALS_H
