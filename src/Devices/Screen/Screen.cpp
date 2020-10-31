#include "Screen.h"

Screen::Screen(Adafruit_SSD1306 *display) {
	this->display = display;

  for(uint8_t i=0; i<BANK_SIZE; i++) {
    voltages[i] = 0;
  }
}

void Screen::initialize() {
    display->clearDisplay();
    // display->setTextSize(2);      // Normal 1:1 pixel scale
    // display->setTextColor(SSD1306_WHITE); // Draw white text
    // display->setCursor(0, 0);     // Start at top-left corner
    // display->cp437(true);         // Use full 256 char 'Code Page 437' font

    // display->println("SMART");
    // display->println("BALANCER");

    display->drawPixel(10, 10, SSD1306_WHITE);

    display->display();

    // display->setTextSize(1);
}

void Screen::setVoltages(float voltages[]) {
  this->voltages = voltages;
  render();
}

void Screen::renderVoltages() {  
  char buf[8];
  uint8_t xOffsets[] = {0, 40, 80, 0, 40, 80};
  uint8_t yOffsets[] = {10, 10, 10, 20, 20, 20};

  for(uint8_t i=0; i<BANK_SIZE; i++) {
    display->setCursor(xOffsets[i], yOffsets[i]);
    display->write("0.00v");
  }  
}

void Screen::render() {
  display->clearDisplay();
  // renderBalancingLine();
  renderVoltages();
  display->display();
}