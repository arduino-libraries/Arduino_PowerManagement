
#include "Arduino.h"
#include "Arduino_PowerManagement.h"


#define WAKE_PIN A3
#define SLEEP_PIN 0

volatile bool sleepFlag = false;

PowerManagement manager;
Board board; 
Charger charger;

void setup() {

  
    
    manager = PowerManagement();
    manager.begin();
    board = manager.getBoard();
    charger = manager.getCharger();

    attachInterrupt(digitalPinToInterrupt(SLEEP_PIN), goToSleep, RISING);

    #if defined(ARDUINO_PORTENTA_C33)
    board.enableWakeupFromPin(WAKE_PIN, RISING);
    #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
    board.enableWakeupFromPin();
    #endif

    
    board.setAllPeripheralsPower(true);
    charger.disable();

    pinMode(LEDB, OUTPUT);
}

void goToSleep(){
  sleepFlag = true;
}

void loop() {
    if(sleepFlag){
        sleepFlag = false;

        //board.setAllPeripheralsPower(false);
        board.standByUntilWakeupEvent();
    } else {

        digitalWrite(LEDB, HIGH);
        delay(1000);
        digitalWrite(LEDB, LOW);
        delay(1000);
    }
}
