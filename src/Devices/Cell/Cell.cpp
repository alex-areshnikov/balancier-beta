#include "Cell.h"

const int Cell::HISTORY_SIZE = 10;

Cell::Cell(const uint8_t voltagePin, const uint8_t controlPin) {
	this->voltagePin = voltagePin;
	controller = new CellController(controlPin);
	voltage = 0;
	
	for(size_t i=0; i<HISTORY_SIZE; i++) prevReadings[i] = 0;
};

void Cell::process(float balancingVoltage) {
	for(size_t i=1; i<HISTORY_SIZE; i++) prevReadings[i-1] = prevReadings[i];
	prevReadings[HISTORY_SIZE-1] = analogRead(voltagePin);

	setVoltage();
	controller->setVoltage(voltage);
	controller->balanceTo(balancingVoltage);
};

int Cell::getVoltage() {
	return(voltage);
}

// private

void Cell::setVoltage() {
	float voltage = 0.0;
	for(size_t i=0; i<HISTORY_SIZE; i++) voltage += prevReadings[i];

	this->voltage = round(voltage / HISTORY_SIZE);
};