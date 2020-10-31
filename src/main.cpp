#include <Arduino.h>

#include "Devices/Bank6S/Bank6S.h"
#include "Devices/Screen/Screen.h"
#include "Services/LedsChecker/LedsChecker.h"

#define SERIAL_PRINT_VOLTAGES true
#define SCREEN_ENABLE false

#define NOTHING 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define S_ALL 7

#define POWER_PIN 8
#define REM_READ_PIN A0

bool remOn = true;
int remCounter = 0;

bool readyToShutDown = true;

const uint8_t voltagePins[] = {A1, A2, A3, A0, A7, A6};
const uint8_t controlPins[] = {7, 23, 3, 4, 5, 6};
Bank6S bank(voltagePins, controlPins);

volatile bool balancingStart = false;
volatile bool balancingStop = false;
volatile bool reportVoltages = false;

const uint16_t blalncingDurationSeconds = 300;
const uint8_t blalncingRestSeconds = 2;
const uint8_t blalncingIdleSeconds = 10;

volatile uint16_t secondsCounter = blalncingDurationSeconds - 2;

Screen *screen;

void initializeSecondsTimer() {
  // Reset Timer 4 Reg A
  TCCR4A = 0;

  // Set prescaler 1024
  TCCR4B |= (1 << CS12);
  TCCR4B &= ~(1 << CS11);
  TCCR4B |= (1 << CS10);

  // Set timer value 0
  TCNT4 = 0;

  // Set compare value. 1 second at 1024 prescaler
  OCR4A = 15625;

  // Enable compare interrupt
  TIMSK4 = (1 << OCIE4A);

  // Enable global interrupts
  sei();
}

void initializeBoard() {
  initializeSecondsTimer();
  Serial.begin(115200);
    
  for(int i=0; i<6; i++) {
    pinMode(controlPins[i], OUTPUT);
  }

  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, HIGH);  

  analogReference(EXTERNAL);

  if(SCREEN_ENABLE) {
    // screen = new Screen(&display);
    // screen->initialize();
  }
}

void processManualPinEnable() {
  while(Serial.available()) {
    char inputChar = toupper(Serial.read());
    int inputDigit = inputChar-48;

    Serial.println("");
    Serial.print(inputChar);
    
    if(inputDigit > 0 && inputDigit <= 6) {
      inputChar = toupper(Serial.read());
      Serial.print(inputChar);

      if(inputChar == 'O') {
        Serial.println(" Enable");
        digitalWrite(controlPins[inputDigit-1], HIGH); 
      } else {
        Serial.println(" Disable");
        digitalWrite(controlPins[inputDigit-1], LOW); 
      }
    }    
  }
}

void processPowerControl() {
  if(!readyToShutDown) return;

  remOn = analogRead(REM_READ_PIN) > 1000;
  if(remOn && remCounter > 0) remCounter = 0;

  if(remCounter > 5) digitalWrite(POWER_PIN, LOW); //shutdown
}

void printVoltages() {
  // if(!bank.isVoltagesChanged()) return;

  float* voltages = bank.getVoltages();

  Serial.print("\nREM[");
  Serial.print(remOn ? "ON" : "OFF");
  Serial.print("] Voltages[");
  Serial.print(bank.totalVoltage());
  Serial.print("v/");
  Serial.print(bank.getBalancingVoltage());
  Serial.print("v] ");

  for(int i=0; i<6; i++) {        
    Serial.print(voltages[i]);
    Serial.print("v ");
  }
}

void updateScreen() {
  Serial.println("Screen render");
  screen->setVoltages(bank.getVoltages());
}

void processFlags() {
  if(balancingStart) {
    balancingStart = false;
    bank.startBalancingRoutine();

    if(bank.isBalancing()) {
      readyToShutDown = false;
    } else {
      // Nothing to balance.
      // Wait blalncingIdleSeconds before next start of balancing routine
      secondsCounter = blalncingDurationSeconds - blalncingIdleSeconds;
    }
  }

  if(balancingStop) {
    readyToShutDown = true;
    balancingStop = false;
    bank.stopBalancingRoutine();
  }

  if(reportVoltages) {
    reportVoltages = false;
    if(SERIAL_PRINT_VOLTAGES) printVoltages();
    // if(SCREEN_ENABLE) updateScreen();
  }
}

void setup() {
  initializeBoard();
    
  LedsChecker *ledsChecker = new LedsChecker();
  ledsChecker->call(controlPins);

  Serial.println("Setup completed");
}

void loop() {  
  bank.processVoltages();

  processFlags();
  // processManualPinEnable();
  processPowerControl();
  
  delay(30);
}

ISR(TIMER4_COMPA_vect) {  
  if(++secondsCounter == blalncingDurationSeconds) {
    balancingStop = true;
  }

  if(secondsCounter == (blalncingDurationSeconds + blalncingRestSeconds)) {
    balancingStart = true;
    secondsCounter = 0;
  }

  if(!remOn) remCounter++;

  reportVoltages = true;

  TCNT4 = 0;
}