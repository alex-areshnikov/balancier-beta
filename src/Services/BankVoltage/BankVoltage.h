#ifndef Included_BankVoltage_H
#define Included_BankVoltage_H

#include <Arduino.h>

class BankVoltage {
	private:
        static const float IN_RESISTORS_OHMS[];
        static const float OUT_RESISTORS_OHMS[];
        static const float REF_VOLTAGE;

        static const uint8_t BANK_SIZE = 6;
        float rawVoltages[BANK_SIZE];
        float previousRawVoltages[BANK_SIZE];
        float convertedVoltages[BANK_SIZE];
        float restoredVoltages[BANK_SIZE];
        float voltages[BANK_SIZE];

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