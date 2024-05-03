#pragma once

#include <QThread>
#include <QDebug>


class EpimetheusThread : public QThread
{
	Q_OBJECT

public:
	EpimetheusThread();
	~EpimetheusThread();

protected:
	void run() override;

private:
};