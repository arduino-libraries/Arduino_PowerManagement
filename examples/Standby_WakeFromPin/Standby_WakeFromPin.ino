
#include "Arduino.h"
#include "Arduino_PowerManagement.h"


#define WAKE_PIN A3
#define GOTO_SLEEP_PIN 0

volatile bool shouldGoToSleep = false;

Board board; 
Charger charger;

void setup() {
    board = Board();
    charger = Charger();
    board.begin();
    charger.begin();

    // Allows to use a button to put the device into sleep mode
    attachInterrupt(digitalPinToInterrupt(GOTO_SLEEP_PIN), goToSleep, RISING);

    #if defined(ARDUINO_PORTENTA_C33)
    // On Portenta C33, you can specify which pin to use to wake up the device from sleep mode
    // Please read the documentation to understand which pins can be used to wake up the device.
    board.enableWakeupFromPin(WAKE_UP_PIN, RISING);
    #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_GENERIC_STM32H747_M4) || defined(ARDUINO_NICLA_VISION)
    // On Portenta only pin GPIO0 can be used to wake up the device from sleep mode
    board.enableWakeupFromPin();
    #endif

    // TODO why is this needed? Why true?
    board.setAllPeripheralsPower(true);
    // TODO why is this needed?
    charger.setEnabled(false);

    pinMode(LEDB, OUTPUT);
}

void goToSleep(){
  shouldGoToSleep = true;
}

void loop() {
    if(shouldGoToSleep){
        shouldGoToSleep = false;

        // TODO why is this here?
        //board.setAllPeripheralsPower(false);
        board.standByUntilWakeupEvent();
    } else {
        // Show that the board is awake by blinking the LED
        digitalWrite(LEDB, HIGH);
        delay(1000);
        digitalWrite(LEDB, LOW);
        delay(1000);
    }
}
