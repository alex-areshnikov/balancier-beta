#include "Bank6S.h"

Bank6S::Bank6S(const uint8_t voltagePins[], const uint8_t controlPins[]) {	
	balancier = new Balancier();
	balancing = false;

	bankVoltage = new BankVoltage();

	for(size_t i=0; i<BANK_SIZE; ++i) {
		cells[i] = new Cell(voltagePins[i], controlPins[i]);
	}
};

void Bank6S::processVoltages() {
	for(size_t i=0; i<BANK_SIZE; i++) {
		cells[i]->process();
		bankVoltage->sUpdate(i, cells[i]->getRawVoltage());
		cells[i]->setProcessedVoltage(bankVoltage->s(i));		
	}
};

void Bank6S::startBalancingRoutine() {
	balancier->process(bankVoltage->getVoltages());
	float balancingVoltage = balancier->getBalancingVoltage();

	for(size_t i=0; i<BANK_SIZE; i++) {
		if(cells[i]->balance(balancingVoltage)) balancing = true;
	}
}

void Bank6S::stopBalancingRoutine() {
	balancing = false;

	for(size_t i=0; i<BANK_SIZE; i++) {
		cells[i]->stopBalance();
	}
}

bool Bank6S::isBalancing() {
	return balancing;
};

float Bank6S::getBalancingVoltage() {
	return balancier->getBalancingVoltage();
};

float* Bank6S::getVoltages() {
	return bankVoltage->getVoltages();
}

float Bank6S::totalVoltage() {
	return bankVoltage->total();
}