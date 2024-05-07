
#include "Arduino.h"
#include "Arduino_PowerManagement.h"
#include "RTC.h"

RTCTime initial_time(1, Month::JANUARY, 2000, 12, 10, 00, DayOfWeek::TUESDAY, SaveLight::SAVING_TIME_ACTIVE);

LowPower lowPower;
PowerManagement manager;
Board board; 
Charger charger;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    
    RTC.begin();
    
    manager = PowerManagement();
    manager.begin();
    board = manager.getBoard();

    board.enableWakeupFromRTC();
    board.setAllPeripheralsPower(true);

   
    if (!RTC.isRunning()) {
        RTC.setTime(initial_time);
    }

    digitalWrite(LED_BUILTIN, HIGH);
    board.sleepFor(0, 0, 10);

    // Turn LED on to indicate the board is awake
    digitalWrite(LED_BUILTIN, LOW);
}

void loop(){
    //board.setAllPeripheralsPower(false);
    board.deepSleepUntilWakeupEvent();
}

