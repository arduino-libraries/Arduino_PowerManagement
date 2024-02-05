
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

    attachInterrupt(digitalPinToInterrupt(SLEEP_PIN), sleep, RISING);

    board.enableWakeupFromPin(WAKE_PIN, RISING);
    board.setAllPeripheralsPower(true);
    charger.disable();

    pinMode(LED_BUILTIN, OUTPUT);
}

void sleep(){
  sleepFlag = true;
}

void loop() {
    if(sleepFlag){
        sleepFlag = false;

        //board.setAllPeripheralsPower(false);
        board.sleepUntilWakeupEvent();
    } else {

        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
    }
}
