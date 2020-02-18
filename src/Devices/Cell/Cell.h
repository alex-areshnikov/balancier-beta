#include <Arduino.h>
#include <math.h>

#include "CellController/CellController.h"

class Cell {
	private:
		static const int HISTORY_SIZE;

		int prevReadings[10];
		int voltagePin;
		CellController *controller;
		int voltage;
		float processedVoltage;

		void setVoltage();
	public:
		Cell(const uint8_t, const uint8_t);
		void process(float);
		int getVoltage();
		void setProcessedVoltage(float);
};
