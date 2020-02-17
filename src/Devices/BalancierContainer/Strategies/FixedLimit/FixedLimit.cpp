#include "FixedLimit.h"

Balancier::Strategies::FixedLimit::FixedLimit(float limit) {
	this->limit = limit;
}

float Balancier::Strategies::FixedLimit::balanceVoltage() {
	return limit;
}