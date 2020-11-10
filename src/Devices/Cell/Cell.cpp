#include "Cell.h"

Cell::Cell(const uint8_t voltagePin, const uint8_t controlPin) {
	this->voltagePin = voltagePin;
	this->controlPin = controlPin;
	rawVoltage = 0;
	
	for(size_t i=0; i<HISTORY_SIZE; i++) prevReadings[i] = 0;
};

void Cell::process() {
	for(size_t i=1; i<HISTORY_SIZE; i++) prevReadings[i-1] = prevReadings[i];
	prevReadings[HISTORY_SIZE-1] = analogRead(voltagePin);

	setVoltage();
};

int Cell::getRawVoltage() {
	return(rawVoltage);
}

void Cell::setProcessedVoltage(float processedVoltage) {
	this->processedVoltage = processedVoltage;
}

bool Cell::balance(float balancingVoltage) {
	if(processedVoltage > balancingVoltage) {
		digitalWrite(controlPin, HIGH);
		return true;
	}

	return false;
}

void Cell::stopBalance() {
	digitalWrite(controlPin, LOW);
}

// private

void Cell::setVoltage() {
	float voltage = 0.0;
	for(size_t i=0; i<HISTORY_SIZE; i++) voltage += prevReadings[i];

	rawVoltage = round(voltage / HISTORY_SIZE);
};