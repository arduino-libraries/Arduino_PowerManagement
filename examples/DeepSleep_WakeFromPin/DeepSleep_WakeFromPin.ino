
#include "Arduino.h"
#include "PowerManagement.h"
#include "LowPower.h"

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

    attachInterrupt(digitalPinToInterrupt(SLEEP_PIN), sleep, RISING);

    board.enableWakeupFromPin(WAKE_PIN);
    //board.turnPeripheralsOn();
    charger.disableCharger();

    pinMode(LED_BUILTIN, OUTPUT);
}

void sleep(){
  sleepFlag = true;
}

void loop() {
    if(sleepFlag){
        sleepFlag = false;

        //board.turnPeripheralsOff();
        board.sleepUntilWakeupEvent();
    } else {

        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
    }
}
