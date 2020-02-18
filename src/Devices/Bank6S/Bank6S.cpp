#include "Bank6S.h"

const float Bank6S::IN_RESISTORS_OHMS[] = { 0, 5.1, 5.1, 9.925, 9.979, 14.789 };
const float Bank6S::OUT_RESISTORS_OHMS[] = { 5.1, 5.1, 5.1, 5.1, 5.1, 5.1 };
const float Bank6S::REF_VOLTAGE = 5;

Bank6S::Bank6S(const uint8_t voltagePins[], const uint8_t controlPins[]) {	
	balancier = new Balancier();

	for(size_t i=0; i<BANK_SIZE; ++i) {
		cells[i] = new Cell(voltagePins[i], controlPins[i]);
		rawVoltages[i] = 0;
	}
};

void Bank6S::process() {
	for(size_t i=0; i<BANK_SIZE; i++) {
		prevVoltages[i] = rawVoltages[i];
	}	

	for(size_t i=0; i<BANK_SIZE; i++) {
		cells[i]->process(balancier->getBalancingVoltage());
		cells[i]->setProcessedVoltage(voltages[i]);
		rawVoltages[i] = cells[i]->getVoltage();
	}
	
	if(isVoltagesChanged()) {
		convertVoltages();
		deaccumulateVoltages();
		balancier->process(voltages);
	}
};

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
		convertedVoltages[i] = rawVoltages[i] * REF_VOLTAGE / 1024;
    restoredVoltages[i] = (convertedVoltages[i] * (IN_RESISTORS_OHMS[i] + OUT_RESISTORS_OHMS[i])) / OUT_RESISTORS_OHMS[i];
	}
};

void Bank6S::deaccumulateVoltages() {
	voltages[0] = restoredVoltages[0];

	for(size_t i=1; i<BANK_SIZE; i++) {
		voltages[i] = restoredVoltages[i] - restoredVoltages[i-1];
	}
};