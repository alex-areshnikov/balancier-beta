#include "BankVoltage.h"

const float BankVoltage::IN_RESISTORS_OHMS[]  = { 0.0,  10.0, 13.75, 10.0, 10.0, 7.5 };
const float BankVoltage::OUT_RESISTORS_OHMS[] = { 20.0, 20.0, 10.0, 4.75, 3.24, 2.2 };
const float BankVoltage::REF_VOLTAGE = 4.094;

BankVoltage::BankVoltage() {
	for(uint8_t i=0; i<BANK_SIZE; i++) {
        rawVoltages[i] = 0;
        previousRawVoltages[i] = 0;
    }
}

void BankVoltage::update(float rawVoltages[]) {
    for(uint8_t i=0; i<BANK_SIZE; i++) {
        previousRawVoltages[i] = this->rawVoltages[i];
        this->rawVoltages[i] = rawVoltages[i];
    }
}

void BankVoltage::sUpdate(uint8_t index, float rawVoltage) {
    previousRawVoltages[index] = rawVoltages[index];
    rawVoltages[index] = rawVoltage;

    convert();
    deaccumulate();
}

float BankVoltage::s(uint8_t index) {
    return voltages[index];
}

float* BankVoltage::getVoltages() {
    return voltages;
}

bool BankVoltage::changed() {
	for(uint8_t i=0; i<BANK_SIZE; i++) {
		if(previousRawVoltages[i] != rawVoltages[i]) return true;
	}

	return false;
};

bool BankVoltage::sChanged(uint8_t index) {
    return rawVoltages[index] != previousRawVoltages[index];
}

float BankVoltage::total() {
    return restoredVoltages[BANK_SIZE-1];
}

// private

void BankVoltage::convert() {
	for(size_t i=0; i<BANK_SIZE; i++) {
		convertedVoltages[i] = rawVoltages[i] * REF_VOLTAGE / 1023;
    	restoredVoltages[i] = (convertedVoltages[i] * (IN_RESISTORS_OHMS[i] + OUT_RESISTORS_OHMS[i])) / OUT_RESISTORS_OHMS[i];
	}
};

void BankVoltage::deaccumulate() {
	voltages[0] = restoredVoltages[0];

	for(size_t i=1; i<BANK_SIZE; i++) {
		voltages[i] = restoredVoltages[i] - restoredVoltages[i-1];
	}
};