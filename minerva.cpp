//Comms
#include "minerva.h"
#include <QDebug>

//enable when wiringPi is installed
//#include "wiringPi.h"
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

//dummy function to comly with wiringPi
void Minerva::digitalWrite(int pin, int value) {
	//dummy function
}
void Minerva::pinMode(int pin, int mode) {
	//dummy function
}
void Minerva::wiringPiSetupGpio() {

}