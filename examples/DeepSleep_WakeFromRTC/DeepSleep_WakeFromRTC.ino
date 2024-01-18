
#include "Arduino.h"
#include "Arduino_PowerManagement.h"
#include "RTC.h"

RTCTime initial_time(1, Month::JANUARY, 2000, 12, 10, 00, DayOfWeek::TUESDAY, SaveLight::SAVING_TIME_ACTIVE);

LowPower lowPower;
PowerManagement manager;
Board board; 
Charger charger;

static void alarmCallback()
{   
    board.turnPeripheralsOn();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(5000);
    digitalWrite(LED_BUILTIN, LOW);
    board.turnPeripheralsOff();
    board.deepSleepUntilWakeupEvent();
}


void setup() {
    RTC.begin();
    
    manager = PowerManagement();
    manager.begin();
    board = manager.getBoard();

    board.enableWakeupFromRTC();
    board.turnPeripheralsOn();

   
    if (!RTC.isRunning()) {
        RTC.setTime(initial_time);
        board.sleepFor(0, 0, 1, &alarmCallback, &RTC);
    }

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

 
}

void loop(){
    board.turnPeripheralsOff();
    board.deepSleepUntilWakeupEvent();
}

