#ifndef IOUTILS_H
#define IOUTILS_H

#include <QObject>

class IOUtils : public QObject
{
    Q_OBJECT
public:
    static const bool IS_BIG_ENDIAN;
    static void orderData(unsigned char *pData, unsigned int len);
};

#endif // IOUTILS_H
