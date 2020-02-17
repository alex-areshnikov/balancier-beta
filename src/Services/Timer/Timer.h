#ifndef Included_Timer_H
#define Included_Timer_H

#include <Arduino.h>

class Timer {
	private:
		int duration_ms;
		unsigned long startTimestamp;
	public:
		Timer();

		void setMS(int);
		void setSeconds(int);
		bool isCompleted();
};

#endif