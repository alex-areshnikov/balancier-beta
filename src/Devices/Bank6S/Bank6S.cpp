#include "Bank6S.h"

const float Bank6S::IN_RESISTORS_OHMS[]  = { 0.0,  10.0, 13.65, 9.95, 9.9, 7.5 };
const float Bank6S::OUT_RESISTORS_OHMS[] = { 20.0, 20.0, 10.0, 4.75, 3.24, 2.2 };
const float Bank6S::REF_VOLTAGE = 4.094;

Bank6S::Bank6S(const uint8_t voltagePins[], const uint8_t controlPins[]) {	
	balancier = new Balancier();

	for(size_t i=0; i<BANK_SIZE; ++i) {
		cells[i] = new Cell(voltagePins[i], controlPins[i]);
		rawVoltages[i] = 0;
	}
};

void Bank6S::processVoltages() {
	for(size_t i=0; i<BANK_SIZE; i++) {
		prevVoltages[i] = rawVoltages[i];
	}	

	for(size_t i=0; i<BANK_SIZE; i++) {
		cells[i]->process();
		cells[i]->setProcessedVoltage(voltages[i]);
		rawVoltages[i] = cells[i]->getVoltage();
	}
	
	if(isVoltagesChanged()) {
		convertVoltages();
		deaccumulateVoltages();
	}
};

void Bank6S::startBalancingRoutine() {
	balancier->process(voltages);
	float balancingVoltage = balancier->getBalancingVoltage();

	for(size_t i=0; i<BANK_SIZE; i++) {
		cells[i]->balance(balancingVoltage);
	}
}

void Bank6S::stopBalancingRoutine() {
	for(size_t i=0; i<BANK_SIZE; i++) {
		cells[i]->stopBalance();
	}
}

bool Bank6S::isVoltagesChanged() {
	for(size_t i=0; i<BANK_SIZE; i++) {
		if(prevVoltages[i] != rawVoltages[i]) return true;
	}

	return false;
};

float* Bank6S::getVoltages() {
	return voltages;
};

float Bank6S::getBalancingVoltage() {
	return balancier->getBalancingVoltage();
};

float Bank6S::totalVoltage() {
	return restoredVoltages[BANK_SIZE-1];
}

// private

void Bank6S::convertVoltages() {
	for(size_t i=0; i<BANK_SIZE; i++) {
		convertedVoltages[i] = rawVoltages[i] * REF_VOLTAGE / 1023;
    restoredVoltages[i] = (convertedVoltages[i] * (IN_RESISTORS_OHMS[i] + OUT_RESISTORS_OHMS[i])) / OUT_RESISTORS_OHMS[i];
	}
};

void Bank6S::deaccumulateVoltages() {
	voltages[0] = restoredVoltages[0];

	for(size_t i=1; i<BANK_SIZE; i++) {
		voltages[i] = restoredVoltages[i] - restoredVoltages[i-1];
	}
};