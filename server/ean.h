#ifndef EAN_H
#define EAN_H

#include <QString>

class Ean {
private:


public:
    QString calculateCheckSum(QString eanCode);
    QString getEanCode(QString productCode);
};

#endif // EAN_H
