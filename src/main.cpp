#include <Arduino.h>
#include "Devices/Bank6S/Bank6S.h"

#define NOTHING 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define S_ALL 7


int balancierPins[] = {7,2,3,4,5,6};
int powerPin = 8;
int selectButton = A7;
bool selectButtonPressed = false;

const uint8_t voltagePins[] = {A1, A2, A3, A4, A5, A6};
const uint8_t controlPins[] = {7, 2, 3, 4, 5, 6};
Bank6S bank(voltagePins, controlPins);

int sState;

void initializeBoard() {
  Serial.begin(115200);
    
  for(int i=0; i<6; i++) {
    pinMode(balancierPins[i], OUTPUT);
  }

  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);  
}

void balancierLedsCheck() {
  for(int i=0; i<6; i++) {
    digitalWrite(balancierPins[i], HIGH);   
    delay(50);                    
    digitalWrite(balancierPins[i], LOW);   
  }

  for(int i=5; i>=0; i--) {
    digitalWrite(balancierPins[i], HIGH);   
    delay(50);                    
    digitalWrite(balancierPins[i], LOW);   
  }

  delay(50);

  for(int i=0; i<6; i++) {
    digitalWrite(balancierPins[i], HIGH);      
  }
  
  delay(500);                   
  
  for(int i=0; i<6; i++) {
    digitalWrite(balancierPins[i], LOW);      
  }
}

void enableS(int s1=0, int s2=0, int s3=0, int s4=0, int s5=0, int s6=0) {
  digitalWrite(balancierPins[0], s1); 
  digitalWrite(balancierPins[1], s2); 
  digitalWrite(balancierPins[2], s3); 
  digitalWrite(balancierPins[3], s4); 
  digitalWrite(balancierPins[4], s5); 
  digitalWrite(balancierPins[5], s6); 
}

void processState() {
  enableS();

  if(sState == NOTHING) return;

  if(sState == S_ALL) {
    enableS(1,1,1,1,1,1);
  } else {
    digitalWrite(balancierPins[sState-1], HIGH); 
  }
}

void processSelect() {  
  int pinRead = analogRead(selectButton);

  if(pinRead > 1000 && !selectButtonPressed) return;
  if(pinRead < 1000 && selectButtonPressed) return;

  selectButtonPressed = pinRead < 1000;

  if(!selectButtonPressed) return;

  if(++sState > S_ALL) sState = NOTHING;  
}

void printVoltages() {
  if(!bank.isVoltagesChanged()) return;

  float* voltages = bank.getVoltages();

  Serial.print("\nVoltages[");
  Serial.print(bank.totalVoltage());
  Serial.print("v/");
  Serial.print(bank.getBalancingVoltage());
  Serial.print("v] ");

  for(int i=0; i<6; i++) {        
    Serial.print(voltages[i]);
    Serial.print("v ");
  }
}

void setup() {
  initializeBoard();
  balancierLedsCheck();

  delay(1000);

  sState = S_ALL;

  Serial.println("Initialized");
}

void loop() {  
  bank.process();

  printVoltages();
  // processSelect();
  // processState();
  
  delay(100);
}