#include "Arduino.h"
#include "Arduino_PowerManagement.h"

Board board; 


void setup() {
    board = Board();
    if(!board.begin()){
        Serial.println("Board initialization failed.");
        while (true);
    }
    board.enableWakeupFromRTC();
    board.sleepFor(0, 0, 1);

    pinMode(LEDB, OUTPUT);
    digitalWrite(LEDB, LOW);
    board.setAllPeripheralsPower(false);
    board.standByUntilWakeupEvent();
}

void loop() {
  // put your main code here, to run repeatedly:
} 