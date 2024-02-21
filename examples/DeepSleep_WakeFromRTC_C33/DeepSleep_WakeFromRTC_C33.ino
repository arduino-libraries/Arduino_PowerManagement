
#include "Arduino.h"
#include "Arduino_PowerManagement.h"
#include "RTC.h"

RTCTime initial_time(1, Month::JANUARY, 2000, 12, 10, 00, DayOfWeek::TUESDAY, SaveLight::SAVING_TIME_ACTIVE);

LowPower lowPower;
PowerManagement manager;
Board board; 
Charger charger;

void setup() {
    RTC.begin();

    digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN));
    
    manager = PowerManagement();
    manager.begin();
    board = manager.getBoard();

    board.enableWakeupFromRTC();
    board.setAllPeripheralsPower(true);

   
    if (!RTC.isRunning()) {
        RTC.setTime(initial_time);
        board.sleepFor(0, 0, 1);
    }

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop(){
    //board.setAllPeripheralsPower(false);
    board.deepSleepUntilWakeupEvent();
}

