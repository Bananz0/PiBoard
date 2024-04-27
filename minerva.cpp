//Comms
#include "minerva.h"
#include <QDebug>
#include <QFile>
#include <QThread>


//enable when wiringPi is installed
#include "wiringPi.h"

//dummy defines for wiringPi
//#define OUTPUT 1
//#define INPUT 0
//#define HIGH 1
//#define LOW 0


Minerva::Minerva() {

}

void Minerva::getServerWindowSize(QSize hermesSize){
    winSize = hermesSize;
};

QSize Minerva::setClentWindowSize(){
    return winSize;
}

QString Minerva::testConnection(){
    pinMode(dataPins[0], OUTPUT);
    pinMode(dataPins[4], INPUT);

    QString connectionStatus;
    int connectionStatusNum = 0;
    int connectionStatusNumSent = 0;

    for (int i = 0; i < 4; i++){
        delay(100);
        digitalWrite(dataPins[i],1);
        delay(100);

        connectionStatusNum += digitalRead(dataPins[i+4]);
        connectionStatusNumSent += receiveBit(dataPins[i+4]);
        qDebug() << connectionStatusNum << "Send Pin: "<< i << "Receive Pin: " << i+4;
    }

    if (connectionStatusNum != 4) {
        connectionStatus = "Connection failed";
    }
    else {
        connectionStatus = "Connection successful";
    }
    qDebug() << connectionStatus;
    return connectionStatus;
}

void Minerva::selectDataPin(int pinNumber,int dataModeNum){
    pinMode(dataPins[pinNumber], dataModeNum);
};

void Minerva::initializeGPIO() {
    wiringPiSetupGpio();
}

void Minerva::serverMode() {
    selectDataPin(0, 1);
    selectDataPin(1, 1);
    selectDataPin(2, 1);
    selectDataPin(3, 1);
}


void Minerva::clientMode() {
    selectDataPin(4, 0);
    selectDataPin(5, 0);
    selectDataPin(6, 0);
    selectDataPin(7, 0);
}

//https://doc.qt.io/qt-6/qdatastream.html
void Minerva::encodeData() {
    ////Using IO for data transfer (i thnk)
    ////Open file
    //QFile file("file.dat");
    //if (!file.exists()) {
    //    qDebug() << "File does not exist";
    //}
    //file.open(QIODevice::WriteOnly);

    //QDataStream out(&data, QDataStream::WriteOnly);

    //out << drawDataPacket->startPoint;
    //out << drawDataPacket->endPoint;
    //out << drawDataPacket->movingPoint;
    //out << drawDataPacket->pen;
    //out << drawDataPacket->drawMode;
    //out << drawDataPacket->windowSize;
    //out << drawDataPacket->clearCanvasFlag;

    ////qDebug() << data.size();
    ////Write data to file
    //file.write(data);
    ////qInfo() << data.toHex();

    //simulation of sending data through individual packets through GPIO

//    QFile posFile("posData.dat");
//    posFile.open(QIODevice::WriteOnly);

//    QFile flagsFile("flagsData.dat");
//    flagsFile.open(QIODevice::WriteOnly);

//    QFile penFile("penData.dat");
//    penFile.open(QIODevice::WriteOnly);

//    QFile sizeFile("sizeData.dat");
//    sizeFile.open(QIODevice::WriteOnly);



    //Sending Individual Packets
    QDataStream posStream(&posData, QDataStream::WriteOnly);
    QDataStream flagsStream(&flagsData, QDataStream::WriteOnly);
    QDataStream penStream(&penData, QDataStream::WriteOnly);
    QDataStream sizeStream(&sizeData, QDataStream::WriteOnly);

    posStream << drawDataPacket->startPoint;
    posStream << drawDataPacket->movingPoint;
    posStream << drawDataPacket->endPoint;
    flagsStream << drawDataPacket->clearCanvasFlag;
    flagsStream << drawDataPacket->drawMode;
    penStream << drawDataPacket->pen;
    sizeStream << drawDataPacket->windowSize;

//    //Finding out the data size for transmission
//    qDebug() << posData.size() << " Position Data";
//    qDebug() << flagsData.size() << " Flags Data";
//    qDebug() << penData.size() << " Pen Data";
//    qDebug() << sizeData.size() << " Size Data";

//    posFile.write(posData);
//    flagsFile.write(flagsData);
//    penFile.write(penData);
//    sizeFile.write(sizeData);

    //Sending data (gpio)
    sendData(posData, 0);
    sendData(flagsData, 1);
    sendData(penData, 2);
    sendData(sizeData, 3);
}

