#include "Arduino.h"
#include "Arduino_PowerManagement.h"

PowerManagement manager;
Board board; 


void setup() {
    manager = PowerManagement();
    manager.begin();
    board = manager.getBoard();
    board.enableWakeupFromRTC();
    board.sleepFor(0, 0, 1);

    pinMode(LEDB, OUTPUT);
    digitalWrite(LEDB, LOW);
    board.setAllPeripheralsPower(false);
    board.deepSleepUntilWakeupEvent();
}

void loop() {
  // put your main code here, to run repeatedly:
} 