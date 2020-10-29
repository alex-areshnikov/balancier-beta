#include <Arduino.h>

class Balancier {
	private:
		uint8_t mode;
		float balancingVoltage;

	public:
		static const uint8_t AVERAGE_CELL_VOLTAGE_MODE = 0x1;
		static const uint8_t MINIMAL_CELL_VOLTAGE_MODE = 0x2;
		static const uint8_t FIXED_VOLTAGE_MODE = 0x3;

		const float FIXED_VOLTAGE_TARGET = 2.5;
		const float CELL_VOLTAGE_ALLOWED_GAP = 0.05;

		Balancier();
		void process(float[]);
		void calcAvgCell(float[]);
		void calcMinCell(float[]);
		float getBalancingVoltage();
};