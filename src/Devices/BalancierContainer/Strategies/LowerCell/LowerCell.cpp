#include "LowerCell.h"

Balancier::Strategies::LowerCell::LowerCell(std::vector<float> voltages) {
	this->voltages = voltages;
}

float Balancier::Strategies::LowerCell::balanceVoltage() {
	return *(std::min_element(voltages.begin(), voltages.end()));
}