#include "EpimetheusThread.h"

//EpimetheusThread::EpimetheusThread(Minerva* minerva) : minerva(minerva)
//{
//}

EpimetheusThread::EpimetheusThread() {

}

EpimetheusThread::~EpimetheusThread(){

}

void EpimetheusThread::run(){
	//minerva->receive();
	//QThread::sleep(5);
	qDebug() << "Receiver Thread has started";
}
