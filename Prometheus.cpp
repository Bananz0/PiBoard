#include "Prometheus.h"

Prometheus::Prometheus(Minerva* minervaOut) : minerva(minervaOut)
{
}

Prometheus::~Prometheus()
{}

void Prometheus::stop() {
	t_stop = true;
}

void Prometheus::sendDataUsingThread() {
	while (!t_stop) {
		minerva->send();
		qDebug() << "Have sent using qThread";
		//QThread::sleep(100);
	}

}