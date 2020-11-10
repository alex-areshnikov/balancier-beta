#include <Arduino.h>
#include <math.h>

class Cell {
	private:
		static const int HISTORY_SIZE = 10;

		int prevReadings[10];
		uint8_t voltagePin;
		uint8_t controlPin;
		int rawVoltage;
		float processedVoltage;

		void setVoltage();
	public:
		Cell(const uint8_t, const uint8_t);
		void process();
		bool balance(float);
		void stopBalance();
		int getRawVoltage();
		void setProcessedVoltage(float);
};
