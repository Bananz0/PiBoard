#include "PrometheusThread.h"


//PrometheusThread::PrometheusThread(Minerva* minerva) : minerva(minerva) {
//
//}

PrometheusThread::PrometheusThread(){
}

PrometheusThread::~PrometheusThread()
{}

void PrometheusThread::run(){
	//minerva->receive();
	//QThread::sleep(5);
	qDebug() << "Receiver Thread has started";
}
