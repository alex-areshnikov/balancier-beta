#include <Arduino.h>

class Balancier {
	private:
		uint8_t mode;
		float balancingVoltage;

	public:
		static const uint8_t AVERAGE_CELL_VOLTAGE_MODE = 0x1;
		static const uint8_t MINIMAL_CELL_VOLTAGE_MODE = 0x2;

		Balancier();
		void process(float[]);
		void calcAvgCell(float[]);
		void calcMinCell(float[]);
		float getBalancingVoltage();
};