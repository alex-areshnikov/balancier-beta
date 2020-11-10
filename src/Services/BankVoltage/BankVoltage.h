#ifndef Included_BankVoltage_H
#define Included_BankVoltage_H

#include <Arduino.h>

class BankVoltage {
	private:
                static const uint8_t BANK_SIZE = 6;
                float rawVoltages[BANK_SIZE];
                float previousRawVoltages[BANK_SIZE];
                float convertedVoltages[BANK_SIZE];
                float restoredVoltages[BANK_SIZE];
                float voltages[BANK_SIZE];

                static constexpr float IN_RESISTORS_OHMS[]  = { 0.0,  10.0, 13.65, 9.95, 9.9, 7.5 };
                static constexpr float OUT_RESISTORS_OHMS[] = { 20.0, 20.0, 10.0, 4.75, 3.24, 2.2 };
                static const float REF_VOLTAGE = 4.094;

                void convert();
                void deaccumulate();
	public:
                BankVoltage();

                float* getVoltages();
                void update(float[]);
                void sUpdate(uint8_t, float);
                float s(uint8_t);
                bool changed();
                bool sChanged(uint8_t);
                float total();

                
};

#endif