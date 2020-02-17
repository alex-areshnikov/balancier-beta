#include "Wakeupper.h"

Wakeupper::Wakeupper(int msWakeupInterval) {
	this->msWakeupInterval = msWakeupInterval;
	this->lastWakeupTimestamp = millis();
}

bool Wakeupper::isWakeupTime() {
	unsigned long msSinceWakeup = millis() - lastWakeupTimestamp;

	if(msSinceWakeup >= msWakeupInterval) {
		lastWakeupTimestamp = millis();
		return(true);
	}

	return(false);
}