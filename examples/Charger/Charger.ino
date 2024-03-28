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
    // Wait for Serial to be ready with a timeout of 5 seconds
    for (auto start = millis(); !Serial && millis() - start < 5000;);

    manager = PowerManagement();
    manager.begin();

    battery = manager.getBattery();
    charger = manager.getCharger();

    Serial.print("Charging is enabled: ");
    Serial.println(charger.isEnabled() ? "true" : "false");

    Serial.print("Charge current: ");
    Serial.println(charger.getChargeCurrent());

    Serial.print("Charge voltage: ");
    Serial.println(charger.getChargeVoltage());

    Serial.print("End of charge current: ");
    Serial.println(charger.getEndOfChargeCurrent());

    Serial.print("Input current limit: ");
    Serial.println(charger.getInputCurrentLimit());

    // The following charger settings are not supported on Nicla Vision
    #if !defined(ARDUINO_NICLA_VISION)
        if (!charger.setChargeCurrent(0.2))
        {
            Serial.println("Failed to set charge current");
            Serial.println("Please double check the supported values in the documentation");
        }

        if (!charger.setChargeVoltage(3.8))
        {
            Serial.println("Failed to set charge voltage");
            Serial.println("Please double check the supported values in the documentation");
        }

        if (!charger.setEndOfChargeCurrent(0.005))
        {
            Serial.println("Failed to set end of charge current");
            Serial.println("Please double check the supported values in the documentation");
        }
    #endif
}

String getChargerState(){
    ChargingState status = charger.getState();

    switch (status) {
        case ChargingState::PreCharge:
            return "precharge";
            break;
        case ChargingState::FastChargeConstantCurrent:
            return "fast-charge constant current";
            break;
        case ChargingState::FastChargeConstantVoltage:
            return "fast-charge constant voltage";
            break;
        case ChargingState::EndOfCharge:
            return "end-of-charge";
            break;
        case ChargingState::Done:
            return "done";
            break;
        case ChargingState::TimerFaultError:
            return "timer fault";
            break;
        case ChargingState::ThermistorSuspendError:
            return "thermistor suspend";
            break;
        case ChargingState::ChargerDisabled:
            return "off";
            break;
        case ChargingState::BatteryOvervoltageError:
            return "overvoltage condition";
            break;
        case ChargingState::ChargerBypassed:
            return "disabled";
            break;
        default:
            return "unknown";
            break;
    }
}

void loop(){
    ChargingState status = charger.getState();

    Serial.print("* Voltage: ");
    Serial.println(String(battery.voltage()) + "mV");

    Serial.print("* Current: ");
    Serial.println(String(battery.current()) + " mA");

    Serial.print("* Percentage: ");
    Serial.println(String(battery.percentage()) + "%");

    Serial.print("* Charger state: ");
    Serial.println(getChargerState());

    Serial.println();
    delay(1000);
}
