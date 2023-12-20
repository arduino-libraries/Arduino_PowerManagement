
#include "Arduino.h"
#include "LowPower.h"
#include "PowerManagement.h"

#define WAKE_PIN A3
#define SLEEP_PIN 0

bool ledState = false;
bool sleepFlag = false;

PowerManagement manager;
Board board; 
Charger charger;
LowPower lowPower;

void setup() {
    lowPower = LowPower();
    manager = PowerManagement();
    manager.begin();
    board = manager.getBoard();
    charger = manager.getCharger();

    attachInterrupt(digitalPinToInterrupt(SLEEP_PIN), sleep, RISING);
    lowPower.setWakeupPin(WAKE_PIN);
    board.lowPowerMode(false);
}

void sleep(){
  sleepFlag = true;
}

void loop() {
    if(sleepFlag){
        board.lowPowerMode(true);
        charger.disableCharger();
        Wire3.end();

        sleepFlag = false;
        lowPower.deepSleep();
    }
}
