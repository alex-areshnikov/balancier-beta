#include "LedsChecker.h"

LedsChecker::LedsChecker() {
	
}

void LedsChecker::call(const uint8_t controlPins[]) {
  for(int i=0; i<BANK_SIZE; i++) {
    digitalWrite(controlPins[i], HIGH);   
    delay(CELL_JUMP_DELAY);                    
    digitalWrite(controlPins[i], LOW);   
  }

  for(int i=BANK_SIZE-1; i>=0; i--) {
    digitalWrite(controlPins[i], HIGH);   
    delay(CELL_JUMP_DELAY);                    
    digitalWrite(controlPins[i], LOW);   
  }

  delay(CELL_JUMP_DELAY);

  for(int i=0; i<BANK_SIZE; i++) {
    digitalWrite(controlPins[i], HIGH);      
  }
  
  delay(ALL_CELLS_ON_DELAY);                   
  
  for(int i=0; i<BANK_SIZE; i++) {
    digitalWrite(controlPins[i], LOW);      
  }
}