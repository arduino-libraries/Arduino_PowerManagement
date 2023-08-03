


#include "PowerManagement.h"

PowerManagement PowerManager = PowerManagement();
Battery battery; 
Board board; 

void setup() {
  battery = PowerManager.getBattery();
  board = PowerManager.getBoard();

  Serial.begin(115200);
  while (!Serial);
  Wire1.begin();

  battery.begin();
  board.begin();
}

void loop() {

   
    Serial.println("is battery powered: "); board.isBatteryPowered();
    Serial.println("is usb powered: "); board.isUSBPowered();
    Serial.println("is charging: "); board.isCharging();
 
    Serial.println();

    Serial.print("Voltage: ");
    Serial.println(battery.readVoltageAvg());
    Serial.print("Percentage: ");
    Serial.println(battery.readPercentage());
    Serial.print("Current: ");
    Serial.println(battery.readCurrentAvg());
    Serial.print("Temperature: ");
    Serial.println(battery.readTempAvg());
    Serial.print("Time-to-full: ");
    Serial.println(battery.readTimeToFull());
    Serial.print("Time-to-empty: ");
    Serial.println(battery.readTimeToFull());
    Serial.print("Remaining capacity ");
    Serial.println(battery.readRemainingCapacity());
    Serial.print("Reported capacity");
    Serial.println(battery.readReportedCapacity());
    Serial.println("");

    delay(1000);

}