void Minerva::decodeData() {
    //Open file
    //QFile file("file.dat");
    //if (!file.exists()) {
    //    qDebug() << "File does not exist";
    //}
    //file.open(QIODevice::ReadOnly);

    ////Store data from file in QByteArray
    //QByteArray data;
    //QDataStream in(&data, QDataStream::ReadOnly);

    //data = file.readAll();
    //QDataStream in(&file);  

    //in >> drawDataPacket2->startPoint;
    //in >> drawDataPacket2->endPoint;
    //in >> drawDataPacket2->movingPoint;
    //in >> drawDataPacket2->pen;
    //in >> drawDataPacket2->drawMode;
    //in >> drawDataPacket2->windowSize;
    //in >> drawDataPacket2->clearCanvasFlag;


//    //simulation of receiving data through individual packets through GPIO
//    QFile posFile("posData.dat");
//    posFile.open(QIODevice::ReadOnly);

//    QFile flagsFile("flagsData.dat");
//    flagsFile.open(QIODevice::ReadOnly);

//    QFile penFile("penData.dat");
//    penFile.open(QIODevice::ReadOnly);

//    QFile sizeFile("sizeData.dat");
//    sizeFile.open(QIODevice::ReadOnly);

//    posData = posFile.readAll();
//    flagsData = flagsFile.readAll();
//    penData = penFile.readAll();
//    sizeData = sizeFile.readAll();


    //Receiving data (gpio)
    posData = receiveData(4,48);
    flagsData = receiveData(5,5);
    penData = receiveData(6,116);
    sizeData = receiveData(7,8);

    //qDebug() << posData + flagsData + penData + sizeData;

    QByteArray arrayData = posData + flagsData + penData + sizeData;

    //Receiving Individual Packets
    QDataStream posStream(&posData, QDataStream::ReadOnly);
    QDataStream flagsStream(&flagsData, QDataStream::ReadOnly);
    QDataStream penStream(&penData, QDataStream::ReadOnly);
    QDataStream sizeStream(&sizeData, QDataStream::ReadOnly);

    posStream >> drawDataPacket2->startPoint;
    posStream >> drawDataPacket2->movingPoint;
    posStream >> drawDataPacket2->endPoint;
    flagsStream >> drawDataPacket2->clearCanvasFlag;
    flagsStream >> drawDataPacket2->drawMode;
    penStream >> drawDataPacket2->pen;
    sizeStream >> drawDataPacket2->windowSize;
}



void Minerva::sendBit(uint pinNumber,bool bitData) {
    if (bitData) {
		digitalWrite(dataPins[pinNumber], HIGH);
	}
    else {
		digitalWrite(dataPins[pinNumber], LOW);
	}
}

int Minerva::receiveBit(uint pinNumber) {
    int bitValue = digitalRead(dataPins[pinNumber]);
    delayMicroseconds(1000);
    return bitValue;
}

void Minerva::sendData(QByteArray data, uint pinNumber) {
    for (int i = 0; i < data.size(); i++) {
        uint8_t byte = static_cast<uint8_t>(data[i]);
        for (int j = 0; j < 8; j++) {
            bool bit = (byte & (1 << (7 - j))) != 0;
            sendBit(pinNumber, bit);
            delayMicroseconds(1000);
        }
        delayMicroseconds(10000);
    }
}

QByteArray Minerva::receiveData(uint pinNumber, int expectedByteSize) {
    QByteArray receivedData;
    uint8_t byteValue = 0;
    int bitCount = 0;
    bool byteStarted = false;
    unsigned long byteStartTime = 0;

    for (int i = 0; i < expectedByteSize * 8; i++) {
        int bitValue = receiveBit(pinNumber);

        if (bitValue == 1 && !byteStarted) {
            byteStarted = true;
            byteStartTime = micros(); // Record the start time of the byte
        }

        if (byteStarted) {
            unsigned long currentTime = micros();
            if (currentTime - byteStartTime > 10000) { // Adjust this value to match the delay between bytes on the sender side
                byteValue = (byteValue << 1) | bitValue;
                bitCount++;

                if (bitCount == 8) {
                    receivedData.append(byteValue);
                    byteValue = 0;
                    bitCount = 0;
                    byteStarted = false;
                }
            }
        }

        if (receivedData.size() == expectedByteSize) {
            break;
        }
    }
    qDebug() << receivedData;
    return receivedData;
}



//dummy function to comly with wiringPi not being present in windows
//void Minerva::digitalWrite(int pin, int value) {
//	//dummy function
//}
//void Minerva::pinMode(int pin, int mode) {
//	//dummy function
//}
//void Minerva::wiringPiSetupGpio() {

//}
//int Minerva::digitalRead(int pinNumber) {
//	//dummy function
//    return 0;
//}
