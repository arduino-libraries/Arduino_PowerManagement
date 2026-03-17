/*
Standby Wake from RTC Demo for Nicla Vision
This example demonstrates how to  wake up the Nicla Vision from standby mode using the included RTC (Real Time Clock).
The device will stay awake for ~5 seconds, then go to sleep for 10 second. When the device is awake you will see the board's blue LED turned on. 
Effectively, you will get the same effect as with blink. 

The example also turns off the peripherals before going to sleep and turns them back on after waking up.
Usage:
    - Make sure you are running the latest version of the Nicla Vision core.
    - Select the Nicla Vision board from the Tools menu
    - Select the Nicla Vision USB port from the Tools menu
    - Upload the code to your Nicla Vision

Note: You need to upload this sketch to both cores, the M7 and the M4 for it to work.
      You can do so by selecting the M7 core and then the M4 core from the Tools menu in the "Target core" section.

Initial authors: 
Sebastian Romero (s.romero@arduino.cc)
*/

#include "Arduino_PowerManagement.h"

Board board;

void blinkLed(int ledPin, int delayTime = 1000){
    digitalWrite(ledPin, LOW);
    delay(delayTime);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
}

void setup() {
    // When uploading this sketch to the M4 core, it just goes to standby mode.
    #if defined(CORE_CM4)
      board.standByUntilWakeupEvent();
      return;
    #endif

    pinMode(LEDR, OUTPUT); // Used to indicate errors
    digitalWrite(LEDR, HIGH); // Turn off the red LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW); // Turn on the built-in LED to show that the board is awake
    
    if(!board.begin()){
        // If the board fails to initialize, it will blink the red LED
        while (true){
            blinkLed(LEDR);
        }
    }

    delay(10000); // keep the board awake for 10 seconds, so we can se it working
    board.shutDownFuelGauge();

    // The LED should go off when the board goes to sleep
    board.setAllPeripheralsPower(false);    

    board.enableWakeupFromRTC(0, 0, 10); // Go to standby for 10 seconds
    board.standByUntilWakeupEvent();
}

void loop() {} 