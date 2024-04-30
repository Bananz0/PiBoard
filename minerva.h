#ifndef MINERVA_H
#define MINERVA_H

#include <QSize>
#include <QString>
#include <QPointF>
#include <QPen>
#include <QDataStream>
#include <QFile>
class Minerva
{
private:
    int dataPins[10];
public:
    Minerva();
    ~Minerva();
    QString testConnection();
    void selectDataPin(int pinNumber, int dataModeNum);
    void getServerWindowSize(QSize hermesSize);
    QSize setClentWindowSize();
    void initializeGPIO();
    void serverMode();
    void clientMode();
    void encodeData();
    void decodeData();
    
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

    QSize winSize;
    drawData* sendDataPacket;
    drawData* receiveDataPacket;
    QByteArray posData, penData, flagsData, sizeData;

    void sendBit(uint pinNumber, bool bitData);
    int receiveBit(uint pinNumber);
    void sendData(QByteArray data, uint pinNumber);
    QByteArray receiveData(uint pinNumber,int expectedByteSize);
};

#endif // MINERVA_H
