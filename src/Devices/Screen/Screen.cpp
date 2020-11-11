#include "Screen.h"

Screen::Screen() {	
  for(uint8_t i=0; i<BANK_SIZE; i++) {    
    voltages[i] = 0;
  }

  uint8_t canvasBuffer[32];
  canvas = new NanoCanvas(32, 8, canvasBuffer);
}

void Screen::initialize() {
}

void Screen::setVoltages(float voltages[]) {
  this->voltages = voltages;
}

void Screen::render() {
  renderVoltages();
}

void Screen::renderVoltages() {  
  uint8_t xOffsets[] = {0, 48, 96, 0, 48, 96};
  uint8_t yOffsets[] = {2, 2, 2, 4, 4, 4};
  
  char charBuffer[8];

  for(uint8_t i=0; i<BANK_SIZE; i++) {
    (String(voltages[i], 2)+"v").toCharArray(charBuffer, 8);

    canvas->clear();
    canvas->printFixed(0, 0, charBuffer);
    canvas->blt(xOffsets[i], yOffsets[i]);  
  }  
}