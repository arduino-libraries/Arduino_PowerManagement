/*
    Standby Wake from RTC Demo for Portenta C33 

    This example demonstrates how to  wake up the Portenta C33 from standby mode using the included RTC (Real Time Clock).
    The device will go to sleep for 1 second and then wake up. When the device is awake you will see the board's blue LED turned on. 
    Effectively, you will get the same effect as with blink. 

    On the Portenta C33 with the peripherals turned off you can expect around 60uA of current consumption in standby mode.
    The example also turns off the peripherals before going to sleep and turns them back on after waking up.

    Usage:
        - Make sure you are running the latest version of the Renesas Core
        - Select the Portenta C33 board from the Tools menu
        - Select the Portenta C33 USB port from the Tools menu
        - Upload the code to your Portenta C33
    
    Initial author: Cristian Dragomir (c.dragomir@arduino.cc)
*/


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
    digitalWrite(LED_BUILTIN, LOW); // Turn on the built-in LED
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH); // Turn off the built-in LED
    pinMode(LEDB, OUTPUT); // Used to indicate that the board is awake    
  
    if(!board.begin()){
        while (true){
            blinkLed(LEDR);
        }
    }


    board.setAllPeripheralsPower(true); // TODO: Check if this is necessary
    digitalWrite(LEDB, LOW); // Turn on the blue LED to show that the board is still awake
    
    RTC.begin();
    if (!RTC.isRunning()) {
        if(!RTC.setTime(initialTime)){
            while (true){
                blinkLed(LEDR);
            }
        }
    }

    board.enableWakeupFromRTC(0, 0, 10); // Sleep for 10 seconds

    delay(10000); // Keep the board awake for 10 seconds, so we can se it working

    board.shutDownFuelGauge();
    board.setAllPeripheralsPower(false);
    board.standByUntilWakeupEvent();
}

void loop(){}