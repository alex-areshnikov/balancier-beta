#ifndef Included_Screen_H
#define Included_Screen_H

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "nano_gfx.h"

class Screen {
	private:
                static const uint8_t BANK_SIZE = 6;    

                NanoCanvas *canvas;
                float *voltages;
                
                void renderVoltages();

	public:
                Screen();
                void initialize();
                void setVoltages(float[]);
                void render();
};

#endif