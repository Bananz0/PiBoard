#pragma once

#include <QObject>
#include <QDebug>
#include "EpimetheusThread.h"
#include "minerva.h"

class Epimetheus  : public QObject
{
	Q_OBJECT

public:
	Epimetheus(Minerva* minervaIn);
	~Epimetheus();
	void receiveDataUsingThread();

	void stop();

private:
	Minerva* minerva;
	bool t_stop = false;
};
