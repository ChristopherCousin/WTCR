#ifndef LOG_H
#define LOG_H
#include <QString>
#include <iostream>

struct Log {
    QString id{""};
    QString serialid{""};
    QString date{""};
    QString hour{""};
    QString actionid{""};
};

#endif // LOG_H
