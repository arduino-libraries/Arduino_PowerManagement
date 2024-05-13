
#include "Arduino_PowerManagement.h"
#include "RTC.h"

RTCTime initialTime(1, Month::JANUARY, 2000, 12, 10, 00, DayOfWeek::TUESDAY, SaveLight::SAVING_TIME_ACTIVE);

Board board; 

void blinkLed(int ledPin, int delayTime = 1000){
    digitalWrite(ledPin, LOW);
    delay(delayTime);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
}

void setup() {
    pinMode(LEDR, OUTPUT); // Used to indicate errors
    digitalWrite(LEDR, HIGH); // Turn off the red LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); // Turn off the built-in LED
    pinMode(LEDB, OUTPUT); // Used to indicate that the board is awake    
    
    // Turn on the blue LED to show that the board is still awake
    digitalWrite(LEDB, LOW);
    
    RTC.begin();
    
    if(!board.begin()){
        while (true){
            blinkLed(LEDR);
        }
    }

    board.enableWakeupFromRTC(0, 0, 10); // Sleep for 60 seconds
    board.setAllPeripheralsPower(true); // TODO: Check if this is necessary
   
    if (!RTC.isRunning()) {
        RTC.setTime(initialTime);
    }

    board.standByUntilWakeupEvent();
}

void loop(){}
