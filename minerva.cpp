//Comms
#include "minerva.h"
#include <QDebug>
#include <QFile>
#include <QThread>


//enable when wiringPi is installed
#include "wiringPiFake.h"

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

QString Minerva::testConnection() {
    int outputPin = dataPins[0]; 
    int inputPin = dataPins[4];   

    pinMode(outputPin, OUTPUT);
    pinMode(inputPin, INPUT);

    // Set output pin HIGH
    digitalWrite(outputPin, HIGH);
    delay(100); 

    int inputValue = digitalRead(inputPin);


    if (inputValue == HIGH) {
        return "Connection successful";
    }
    else {
        return "Connection failed";
    }
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
	int bitValue;
	bitValue = digitalRead(dataPins[pinNumber]);
	qDebug() << "Received bit: " << bitValue;
    return bitValue;
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

QByteArray Minerva::receiveData(uint pinNumber, int expectedByteSize)
{
    QByteArray receivedData;
    int bitValue = 0;
    int byteValue = 0;
    int bitCount = 0;
    int currentBitValue = 0;
    while (true) {
        bitValue = digitalRead(dataPins[pinNumber]);
        if (bitValue != currentBitValue){
             qDebug() << "Bit has changed from " << currentBitValue << " to " <<bitValue;
        }
        currentBitValue = bitValue;
        if (bitValue == 1) {
            byteValue |= (1 << bitCount);
        }
        bitCount++;
        if (bitCount == 8) {
            receivedData.append(byteValue);
            byteValue = 0;
            bitCount = 0;
        }
        if (receivedData.size() == expectedByteSize) {
            break;
        }
    }
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
