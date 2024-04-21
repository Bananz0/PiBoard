#ifndef MINERVA_H
#define MINERVA_H

#include <QSize>
#include <QString>
#include <QPointF>
#include <QPen>

class Minerva
{
private:
    int dataPins[10] = {25,28,24,27,22,26,30,31,14,10};
public:
    QSize winSize;
    Minerva();
    QString testConnection();
    void selectDataPin(int pinNumber, int dataModeNum);
    void getServerWindowSize(QSize hermesSize);
    QSize setClentWindowSize();
    void initializeGPIO();
    void serverMode();
    void clientMode();

    class drawData {
    public:
        QPointF startPoint;
        QPointF endPoint;
        QPointF movingPoint;
        QPen pen;
        int drawMode = 1;
        QSize windowSize;
        bool clearCanvasFlag = false;

        //https://doc.qt.io/qt-6/qpen.html#capStyle
        drawData() {}
    };

    drawData* drawDataPacket = new drawData;
    

    //dummy function to comly with wiringPi
    void digitalWrite(int pin, int value);
    void pinMode(int pin, int mode);
    void wiringPiSetupGpio();
};

#endif // MINERVA_H
