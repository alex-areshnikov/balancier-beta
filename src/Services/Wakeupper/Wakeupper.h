#ifndef Included_Wakeupper_H
#define Included_Wakeupper_H

#include <Arduino.h>

class Wakeupper {
	private:
		unsigned int msWakeupInterval;
		unsigned long lastWakeupTimestamp;
		
		unsigned long currentMillis();

	public:
		Wakeupper(int);
		bool isWakeupTime();
};

#endif