//Comms
#include "minerva.h"
#include <QDebug>
#include <QFile>
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
    //TODO: Implement actual connection test
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

	//Minerva::selectDataPin(4, 0);
	//Minerva::selectDataPin(5, 0);
	//Minerva::selectDataPin(6, 0);
	//Minerva::selectDataPin(7, 0);

	//Reserved for common ground
	Minerva::selectDataPin(8, 0);
	Minerva::selectDataPin(9, 0);
}


void Minerva::clientMode() {
    //Minerva::selectDataPin(0, 0);
    //Minerva::selectDataPin(1, 0);
    //Minerva::selectDataPin(2, 0);
    //Minerva::selectDataPin(3, 0);

    //Minerva::selectDataPin(4, 1);
    //Minerva::selectDataPin(5, 1);
    //Minerva::selectDataPin(6, 1);
    //Minerva::selectDataPin(7, 1);

    Minerva::selectDataPin(4, 0);
    Minerva::selectDataPin(5, 0);
    Minerva::selectDataPin(6, 0);
    Minerva::selectDataPin(7, 0);

    //Reserved for common ground
    Minerva::selectDataPin(8, 0);
    Minerva::selectDataPin(9, 0);    
}

//https://doc.qt.io/qt-6/qdatastream.html
void Minerva::encodeData() {

    //Using IO for data transfer (i thnk)
    //Open file
    QFile file("file.dat");
    if (!file.exists()) {
        qDebug() << "File does not exist";
    }
    file.open(QIODevice::WriteOnly);

    QDataStream out(&data, QDataStream::WriteOnly);

    out << drawDataPacket->startPoint;
    out << drawDataPacket->endPoint;
    out << drawDataPacket->movingPoint;
    out << drawDataPacket->pen;
    out << drawDataPacket->drawMode;
    out << drawDataPacket->windowSize;
    out << drawDataPacket->clearCanvasFlag;

    //qDebug() << data.size();
    //Write data to file
    file.write(data);
    //qInfo() << data.toHex();

    //simulation of sending data through individual packets through GPIO

    QFile posFile("posData.dat");
    posFile.open(QIODevice::WriteOnly);

    QFile flagsFile("flagsData.dat");
    flagsFile.open(QIODevice::WriteOnly);

    QFile penFile("penData.dat");
    penFile.open(QIODevice::WriteOnly);

    QFile sizeFile("sizeData.dat");
    sizeFile.open(QIODevice::WriteOnly);

    posFile.write(posData);
    flagsFile.write(flagsData);
    penFile.write(penData);
    sizeFile.write(sizeData);



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

}

void Minerva::decodeData() {
    //Open file
    QFile file("file.dat");
    if (!file.exists()) {
        qDebug() << "File does not exist";
    }
    file.open(QIODevice::ReadOnly);

    //Store data from file in QByteArray
    QByteArray data;
    QDataStream in(&data, QDataStream::ReadOnly);

    data = file.readAll();
    //QDataStream in(&file);  

    //in >> drawDataPacket2->startPoint;
    //in >> drawDataPacket2->endPoint;
    //in >> drawDataPacket2->movingPoint;
    //in >> drawDataPacket2->pen;
    //in >> drawDataPacket2->drawMode;
    //in >> drawDataPacket2->windowSize;
    //in >> drawDataPacket2->clearCanvasFlag;


    //simulation of receiving data through individual packets through GPIO
    QFile posFile("posData.dat");
    posFile.open(QIODevice::ReadOnly);

    QFile flagsFile("flagsData.dat");
    flagsFile.open(QIODevice::ReadOnly);

    QFile penFile("penData.dat");
    penFile.open(QIODevice::ReadOnly);

    QFile sizeFile("sizeData.dat");
    sizeFile.open(QIODevice::ReadOnly);

    posData = posFile.readAll();
    flagsData = flagsFile.readAll();
    penData = penFile.readAll();
    sizeData = sizeFile.readAll();


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