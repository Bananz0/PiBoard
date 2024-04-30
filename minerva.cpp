//Comms
#include "minerva.h"
#include <QDebug>
#include <QFile>
#include <QThread>


#define BITSENDDELAY 3
#define BITRECEIVEDELAY 3
#define BYTESENDDELAY 20
#define BYTERECEIVEDELAY 20
 
#include "wiringPiFake.h"




Minerva::Minerva() {
    //initialize GPIO
	initializeGPIO();
	//set send pins
	dataPins[0] = 0;
	dataPins[1] = 1;
	dataPins[2] = 2;
	dataPins[3] = 3;
    //set receive pins
	dataPins[4] = 4;
	dataPins[5] = 5;
	dataPins[6] = 6;
	dataPins[7] = 7;

    //set misc pins
    dataPins[8] = 8;
    dataPins[9] = 9;
   
	//set window size
	winSize = QSize(800, 600);
	//initialize drawDataPacket
	sendDataPacket = new drawData;
	receiveDataPacket = new drawData;
	//initialize data packets
	posData = QByteArray();
	flagsData = QByteArray();
	penData = QByteArray();
	sizeData = QByteArray();
}

Minerva::~Minerva() {
	delete sendDataPacket;
	delete receiveDataPacket;
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
    QFile posFile("posData.dat");
    posFile.open(QIODevice::WriteOnly);

    QFile flagsFile("flagsData.dat");
    flagsFile.open(QIODevice::WriteOnly);

    QFile penFile("penData.dat");
    penFile.open(QIODevice::WriteOnly);

    QFile sizeFile("sizeData.dat");
    sizeFile.open(QIODevice::WriteOnly);



    //Sending Individual Packets
    QDataStream posStream(&posData, QDataStream::WriteOnly);
    QDataStream flagsStream(&flagsData, QDataStream::WriteOnly);
    QDataStream penStream(&penData, QDataStream::WriteOnly);
    QDataStream sizeStream(&sizeData, QDataStream::WriteOnly);

    posStream << sendDataPacket->startPoint;
    posStream << sendDataPacket->movingPoint;
    posStream << sendDataPacket->endPoint;
    flagsStream << sendDataPacket->clearCanvasFlag;
    flagsStream << sendDataPacket->drawMode;
    penStream << sendDataPacket->pen;
    sizeStream << sendDataPacket->windowSize;

//    //Finding out the data size for transmission
//    qDebug() << posData.size() << " Position Data";
//    qDebug() << flagsData.size() << " Flags Data";
//    qDebug() << penData.size() << " Pen Data";
//    qDebug() << sizeData.size() << " Size Data";

    posFile.write(posData);
    flagsFile.write(flagsData);
    penFile.write(penData);
    sizeFile.write(sizeData);

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


    //Receiving data (gpio)
    //posData = receiveData(4,48);
    //flagsData = receiveData(5,5);
    //penData = receiveData(6,116);
    //sizeData = receiveData(7,8);

    //qDebug() << posData + flagsData + penData + sizeData;


    //Receiving Individual Packets
    QDataStream posStream(&posData, QDataStream::ReadOnly);
    QDataStream flagsStream(&flagsData, QDataStream::ReadOnly);
    QDataStream penStream(&penData, QDataStream::ReadOnly);
    QDataStream sizeStream(&sizeData, QDataStream::ReadOnly);

    posStream >> receiveDataPacket->startPoint;
    posStream >> receiveDataPacket->movingPoint;
    posStream >> receiveDataPacket->endPoint;
    flagsStream >> receiveDataPacket->clearCanvasFlag;
    flagsStream >> receiveDataPacket->drawMode;
    penStream >> receiveDataPacket->pen;
    sizeStream >> receiveDataPacket->windowSize;
}



void Minerva::sendBit(uint pinNumber,bool bitData) {
    if (bitData) {
		digitalWrite(dataPins[pinNumber], HIGH);
	}
    else {
		digitalWrite(dataPins[pinNumber], LOW);
	}
    delayMicroseconds( BITSENDDELAY );
}

int Minerva::receiveBit(uint pinNumber) {
    int bitValue = digitalRead(dataPins[pinNumber]);
    delayMicroseconds( BITRECEIVEDELAY );
    return bitValue;
}

void Minerva::sendData(QByteArray data, uint pinNumber) {


}

QByteArray Minerva::receiveData(uint pinNumber, int expectedByteSize) {
    QByteArray receivedData;


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
