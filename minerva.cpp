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

void Minerva::testConnection(){
    if (/*Implement Test Connection*/ 1) {
		qDebug() << "Connection failed";
    }
    else {
		qDebug() << "Connection successful";
	}
};

void Minerva::selectDataPin(int pinNumber,int dataModeNum){
    pinMode(dataPins[pinNumber], dataModeNum);
};

void Minerva::initializeGPIO() {
    wiringPiSetupGpio();
}

void Minerva::serverMode() {
    pinMode(18, OUTPUT);
	digitalWrite(18, HIGH);
}


void Minerva::clientMode() {
    Minerva::selectDataPin(0, 0);
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