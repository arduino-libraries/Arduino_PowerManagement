/*
    Standby Wake From Pin Demo

    This sketch demonstrates how you can use the Arduino_PowermManagement library to send a board to standby mode by using a GPIO pin and wake it up from another. 
    This sketch is universal and worksn on both Portenta C33 and H7. 

    On the the Portenta C33 you can select any of the supported pins (A0, A1, A2, A3, A4, A5, D4, D7) to wake up the board from standby mode, 
    but on the Portenta H7 only GPIO0 can be used to wake up the board from standby mode. GPIO0 is available trough the High Density Connectors and you need a breakout board to access it. 

    Requirements:
        - Arduino Portenta C33, Arduino Portenta H7
        - Arduino IDE / Arduino CLI
        - PowerManagement library (installable from the Arduino Library Manager)

    Usage:
        - Connect a button to GOTO_SLEEP_PIN and with a pull-up resistor to 3.3V
        - Connect a button to pin PORTENTA_C33_WAKEUP_PIN if you are using the Portenta C33 or GPIO0 if you are using a Portenta H7  and with a pull-up resistor to 3.3V 
            (If you need information about how to wire the buttons check this link: https://docs.arduino.cc/built-in-examples/digital/Button/)
        - Upload the provided sketch to the board
        - Press the button connected to GOTO_SLEEP_PIN to put the board into standby mode
        - Press the button connected to PORTENTA_C33_WAKEUP_PIN or GPIO0 to wake up the board from standby mode
        - The LED will blink every second to show that the board is awake when not in standby mode
        
    Original author: C. Dragomir (http://arduino.cc)
*/

#include "Arduino.h"
#include "Arduino_PowerManagement.h"


#define PORTENTA_C33_WAKEUP_PIN A3
#define GOTO_SLEEP_PIN D0

volatile bool shouldGoToSleep = false;

Board board; 

void setup() {
    board = Board();
    board.begin();
    board.setAllPeripheralsPower(true); // TODO: Check if this is necessary

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
        board.shutDownFuelGauge();
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
