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

    charger.enable();

    // TODO What's different on Nicla Vision?
  #if !defined(ARDUINO_NICLA_VISION)
    charger.setChargeCurrent(ChargeCurrent::I_200_mA);
    charger.setChargeVoltage(ChargeVoltage::V_3_80);
    charger.setEndOfChargeCurrent(EndOfChargeCurrent::I_5_mA);
  #endif
}

void getChargerState(){
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

    Serial.print("* Charger state : ");
    Serial.println(getChargerState());

    Serial.println();
    delay(1000);
}
