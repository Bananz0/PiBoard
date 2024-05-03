#pragma once

#include <QObject>
#include <QDebug>
#include "PrometheusThread.h"
#include "minerva.h"

class Prometheus  : public QObject
{
	Q_OBJECT

public:
	Prometheus(Minerva* minervaOut);
	~Prometheus();

public slots:
	void sendDataUsingThread();
	void stop();

private: 
	Minerva* minerva;
	bool t_stop = false;
};
