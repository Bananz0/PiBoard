#include "Epimetheus.h"

Epimetheus::Epimetheus(Minerva* minervaIn) : minerva(minervaIn) {
	
}

Epimetheus::~Epimetheus()
{}

void Epimetheus::receiveDataUsingThread() {
	//while (!t_stop) {
	//	minerva->receive();
	//	qDebug() << "Received Data using qThred()";
	//	QThread::sleep(100);
	//}
	minerva->runReceiveThread();
}

void Epimetheus::stop() {
	t_stop = true;
}