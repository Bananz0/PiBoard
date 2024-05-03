#include "Epimetheus.h"

Epimetheus::Epimetheus(Minerva* minervaIn) : minerva(minervaIn) {
	
}

Epimetheus::~Epimetheus()
{}

void Epimetheus::receiveDataUsingThread() {
	minerva->runReceiveThread();
}

void Epimetheus::stop() {
	t_stop = true;
}