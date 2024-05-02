
/*
  Battery Information Display Demo

  This sketch demonstrates how to read battery information using the PowerManagement library. 
  It prints the battery's voltage, current, percentage, remaining capacity and temperature in a loop. 
  The sketch is designed to work with the PowerManagement library and is intended for educational purposes.

  Requirements:
  - Arduino Portenta C33, Arduino Portenta H7, Arduino Nicla Vision
  - Arduino IDE / Arduino CLI
  - PowerManagement library (installable from the Arduino Library Manager)

  Usage:

  1. Connect the Battery:
     - Please note that batteries without NTC thermistors will 
       not provide temperature information.
  
  2. Upload the Sketch:
     - Open the provided sketch in the Arduino IDE.
     - Select your board type and port from the "Tools" menu.
     - Click the "Upload" button to upload the sketch to your board.

  3. Monitor Serial Output:
     - Open the Serial Monitor in the Arduino IDE.
     - Set the baud rate to 115200.
     - You will see the sketch continuously printing battery information.
*/

#include "Arduino_PowerManagement.h"

Battery battery; 
Charger charger;

void setup() {
   Serial.begin(115200);
   while (!Serial);
   delay(1000); // Delay to give time to load the Serial Monitor


   // Charger charger = Charger();
   // charger.begin();
   // charger.setEndOfChargeCurrent(5); // Set the end of charge current in mA
   Serial.println("Charger initialized.");

   BatteryCharacteristics characteristics = BatteryCharacteristics();
   characteristics.capacity = 200; // Battery capacity in mAh. Change this value to match your battery's capacity.
   characteristics.endOfChargeCurrent = 5; // End of charge current in mA

   battery = Battery(characteristics);
   bool batteryInitialized = battery.begin(true);
   
   if (!batteryInitialized) {
      Serial.println("Battery initialization failed.");
      Serial.println("Please make sure the battery is connected and try again.");
      while (true);
   }

   battery.resetMaximumMinimumVoltage();
}

void printTimeToEmpty(){
   auto timeToEmptySeconds = battery.timeToEmpty();
   if(timeToEmptySeconds == -1){
      Serial.println("* Time to empty: N/A");
      return;
   }
   auto timeToEmptyHours = timeToEmptySeconds / 3600;
   timeToEmptySeconds = timeToEmptySeconds % 3600;
   auto timeToEmptyMinutes = timeToEmptySeconds / 60;
   timeToEmptySeconds = timeToEmptySeconds % 60;
   Serial.println("* Time to empty: " + String(timeToEmptyHours) + "h " + String(timeToEmptyMinutes) + "m " + String(timeToEmptySeconds) + "s");
}

void printTimeToFull(){
   auto timeToFullSeconds = battery.timeToFull();
   if(timeToFullSeconds == -1){
      Serial.println("* Time to full: N/A");
      return;
   }
   auto timeToFullHours = timeToFullSeconds / 3600;
   timeToFullSeconds = timeToFullSeconds % 3600;
   auto timeToFullMinutes = timeToFullSeconds / 60;
   timeToFullSeconds = timeToFullSeconds % 60;
   Serial.println("* Time to full: " + String(timeToFullHours) + "h " + String(timeToFullMinutes) + "m " + String(timeToFullSeconds) + "s");
}

void loop() {
   bool batteryConnected = battery.isConnected();
   Serial.println("* Battery is connected: " + ( batteryConnected ? String("Yes") : String("No")));
   
   if(batteryConnected){
      Serial.println("* Battery is empty: " + ( battery.isEmpty() ? String("Yes") : String("No")));
      Serial.println("* Is fully charged: " + ( battery.isFullyCharged() ? String("Yes") : String("No")));
      Serial.println("* Voltage: " + String(battery.voltage()) + " V");
      Serial.println("* Average Voltage: " + String(battery.averageVoltage()) + " V");
      Serial.println("* Minimum Voltage: " + String(battery.minimumVoltage()) + " V");
      Serial.println("* Maximum Voltage: " + String(battery.maximumVoltage()) + " V");
      Serial.println("* Current: " + String(battery.current()) + " mA");
      Serial.println("* Average Current: " + String(battery.averageCurrent()) + " mA");
      Serial.println("* Percentage: " + String(battery.percentage()) + "%");
      Serial.println("* Remaining Capacity: " + String(battery.remainingCapacity()) + " mAh");
      Serial.println("* Full Capacity: " + String(battery.fullCapacity()) + " mAh");
      Serial.println("* Internal Temperature: " + String(battery.internalTemperature()) + "°C");
      Serial.println("* Average internal Temperature: " + String(battery.averageInternalTemperature()) + "°C");
      printTimeToEmpty();
      printTimeToFull();
      Serial.println();
   }
   delay(2000);
}
