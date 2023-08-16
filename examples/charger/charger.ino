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