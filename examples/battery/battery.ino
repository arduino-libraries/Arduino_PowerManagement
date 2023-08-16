#include "PowerManagement.h"

PowerManagement manager = PowerManagement();
Battery battery; 

void setup() {
  Serial.begin(115200);
  while (!Serial);

  manager.begin();
  battery = manager.getBattery();
}

void loop(){
    Serial.print("* Voltage: ");
    Serial.println(String(battery.readVoltageAvg()) + "mV");

    Serial.print("* Current: ");
    Serial.println(String(battery.readCurrent()) + "mA");

    Serial.print("* Percentage: ");
    Serial.println(String(battery.readPercentage()) + "%");

    Serial.print("* Remaining Capacity: ");
    Serial.println(String(battery.readRemainingCapacity()) + "mAh");

    Serial.print("* Temperature: ");
    Serial.println(String(battery.readTempAvg()));

    Serial.print("* Time-to-full: ");
    Serial.println(String(battery.readTimeToFull()) + "s");

    Serial.print("* Time-to-empty: ");
    Serial.println(String(battery.readTimeToEmpty()) + "s");

    delay(1000);
}