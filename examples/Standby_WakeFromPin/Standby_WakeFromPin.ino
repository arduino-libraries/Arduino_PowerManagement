
#include "Arduino.h"
#include "Arduino_PowerManagement.h"


#define PORTENTA_C33_WAKEUP_PIN A3
#define GOTO_SLEEP_PIN D0

volatile bool shouldGoToSleep = false;

Board board; 

void setup() {
    board = Board();
    board.begin();
    board.setAllPeripheralsPower(true);

    // Allows to use a button to put the device into sleep mode
    attachInterrupt(digitalPinToInterrupt(GOTO_SLEEP_PIN), goToSleep, RISING);

    #if defined(ARDUINO_PORTENTA_C33)
        // On Portenta C33, you can specify which pin to use to wake up the device from sleep mode
        // Please read the documentation to understand which pins can be used to wake up the device.
        board.enableWakeupFromPin(PORTENTA_C33_WAKEUP_PIN, RISING);
    #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_GENERIC_STM32H747_M4) || defined(ARDUINO_NICLA_VISION)
        // On Portenta only pin GPIO0 can be used to wake up the device from sleep mode
        board.enableWakeupFromPin();
    #endif
    


    pinMode(LEDB, OUTPUT);
}

void goToSleep(){
  shouldGoToSleep = true;
}

void loop() {
    if(shouldGoToSleep){
        shouldGoToSleep = false;
        board.setAllPeripheralsPower(false); // turn off peripherals before going to sleep 
        board.standByUntilWakeupEvent();
    } else {
        // Show that the board is awake by blinking the LED
        digitalWrite(LEDB, HIGH);
        delay(1000);
        digitalWrite(LEDB, LOW);
        delay(1000);
    }
}
