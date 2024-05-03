#pragma once

#include <QThread>
#include <QDebug>

class PrometheusThread  : public QThread
{
	Q_OBJECT

public:
	//PrometheusThread(Minerva* minerva);
	PrometheusThread();
	~PrometheusThread();

protected:
	void run() override;

private:
	//Minerva* minerva;
};