
/*
  Battery Information Display Demo

  This sketch demonstrates how to read battery information using the PowerManagement library. It prints the battery's voltage, current, percentage, remaining capacity, temperature, time-to-full, and time-to-empty in a loop. The sketch is designed to work with the PowerManagement library and is intended for educational purposes.

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
     - You will see the sketch continuously printing battery information.

*/

#include "PowerManagement.h"

PowerManagement manager;
Battery battery; 


void setup() {
  Serial.begin(115200);
  while (!Serial);

  manager = PowerManagement();
  manager.begin();
  battery = manager.getBattery();

}

void loop(){
      Serial.println(battery.isConnected());
      Serial.print("* Voltage: ");
      Serial.println(String(battery.averageVoltage()) + "mV");

      Serial.print("* Current: ");
      Serial.println(String(battery.averageCurrent()) + "mA");

      Serial.print("* Percentage: ");
      Serial.println(String(battery.percentage()) + "%");

      Serial.print("* Remaining Capacity: ");
      Serial.println(String(battery.remainingCapacity()) + "mAh");

      Serial.print("* Temperature: ");
      Serial.println(String(battery.temperatureAverage()));

      Serial.println();

    delay(1000);
}