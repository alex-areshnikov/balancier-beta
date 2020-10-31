#ifndef Included_Screen_H
#define Included_Screen_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class Screen {
	private:
        static const uint8_t BANK_SIZE = 6;       

        Adafruit_SSD1306 *display;

        float *voltages;

        void render();
        void renderVoltages();
	public:
		Screen(Adafruit_SSD1306*);

        void initialize();
        void setVoltages(float[]);
};

#endif