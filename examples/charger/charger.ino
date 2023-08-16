/*
Charger Demo

This sketch demonstrates how to write charging parameters, read charger state and monitor charging using the PowerManagement library:
* In the setup() function, it sets the charging parameters
* In the loop() functionit prints the battery's voltage, current, percentage and the charger's state allowing you to monitor charging. 

  Requirements:
  - Arduino Portenta C33, Arduino Portenta H7, Arduino Nicla Vision
  - Arduino IDE
  - PowerManagement library (installable from the Arduino Library Manager)

  Usage:
  1. Install the required library:
     - Open the Arduino IDE.
     - Go to "Sketch" -> "Include Library" -> "Manage Libraries..."
     - Search for "PowerManagement" and install it.

  2. Upload the Sketch:
     - Open the provided sketch in the Arduino IDE.
     - Select your board type and port from the "Tools" menu.
     - Click the "Upload" button to upload the sketch to your board.

  3. Monitor Serial Output:
     - Open the Serial Monitor in the Arduino IDE.
     - Set the baud rate to 115200.
     - You will see the sketch continuously printing battery status and charger state.
*/
#include "PowerManagement.h"

PowerManagement manager;
Battery battery; 
Charger charger;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  manager = PowerManagement();
  manager.begin();

  battery = manager.getBattery();
  charger = manager.getCharger();

  charger.setChargeCurrent(ChargeCurrent::I_500_mA);
  charger.setChargeVoltage(ChargeVoltage::V_3_80);
  charger.setEndOfChargeCurrent(EndOfChargeCurrent::I_5_mA);
  charger.setMaxInputCurrent(MaxInputCurrent::I_100_mA);
}

void loop(){
    ChargeStatus status = charger.getChargeStatus();

    Serial.print("* Voltage: ");
    Serial.println(String(battery.readVoltageAvg()) + "mV");

    Serial.print("* Current: ");
    Serial.println(String(battery.readCurrent()) + " mA");

    Serial.print("* Percentage: ");
    Serial.println(String(battery.readPercentage()) + "%");

    Serial.print("* Charger state :");

    switch (status) {
        case PRECHARGE:
            Serial.println("precharge");
            break;
        case FAST_CHARGE_CC:
            Serial.println("fast-charge constant current");
            break;
        case FAST_CHARGE_CV:
            Serial.println("fast-charge constant voltage");
            break;
        case END_OF_CHARGE:
            Serial.println("end-of-charge");
            break;
        case DONE:
            Serial.println("done");
            break;
        case TIMER_FAULT:
            Serial.println("timer fault");
            break;
        case THERMISTOR_SUSPEND:
            Serial.println("thermistor suspend");
            break;
        case OFF:
            Serial.println("off");
            break;
        case BATTERY_OVERVOLTAGE:
            Serial.println("overvoltage condition");
            break;
        case LINEAR_ONLY:
            Serial.println("disabled");
            break;
        default:
            Serial.println("unknown");
            break;
    }

    Serial.println();
    delay(1000);
}
