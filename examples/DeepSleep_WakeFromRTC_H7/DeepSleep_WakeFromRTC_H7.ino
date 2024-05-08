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