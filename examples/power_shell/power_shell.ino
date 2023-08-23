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
            Serial1.println("precharge");
            // Additional code specific to precharge
            break;
        case FAST_CHARGE_CC:
            Serial1.println("fast-charge constant current");
            // Additional code specific to fast-charge CC
            break;
        case FAST_CHARGE_CV:
            Serial1.println("fast-charge constant voltage");
            // Additional code specific to fast-charge CV
            break;
        case END_OF_CHARGE:
            Serial1.println("end-of-charge");
            // Additional code specific to end-of-charge
            break;
        case DONE:
            Serial1.println("done");
            // Additional code specific to done
            break;
        case TIMER_FAULT:
            Serial1.println("timer fault");
            // Additional code specific to timer fault
            break;
        case THERMISTOR_SUSPEND:
            Serial1.println("thermistor suspend");
            // Additional code specific to thermistor suspend
            break;
        case OFF:
            Serial1.println("off");
            // Additional code specific to off
            break;
        case BATTERY_OVERVOLTAGE:
            Serial1.println("overvoltage condition");
            // Additional code specific to battery overvoltage condition
            break;
        case LINEAR_ONLY:
            Serial1.println("disabled");
            // Additional code specific to linear only
            break;
        default:
            Serial1.println("unknown");
            // Additional code for handling unknown status
            break;
    }
}

void status(){
    
  Serial1.println("BOARD: \n--------------------------");
  Serial1.print("* Powered by usb: "); Serial1.println(board.isUSBPowered());
  Serial1.print("* Powered by battery: "); Serial1.println(board.isBatteryPowered()); 
  Serial1.println();
  
  Serial1.println("CHARGER: \n--------------------------");
  Serial1.print("* Charger status: "); printChargerStatus();
  Serial1.println();

  Serial1.println("BATTERY: \n--------------------------");
  Serial1.println(
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
      if(board.setReferenceVoltage(voltage)) Serial1.println("Succesfully changed reference voltage");
      else Serial1.println("Failed to set reference voltage");
    #else
      Serial1.println("Current board is not an arduino portenta c33");
    #endif
  } else if (rail == "C33_analog"){
    #if defined(ARDUINO_PORTENTA_C33)
      if(board.setAnalogVoltage(voltage)) Serial1.println("Succesfully set analog voltage");
      else Serial1.println("Failed to set analog voltage");
    #else
      Serial1.println("Current board is not an arduino portenta c33");
    #endif

  } else if (rail == "C33_external"){
    #if defined(ARDUINO_PORTENTA_C33)
      if(board.setExternalVoltage(voltage)) Serial1.println("Succesfully set external voltage");
      else Serial1.println("Failed to set external voltage");
    #else
      Serial1.println("Current board is not an arduino portenta c33");
    #endif

  } else if (rail == "H7_external"){
    #if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4)
      board.setExternalVoltage(voltage);
    #else
      Serial1.println("Current board is not an arduino portenta h7");
    #endif

  } else if (rail == "nicla_external"){
    #if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4)
      board.setExternalVoltage(voltage);
    #else
      Serial1.println("Current board is not an arduino nicla vision");
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
      Serial1.println("Current board is not an arduino portenta c33");
    #endif

  } else if (rail == "C33_communication"){
    #if defined(ARDUINO_PORTENTA_C33)
      board.setCommunicationSwitch(on);
    #else
      Serial1.println("Current board is not an arduino portenta c33");
    #endif

  } else if (rail == "H7_external"){
    #if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4)
      board.setExternalSwitch(on);
    #else
      Serial1.println("Current board is not an arduino portenta h7");
    #endif

  } else if (rail == "nicla_external"){
    #if defined(ARDUINO_NICLA_VISION)
     board.setExternalSwitch(on);
    #else
      Serial1.println("Current board is not an arduino nicla vision");
    #endif

  } else if (rail == "nicla_camera"){
    #if defined(ARDUINO_NICLA_VISION)
     board.setCameraSwitch(on);
    #else
      Serial1.println("Current board is not an arduino nicla vision");
    #endif
  }
}

void toggleCharger(std::vector<String> args){
  bool on = atoi(args[1].c_str()) == 1;
  Serial1.println(on);


  if(on){
    if(charger.enableCharger()){
      Serial1.println("> Charger enabled");
    } else {
      Serial1.println("> Error enabling charger");
    }

  } else {
    charger.disableCharger();
    Serial1.println("> Charger disabled");
  }
}



void setup() {
  Serial1.begin(115200);
  while (!Serial1);

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
  if (Serial1.available() > 0) {
    String input = Serial1.readString();
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
        Serial1.println("Unknown command: " + command);
      }

      Serial1.println();
    }
  }
}