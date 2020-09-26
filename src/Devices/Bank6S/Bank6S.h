#include <Arduino.h>
#include "../Cell/Cell.h"
#include "../Balancier/Balancier.h"

class Bank6S {
	private:
		static const uint8_t BANK_SIZE = 6;

		static const float IN_RESISTORS_OHMS[];
		static const float OUT_RESISTORS_OHMS[];
		static const float REF_VOLTAGE;

		uint8_t cellPins[BANK_SIZE];
		Cell *cells[BANK_SIZE];
		Balancier *balancier;
		
		float prevVoltages[BANK_SIZE];
		float rawVoltages[BANK_SIZE];
		float convertedVoltages[BANK_SIZE];
		float restoredVoltages[BANK_SIZE];
		float voltages[BANK_SIZE];

		void convertVoltages();
		void deaccumulateVoltages();
	public:
		Bank6S(const uint8_t[], const uint8_t[]);

		void processVoltages();
		void startBalancingRoutine();
		void stopBalancingRoutine();
		bool isVoltagesChanged();
		float* getVoltages();
		float totalVoltage();
		float getBalancingVoltage();
};