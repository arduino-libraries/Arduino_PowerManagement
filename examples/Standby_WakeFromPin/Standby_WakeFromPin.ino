/*
    Standby Wake From Pin Demo

    This sketch demonstrates how you can use the Arduino_PowermManagement library to send a board to standby mode by using a GPIO pin and wake it up from another. 
    This sketch is universal and worksn on both Portenta C33 and H7. 

    On the the Portenta C33 you can select any of the supported pins (A0, A1, A2, A3, A4, A5, D4, D7) to wake up the board from standby mode.
    However setAllPeripheralsPower(false) in this sketch turns off the power lane of the analog pins.
    This means they cannot sink current and therefore cannot be used to wake up the device. 
    Hency only D4 and D7 can be used to wake up the device in this configuration.

    On the Portenta H7 only GPIO0 can be used to wake up the board from standby mode. GPIO0 is available through the High Density Connectors and you need a breakout board to access it. 

    Requirements:
        - Arduino Portenta C33, Arduino Portenta H7
        - Arduino IDE / Arduino CLI
        - PowerManagement library (installable from the Arduino Library Manager)

    Usage:
        - Connect a button to GOTO_SLEEP_PIN and with a pull-up resistor to 3.3V
        - Connect a button to pin PORTENTA_C33_WAKEUP_PIN if you are using the Portenta C33 or GPIO0 if you are using a Portenta H7  and with a pull-up resistor to 3.3V 
          For maximum power saving use external pull-up resistors.
          You will need to power them separately as the 3.3V pin on the board 
          is turned off when the device goes to sleep and peripherals are turned off.
          Alternatively, use pinMode(<pin>, INPUT_PULLUP) for the pins and connect the buttons to ground.
          (If you need information about how to wire the buttons check this link: https://docs.arduino.cc/built-in-examples/digital/Button/)

        - Upload the provided sketch to the board
          Note: On Portenta H7, you need to upload this sketch to both cores, the M7 and the M4 for it to work.
                You can do so by selecting the M7 core and then the M4 core from the Tools menu in the "Target core" section.
        - Press the button connected to GOTO_SLEEP_PIN to put the board into standby mode
        - Press the button connected to PORTENTA_C33_WAKEUP_PIN or GPIO0 on Portenta H7 to wake up the board from standby mode
        - The LED will blink every second to show that the board is awake when not in standby mode
        
    Original author: C. Dragomir (http://arduino.cc)
*/

#include "Arduino.h"
#include "Arduino_PowerManagement.h"


#define PORTENTA_C33_WAKEUP_PIN D4
#define GOTO_SLEEP_PIN D0

volatile bool shouldGoToSleep = false;

Board board; 

void setup() {
    // When uploading this sketch to the M4 core, it just goes to standby mode.
    #if defined(CORE_CM4)
      board.standByUntilWakeupEvent();
      return;
    #endif

    pinMode(LED_BUILTIN, OUTPUT);

    // Register the sleep and wake-up pins as inputs
    pinMode(GOTO_SLEEP_PIN, INPUT);
    pinMode(PORTENTA_C33_WAKEUP_PIN, INPUT);

    board.begin();
    board.setAllPeripheralsPower(true); // turn on peripherals after waking up from deep sleep

    // Allows to use a button to put the device into sleep mode
    attachInterrupt(digitalPinToInterrupt(GOTO_SLEEP_PIN), goToSleep, FALLING);

    #if defined(ARDUINO_PORTENTA_C33)
        // On Portenta C33, you can specify which pin to use to wake up the device from sleep mode
        // Please read the documentation to understand which pins can be used to wake up the device.
        board.enableWakeupFromPin(PORTENTA_C33_WAKEUP_PIN, FALLING);
    #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_GENERIC_STM32H747_M4)
        // On Portenta only pin GPIO0 can be used to wake up the device from sleep mode
        board.enableWakeupFromPin();
    #endif    
}

void goToSleep(){
  shouldGoToSleep = true;
}

void loop() {
    if(shouldGoToSleep){
        digitalWrite(LED_BUILTIN, HIGH); // turn off the LED to show that the board is going to sleep
        board.shutDownFuelGauge();
        board.setAllPeripheralsPower(false); // turn off peripherals before going to sleep 
        board.standByUntilWakeupEvent();
        shouldGoToSleep = false;
    } else {
        // Show that the board is awake by blinking the LED
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
    }
}
