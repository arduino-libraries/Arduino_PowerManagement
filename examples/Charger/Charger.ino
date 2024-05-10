/*
  Charger Demo

  This sketch demonstrates how to write charging parameters,read charger state and monitor charging using the PowerManagement library:
  * In the setup() function, it sets the charging parameters
  * In the loop() functionit prints the battery's voltage, current, percentage and the charger's state allowing you to monitor charging. 

  Requirements:
  - Arduino Portenta C33, Arduino Portenta H7, Arduino Nicla Vision
  - Arduino IDE
  - PowerManagement library (installable from the Arduino Library Manager)

  Usage:

  1. Connect a Battery to the board
  
  2. Upload the Sketch:
    - Open the provided sketch in the Arduino IDE.
    - Select your board type and port from the "Tools" menu.
    - Click the "Upload" button to upload the sketch to your board.

  3. Monitor Serial Output:
    - Open the Serial Monitor in the Arduino IDE.
    - Set the baud rate to 115200.
    - You will see the sketch continuously printing charger state information.
*/
#include "Arduino_PowerManagement.h"

Battery battery; 
Charger charger;

// Charge current in mA, a safe value for most batteries is half the battery capacity
constexpr int CHARGE_CURRENT_MA = 100; // mA
constexpr int END_OF_CHARGE_CURRENT_MA = 5; // mA

void setup() {
    Serial.begin(115200);
    // Wait for Serial to be ready with a timeout of 5 seconds
    for (auto start = millis(); !Serial && millis() - start < 5000;);
    delay(1000); // Delay to give time to load the Serial Monitor

    charger = Charger();
    if(!charger.begin()){
        Serial.println("Charger initialization failed.");
        while (true);
    }
    
    Serial.print("* ✅ Charging is enabled: ");
    Serial.println(charger.isEnabled() ? "true" : "false");

    auto chargeCurrent = charger.getChargeCurrent();
    auto chargeVoltage = charger.getChargeVoltage();
    auto endOfChargeCurrent = charger.getEndOfChargeCurrent();
    auto inputCurrentLimit = charger.getInputCurrentLimit();

    Serial.println("* ⚡️ Charge current: " + String(chargeCurrent) + " mA");
    Serial.println("* ⚡️ Charge voltage: " + String(chargeVoltage) + " V");
    Serial.println("* ⚡️ End of charge current: " + String(endOfChargeCurrent) + " mA");
    Serial.println("* ⚡️ Input current limit: " + String(inputCurrentLimit) + " mA");

    if (!charger.setChargeCurrent(CHARGE_CURRENT_MA)){
        Serial.println("Failed to set charge current");
        Serial.println("Please double check the supported values in the documentation");
    }

    if (!charger.setEndOfChargeCurrent(END_OF_CHARGE_CURRENT_MA)){
        Serial.println("Failed to set end of charge current");
        Serial.println("Please double check the supported values in the documentation");
    }
}

String getChargerState(){
    ChargingState status = charger.getState();

    switch (status) {
        case ChargingState::preCharge:
            return "precharge";
            break;
        case ChargingState::fastChargeConstantCurrent:
            return "fast-charge constant current";
            break;
        case ChargingState::fastChargeConstantVoltage:
            return "fast-charge constant voltage";
            break;
        case ChargingState::endOfCharge:
            return "end-of-charge";
            break;
        case ChargingState::done:
            return "done";
            break;
        case ChargingState::timerFaultError:
            return "timer fault";
            break;
        case ChargingState::thermistorSuspendError:
            return "thermistor suspend";
            break;
        case ChargingState::chargerDisabled:
            return "off";
            break;
        case ChargingState::batteryOvervoltageError:
            return "overvoltage condition";
            break;
        case ChargingState::chargerBypassed:
            return "disabled";
            break;
        default:
            return "unknown";
            break;
    }
}

void loop(){
    static ChargingState status = ChargingState::none;

    if (status != charger.getState()) {
        status = charger.getState();
        Serial.print("* 👀 Charger state: ");
        Serial.println(getChargerState());
    }

    delay(1000);
}
