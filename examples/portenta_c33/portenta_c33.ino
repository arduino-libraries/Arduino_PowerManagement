/*
Portenta C33 Power Management Demo

This sketch demonstrates the usage of power management features along with WiFi network scanning using the NINA module.
It is designed specifically for the Arduino Portenta C33 board and won't work with any other board 
The sketch showcases how you can reduce the power usage by disabling the power hungry WiFi chip. 
Additionaly, it showcases how you can change the analog and reference voltages, which is another Portenta C33 specific functionality.

  Requirements:
  - Arduino Portenta C33 board
  - Arduino IDE
  - WiFiC3 library (installable from the Arduino Library Manager)
  - PowerManagement library (if required by the board)

  Usage:
  1. Install the required libraries:
     - Open the Arduino IDE.
     - Go to "Sketch" -> "Include Library" -> "Manage Libraries..."
     - Search for "PowerManagement" and install it.

  2. Upload the Sketch:
     - Open the provided sketch in the Arduino IDE.
     - Select your board type and port from the "Tools" menu.
     - Click the "Upload" button to upload the sketch to your board.

  3. Monitor Serial Output:
     - Open the Serial Monitor in the Arduino IDE.
     - Set the baud rate to 9600.
     - You will see the sketch performing the following steps:
       - Enabling the communication switch.
       - Printing battery status.
       - Scanning and listing available WiFi networks.
       - Turning off the communication switch.
       - Printing battery status again.

*/

#include "PowerManagement.h"
#include <WiFiC3.h>

PowerManagement manager = PowerManagement();
Battery battery;
Board board;
Charger charger;

void setup() {
  Serial1.begin(115200);
  while (!Serial1) {
    ; // wait for serial port to connect
  }

  manager.begin();
  battery = manager.getBattery();
  board = manager.getBoard();
  charger = manager.getCharger();

   // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial1.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial1.println("Please upgrade the firmware");
  }



  //board.setAnalogVoltage(1.80);
  //board.setReferenceVoltage(1.80);

  // Enable the communication switch (adjust rail name if needed)
 // board.setCommunicationSwitch(true);

  // Scan and list available networks


  // Print how much current is pulled from the battery


}

void loop() {
  Serial1.println("Current before: " + String(battery.readCurrent()));

  delay(2000);
  
  listNetworks();

  // Turn off the communication switch
  board.setCommunicationSwitch(false);
  delay(2000);
  // Print how much current is pulled from the battery
  Serial1.println("Current after: " + String(battery.readCurrent()));

}

void listNetworks() {
  Serial1.println("Scanning available networks...");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial1.println("Couldn't get a WiFi connection");
    return;
  }

  Serial1.print("Number of available networks: ");
  Serial1.println(numSsid);

  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial1.print(thisNet);
    Serial1.print(") ");
    Serial1.print(WiFi.SSID(thisNet));
    Serial1.print("\tSignal: ");
    Serial1.print(WiFi.RSSI(thisNet));
    Serial1.print(" dBm");

  }
  Serial1.println();
}

