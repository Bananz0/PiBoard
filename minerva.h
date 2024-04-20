#ifndef MINERVA_H
#define MINERVA_H

//#include wiringPi.h
#include <QSize>

class Minerva
{
public:
    QSize winSize;
    Minerva();
    void testConnection();
    void getServerWindowSize(QSize hermesSize);
    QSize setClentWindowSize();
    void selectDataPin(int pinNumber);
    Minerva *minerva = new Minerva;
};

#endif // MINERVA_H
