//Comms
#include "minerva.h"
#include <QDebug>
#include <QFile>
#include <condition_variable> 
#include <QMutex> 
#include <QQueue> 
#include <QThread>

//enable when wiringPi is installed
//#include "wiringPi.h"

//dummy defines for wiringPi
#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0


Minerva::Minerva() {

}

void Minerva::getServerWindowSize(QSize hermesSize){
    winSize = hermesSize;
};

QSize Minerva::setClentWindowSize(){
    return winSize;
}

QString Minerva::testConnection(){
    QString connectionStatus;
    int connectionStatusNum;
    
    //generate either 0 or 1
    connectionStatusNum = rand() % 2;

    if (connectionStatusNum) {
		connectionStatus = "Connection failed";
    }
    else {
        connectionStatus = "Connection successful";
	}
    qDebug() << connectionStatus;
    return connectionStatus;
};

void Minerva::selectDataPin(int pinNumber,int dataModeNum){
    pinMode(dataPins[pinNumber], dataModeNum);
};

void Minerva::initializeGPIO() {
    wiringPiSetupGpio();
}

void Minerva::serverMode() {
    Minerva::selectDataPin(0, 1);
	Minerva::selectDataPin(1, 1);
	Minerva::selectDataPin(2, 1);
	Minerva::selectDataPin(3, 1);

	Minerva::selectDataPin(4, 0);
	Minerva::selectDataPin(5, 0);
	Minerva::selectDataPin(6, 0);
	Minerva::selectDataPin(7, 0);

	//Reserved for common ground
	Minerva::selectDataPin(8, 0);
	Minerva::selectDataPin(9, 0);
}


void Minerva::clientMode() {
    Minerva::selectDataPin(0, 0);
    Minerva::selectDataPin(1, 0);
    Minerva::selectDataPin(2, 0);
    Minerva::selectDataPin(3, 0);

    Minerva::selectDataPin(4, 1);
    Minerva::selectDataPin(5, 1);
    Minerva::selectDataPin(6, 1);
    Minerva::selectDataPin(7, 1);

    //Reserved for common ground
    Minerva::selectDataPin(8, 0);
    Minerva::selectDataPin(9, 0);    
}


//https://doc.qt.io/qt-6/qdatastream.html
void Minerva::encodeData(){
    QByteArray posData;
    QByteArray penData;
    QByteArray flagsData;
    QByteArray sizeData;

    QDataStream posStream(&posData, QDataStream::WriteOnly);
    QDataStream penStream(&penData, QDataStream::WriteOnly);
    QDataStream flagsStream(&flagsData, QDataStream::WriteOnly);
    QDataStream sizeStream(&sizeData, QDataStream::WriteOnly);


    posStream << drawDataPacket->startPoint;
    posStream << drawDataPacket->endPoint;
    posStream << drawDataPacket->movingPoint;
    penStream << drawDataPacket->pen;
    flagsStream << drawDataPacket->drawMode;
    flagsStream << drawDataPacket->clearCanvasFlag;
    sizeStream << drawDataPacket->windowSize;
    
    qDebug() << "posData: " << posData;
    qDebug() << "penData: " << penData;
    qDebug() << "flagsData: " << flagsData;
    qDebug() << "sizeData: " << sizeData;
}

void Minerva::decodeData(){
    QByteArray posData;
    QByteArray penData;
    QByteArray flagsData;
    QByteArray sizeData;

    QDataStream posStream(&posData, QDataStream::WriteOnly);
    QDataStream penStream(&penData, QDataStream::WriteOnly);
    QDataStream flagsStream(&flagsData, QDataStream::WriteOnly);
    QDataStream sizeStream(&sizeData, QDataStream::WriteOnly);


    posStream << drawDataPacket->startPoint;
    posStream << drawDataPacket->endPoint;
    posStream << drawDataPacket->movingPoint;
    penStream << drawDataPacket->pen;
    flagsStream << drawDataPacket->drawMode;
    flagsStream << drawDataPacket->clearCanvasFlag;
    sizeStream << drawDataPacket->windowSize;

    qDebug() << "Received posData: " << posData;
    qDebug() << "Received penData: " << penData;
    qDebug() << "Received flagsData: " << flagsData;
    qDebug() << "Received sizeData: " << sizeData;
}



void Minerva::sendBit(uint pinNumber,bool bitData) {

    if (bitData) {
		digitalWrite(dataPins[pinNumber], HIGH);
	}
    else {
		digitalWrite(dataPins[pinNumber], LOW);
	}


    digitalWrite(dataPins[pinNumber],LOW);
    digitalWrite(dataPins[pinNumber], HIGH);
	digitalWrite(dataPins[pinNumber], LOW);    
}

void Minerva::receiveBit(uint pinNumber) {
	int bitValue;
	bitValue = digitalRead(dataPins[pinNumber]);
	qDebug() << "Received bit: " << bitValue;
}

void Minerva::sendData(QByteArray data, uint pinNumber) {
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < 8; j++) {
            if (data[i] & (1 << j)) {
				sendBit(pinNumber,0);
			}
            else {
				sendBit(pinNumber,1);
			}
		}
	}
}

QByteArray Minerva::receiveData(uint pinNumber) {
	QByteArray receivedData;
	int bitValue;
	int byteValue = 0;
	int bitCount = 0;

    while (true) {
		bitValue = digitalRead(dataPins[pinNumber]);
        if (bitValue == 1) {
			byteValue |= (1 << bitCount);
		}
		bitCount++;
        if (bitCount == 8) {
			receivedData.append(byteValue);
			byteValue = 0;
			bitCount = 0;
		}
	}
	return receivedData;
}


//dummy function to comly with wiringPi not being present in windows
void Minerva::digitalWrite(int pin, int value) {
	//dummy function
}
void Minerva::pinMode(int pin, int mode) {
	//dummy function
}
void Minerva::wiringPiSetupGpio() {

}
int Minerva::digitalRead(int pinNumber) {
	//dummy function
    return 0;
}