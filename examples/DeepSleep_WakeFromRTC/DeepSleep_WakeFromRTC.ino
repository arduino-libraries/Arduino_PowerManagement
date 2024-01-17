
#include "Arduino.h"
#include "Arduino_PowerManagement.h"
#include "Arduino_Portenta_C33_LowPower.h"
#include "RTC.h"

RTCTime initial_time(1, Month::JANUARY, 2000, 12, 10, 00, DayOfWeek::TUESDAY, SaveLight::SAVING_TIME_ACTIVE);

LowPower lowPower;
PowerManagement manager;
Board board; 
Charger charger;

static void alarmCallback()
{   
    board.turnPeripheralsOn();
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    board.turnPeripheralsOff();
    lowPower.deepSleep();
}






void setup() {
    lowPower = LowPower();
    lowPower.enableWakeupFromRTC();

    manager = PowerManagement();
    manager.begin();
    board = manager.getBoard();
    charger = manager.getCharger();

    board.turnPeripheralsOn();
    charger.disableCharger();

    pinMode(LED_BUILTIN, OUTPUT);

    RTC.begin();
    if (!RTC.isRunning()) RTC.setTime(initial_time);
    board.sleepFor(0, 0, 10, alarmCallback);

    
    charger.disableCharger();

    Serial.begin(115200);
    //while(!Serial);
}

void loop(){
    board.turnPeripheralsOff();
    lowPower.deepSleep();
}

