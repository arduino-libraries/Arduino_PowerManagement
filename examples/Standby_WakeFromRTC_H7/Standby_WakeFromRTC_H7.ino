/*
  Charger Demo

  This sketch demonstrates how to use the PowerManagement library enable low power modes on the Arduino Portenta H7.
  * In the setup() function, it enters standby mode and waits for a wakeup event from the RTC.
  * The loop() functionit is not used in this sketch.
  
  IMPORTANT: Please note that this sketch has to be uploaded to the M4 core too in order to achieve the lowest power consumption.

  Requirements:
  - Arduino Arduino Portenta H7
  - Arduino IDE
  - PowerManagement library (installable from the Arduino Library Manager)

  Usage:

  1. Connect a battery to the board.    
  
  2. Upload the Sketch to the M4 core:
    - Open the provided sketch in the Arduino IDE.
    - Select your board type and port from the "Tools" menu.
    - Select the M4 core from the "Tools" menu.
    - Click the "Upload" button to upload the sketch to your board.

  3. Upload the Sketch to the M7 core:
    - Select the M7 core from the "Tools" menu.
    - Click the "Upload" button to upload the sketch to your board.

  4. Observer LED behavior:
    - The blue LED will turn on when the board is awake.
    - The blue LED will turn off when the board goes to sleep.
    - The red LED will blink if the board fails to initialize.
*/

#include "Arduino_PowerManagement.h"

Board board; 

void setup() {
    board = Board();

    // When uploading this sketch to the M4 core, it just goes to standby mode.
    #if defined(ARDUINO_GENERIC_STM32H747_M4)
      board.standByUntilWakeupEvent();
      return;
    #endif

    // Turn off the built-in LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    
    // Turn on the blue LED to show that the board is still awake
    pinMode(LEDB, OUTPUT);    
    digitalWrite(LEDB, LOW);

    if(!board.begin()){
        // If the board fails to initialize, it will blink the red LED
        pinMode(LEDR, OUTPUT);
        while (true){
            digitalWrite(LEDR, LOW);
            delay(1000);
            digitalWrite(LEDR, HIGH);
            delay(1000);
        }
    }


    board.enableWakeupFromRTC(0, 0, 10); // Sleep for 10 seconds

    // The LED should go off when the board goes to sleep
    board.setAllPeripheralsPower(false);
    board.standByUntilWakeupEvent();
}

void loop() {
  // put your main code here, to run repeatedly:
} 