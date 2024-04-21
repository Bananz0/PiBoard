#ifndef MINERVA_H
#define MINERVA_H

#include <QSize>

class Minerva
{
private:
    int dataPins[10] = {25,28,24,27,22,26,30,31,14,10};
public:
    QSize winSize;
    Minerva();
    void testConnection();
    void selectDataPin(int pinNumber, int dataModeNum);
    void getServerWindowSize(QSize hermesSize);
    QSize setClentWindowSize();
    void initializeGPIO();
    void serverMode();
    void clientMode();

    

    //dummy function to comly with wiringPi
    void digitalWrite(int pin, int value);
    void pinMode(int pin, int mode);
    void wiringPiSetupGpio();
};

#endif // MINERVA_H
