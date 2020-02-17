#include "Balancier.h"

Balancier::Balancier() {
	mode = AVERAGE_CELL_VOLTAGE_MODE;
	balancingVoltage = 99.99;
};

float Balancier::getBalancingVoltage() {
	return balancingVoltage;
};

void Balancier::process(float voltages[]) {
	switch(mode) {
		case AVERAGE_CELL_VOLTAGE_MODE:
			calcAvgCell(voltages);
			break;
		case MINIMAL_CELL_VOLTAGE_MODE:
			calcMinCell(voltages);
			break;
		default:
			// should not be here
			break;
	}
};

void Balancier::calcAvgCell(float voltages[]) {
	balancingVoltage = 0.0;

	for(int i=0; i<6; i++) {
		balancingVoltage += voltages[i];
	}

	balancingVoltage /= 6;
};

void Balancier::calcMinCell(float voltages[]) {
	balancingVoltage = 99.99;

	for(int i=0; i<6; i++) {
		if(voltages[i] < balancingVoltage) balancingVoltage = voltages[i];
	}
};