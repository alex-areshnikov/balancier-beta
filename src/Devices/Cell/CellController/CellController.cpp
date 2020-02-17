#include "CellController.h"

CellController::CellController(uint8_t controlPin) {
	timer = new Timer();
	this->controlPin = controlPin;
	currentVoltage = NONE;
	balancingVoltage = NONE;
	isBalancing = false;
}

void CellController::process() {
	isBalancing ? processBalancing() : processIdle();
}

void CellController::setVoltage(float voltage) {
	currentVoltage = voltage;
}

void CellController::balanceTo(float voltage) {
	balancingVoltage = voltage;
}

// private

void CellController::processBalancing() {
	if(!timer->isCompleted()) return;
	currentVoltage <= balancingVoltage ? turnOff() : turnOn();
}

void CellController::processIdle() {
	if(currentVoltage > balancingVoltage) turnOn();
}

void CellController::turnOn() {
	isBalancing = true;
	timer->setSeconds(MIN_BALANCING_DURATION_SECONDS);
	digitalWrite(controlPin, HIGH);
}

void CellController::turnOff() {
	isBalancing = false;
	digitalWrite(controlPin, LOW);
}