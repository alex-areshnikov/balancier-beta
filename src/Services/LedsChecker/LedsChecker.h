#ifndef Included_LedsChecker_H
#define Included_LedsChecker_H

#include <Arduino.h>

class LedsChecker {
	private:
        static const uint8_t BANK_SIZE = 6;
        static const uint8_t CELL_JUMP_DELAY = 50;
        static const uint16_t ALL_CELLS_ON_DELAY = 500;

	public:
		LedsChecker();

		void call(const uint8_t[]);
};

#endif