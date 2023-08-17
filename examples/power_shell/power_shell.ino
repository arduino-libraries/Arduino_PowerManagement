#include "PowerManagement.h"
#include <vector>
#include <string>

PowerManagement manager;
Battery battery; 
Board board; 
Charger charger;


std::vector<String> splitString(String input) {
  std::vector<String> args;
  int start = 0;
  int end = input.indexOf(' ');
  while (end >= 0) {
    args.push_back(input.substring(start, end));
    start = end + 1;
    end = input.indexOf(' ', start);
  }
  args.push_back(input.substring(start));
  return args;
}


void printChargerStatus(){
   ChargeStatus status = charger.getChargeStatus();

        switch (status) {
        case PRECHARGE:
            Serial.println("precharge");
            // Additional code specific to precharge
            break;
        case FAST_CHARGE_CC:
            Serial.println("fast-charge constant current");
            // Additional code specific to fast-charge CC
            break;
        case FAST_CHARGE_CV:
            Serial.println("fast-charge constant voltage");
            // Additional code specific to fast-charge CV
            break;
        case END_OF_CHARGE:
            Serial.println("end-of-charge");
            // Additional code specific to end-of-charge
            break;
        case DONE:
            Serial.println("done");
            // Additional code specific to done
            break;
        case TIMER_FAULT:
            Serial.println("timer fault");
            // Additional code specific to timer fault
            break;
        case THERMISTOR_SUSPEND:
            Serial.println("thermistor suspend");
            // Additional code specific to thermistor suspend
            break;
        case OFF:
            Serial.println("off");
            // Additional code specific to off
            break;
        case BATTERY_OVERVOLTAGE:
            Serial.println("overvoltage condition");
            // Additional code specific to battery overvoltage condition
            break;
        case LINEAR_ONLY:
            Serial.println("disabled");
            // Additional code specific to linear only
            break;
        default:
            Serial.println("unknown");
            // Additional code for handling unknown status
            break;
    }
}

void status(){
    
  Serial.println("BOARD: \n--------------------------");
  Serial.print("* Powered by usb: "); Serial.println(board.isUSBPowered());
  Serial.print("* Powered by battery: "); Serial.println(board.isBatteryPowered()); 
  Serial.println();
  
  Serial.println("CHARGER: \n--------------------------");
  Serial.print("* Charger status: "); printChargerStatus();
  Serial.println();

  Serial.println("BATTERY: \n--------------------------");
  Serial.println(
    "* Voltage: " + String(battery.readVoltageAvg()) + "mV \n" +
    "* Current: " + String(battery.readCurrent()) + "mA \n" + 
    "* Percentage: " + String(battery.readPercentage()) + "% \n" +
    "* Remaining Capacity: " + String(battery.readRemainingCapacity()) + "mAh \n" +
    "* Temperature: " + String(battery.readTempAvg()) + "\n" +  
    "* Time-to-full: " + String(battery.readTimeToFull()) + "s \n" + 
    "* Time-to-empty: " + String(battery.readTimeToEmpty()) + "s \n");
}


void setRailVoltage(std::vector<String> args){
  String rail = args[1];
  float voltage = atof(args[2].c_str());

  if(rail == "C33_reference"){
    #if defined(ARDUINO_PORTENTA_C33)
      if(board.setReferenceVoltage(voltage)) Serial.println("Succesfully changed reference voltage");
      else Serial.println("Failed to set reference voltage");
    #else
      Serial.println("Current board is not an arduino portenta c33");
    #endif
  } else if (rail == "C33_analog"){
    #if defined(ARDUINO_PORTENTA_C33)
      if(board.setAnalogVoltage(voltage)) Serial.println("Succesfully set analog voltage");
      else Serial.println("Failed to set analog voltage");
    #else
      Serial.println("Current board is not an arduino portenta c33");
    #endif

  } else if (rail == "C33_external"){
    #if defined(ARDUINO_PORTENTA_C33)
      if(board.setExternalVoltage(voltage)) Serial.println("Succesfully set external voltage");
      else Serial.println("Failed to set external voltage");
    #else
      Serial.println("Current board is not an arduino portenta c33");
    #endif

  } else if (rail == "H7_external"){
    #if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4)
      board.setExternalVoltage(voltage);
    #else
      Serial.println("Current board is not an arduino portenta h7");
    #endif

  } else if (rail == "nicla_external"){
    #if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4)
      board.setExternalVoltage(voltage);
    #else
      Serial.println("Current board is not an arduino nicla vision");
    #endif

  }
}

void toggleRail(std::vector<String> args){
  String rail = args[1];
  bool on = atoi(args[2].c_str()) == 1;

  if (rail == "C33_external"){
    #if defined(ARDUINO_PORTENTA_C33)
      board.setExternalSwitch(on);
    #else
      Serial.println("Current board is not an arduino portenta c33");
    #endif

  } else if (rail == "C33_communication"){
    #if defined(ARDUINO_PORTENTA_C33)
      board.setCommunicationSwitch(on);
    #else
      Serial.println("Current board is not an arduino portenta c33");
    #endif

  } else if (rail == "H7_external"){
    #if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4)
      board.setExternalSwitch(on);
    #else
      Serial.println("Current board is not an arduino portenta h7");
    #endif

  } else if (rail == "nicla_external"){
    #if defined(ARDUINO_NICLA_VISION)
     board.setExternalSwitch(on);
    #else
      Serial.println("Current board is not an arduino nicla vision");
    #endif

  } else if (rail == "nicla_camera"){
    #if defined(ARDUINO_NICLA_VISION)
     board.setCameraSwitch(on);
    #else
      Serial.println("Current board is not an arduino nicla vision");
    #endif
  }
}

void toggleCharger(std::vector<String> args){
  bool on = atoi(args[1].c_str()) == 1;
  Serial.println(on);


  if(on){
    if(charger.enableCharger()){
      Serial.println("> Charger enabled");
    } else {
      Serial.println("> Error enabling charger");
    }

  } else {
    charger.disableCharger();
    Serial.println("> Charger disabled");
  }
}



void setup() {
  Serial.begin(115200);
  while (!Serial);

  manager = PowerManagement();
  manager.begin();

  battery = manager.getBattery();
  board = manager.getBoard();
  charger = manager.getCharger();


  #if !defined(ARDUINO_NICLA_VISION)
    charger.setChargeCurrent(ChargeCurrent::I_200_mA);
    charger.setChargeVoltage(ChargeVoltage::V_3_80);
    charger.setEndOfChargeCurrent(EndOfChargeCurrent::I_5_mA);
  #endif
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readString();
    input.trim();
    std::vector<String> args = splitString(input);

    if (args.size() > 0) {
      String command = args[0];
      if (command == "toggle_rail") {
        toggleRail(args);
      } else if (command == "set_rail_voltage") {
        setRailVoltage(args);
      } else if (command == "toggle_charger") {
        toggleCharger(args);
      } else if (command == "status") {
        status();

      } else {
        Serial.println("Unknown command: " + command);
      }

      Serial.println();
    }
  }
}