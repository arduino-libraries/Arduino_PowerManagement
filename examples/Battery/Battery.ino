
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
  1. Install the required library:
     - Open the Arduino IDE.
     - Go to "Sketch" -> "Include Library" -> "Manage Libraries..."
     - Search for "Arduino_PowerManagement" and install it.

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

void loop() {
   Serial.println("* Battery is connected: " + ( battery.isConnected() ? String("Yes") : String("No")));
   Serial.println("* Voltage: " + String(battery.voltage()) + "mV");
   Serial.println("* Current: " + String(battery.current()) + "mA");
   Serial.println("* Percentage: " + String(battery.percentage()) + "%");
   Serial.println("* Remaining Capacity: " + String(battery.remainingCapacity()) + "mAh");
   Serial.println("* Temperature: " + String(battery.temperature()));
   Serial.println();
   delay(1000);
}
