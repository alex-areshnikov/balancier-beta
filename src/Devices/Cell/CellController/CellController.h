#include <Arduino.h>
#include "Services/Timer/Timer.h"

class CellController {
		const uint8_t NONE = -1;
		const uint8_t MIN_BALANCING_DURATION_SECONDS = 60;

		Timer *timer;
		uint8_t controlPin;
		float currentVoltage;
		float balancingVoltage;
		bool isBalancing;

		void processBalancing();
		void processIdle();
		void turnOn();
		void turnOff();
	public:
		CellController(uint8_t);

		void process();
		void setVoltage(float);
		void balanceTo(float);
};