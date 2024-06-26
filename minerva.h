#pragma once

#ifndef MINERVA_H
#define MINERVA_H

#include <QSize>
#include <QString>
#include <QPointF>
#include <QPen>
#include <QDataStream>
#include <QFile>
#include <QThread>
#include <QDebug>
#include <QObject>
#include <QQueue>
#include <QMutex>

class Minerva : public QObject
{
	Q_OBJECT

private:
    int dataPins[10];

public:
    Minerva();
    ~Minerva();
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
        bool operator==(const drawData& other) const {
            return startPoint == other.startPoint
                && movingPoint == other.movingPoint
                && endPoint == other.endPoint
                && clearCanvasFlag == other.clearCanvasFlag
                && drawMode == other.drawMode
                && pen == other.pen
                && windowSize == other.windowSize;
        }
    };

    QSize winSize;
    drawData* lastReceivedDataPacket = nullptr;
    drawData* lastSentDataPacket = nullptr;
    drawData* sendDataPacket = nullptr;
    drawData* receiveDataPacket = nullptr;
    QByteArray posData, penData, flagsData, sizeData, bigData, bigData_raw;
    void sendData(QByteArray data, uint pinNumber);
    QByteArray receiveData(uint pinNumber);
    QQueue<QByteArray> dataQueue, posQueue, flagsQueue, penQueue, sizeQueue;

    void sendBigData();
    void receiveBigData();
    void sendMultipleData();
    void receiveMultipleData();
    void send();
    void receive();
    void sendFile();
    void receiveFile();
    void receiveGPIO();
    void sendGPIO();
    void runSendThread();
    void runReceiveThread();
    void startReceiveThread();
    void startSendThread();
    QString testDMA();
    QString testPins();
    void sendReady(bool value, int pin);
    bool isReceiveReady(int pin);
    void sendBitUnclocked(uint s_pin, bool send);
    bool receiveBitUnclocked(uint r_pin);
    QMutex *sendLock, * recLock;
};


#endif // MINERVA_H
