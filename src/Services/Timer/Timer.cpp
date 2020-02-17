#include "Timer.h"

Timer::Timer() {
	duration_ms = 0;
	startTimestamp = millis();
}

void Timer::setMS(int duration) {
	startTimestamp = millis();
	duration_ms = duration;
}

void Timer::setSeconds(int duration) {
	startTimestamp = millis();
	duration_ms = duration * 1000;
}

bool Timer::isCompleted() {
	return((startTimestamp + duration_ms) < millis());
}