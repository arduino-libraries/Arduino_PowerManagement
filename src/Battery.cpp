#ifndef Battery_H
#define Battery_H

#define CAPACITY 200
#define V_EMPTY 3000

#define BATTERY_STATUS_BIT 3 

#include "Battery.h"

Battery::Battery() {



}

void Battery::begin(){
    if(readBitFromRegister(this->_wire, DEVICE_ADDRESS, STATUS_REG, POR_BIT)){
      Serial.println("Por bit is set...");

      uint16_t tempHibCfgReg = readRegister16(this->_wire, DEVICE_ADDRESS, HIB_CFG_REG);

      // release from hibernation
      writeRegister16(this->_wire, DEVICE_ADDRESS, SOFT_WAKEUP_REG, 0x90); // Exit Hibernate Mode step 1
      writeRegister16(this->_wire, DEVICE_ADDRESS, HIB_CFG_REG, 0x0);      // Exit Hibernate Mode step 2
      writeRegister16(this->_wire, DEVICE_ADDRESS, SOFT_WAKEUP_REG, 0x0);  // Exit Hibernate Mode step 3
      Serial.println("returning from hibernation");

      // set battery configuration
      writeRegister16(this->_wire, DEVICE_ADDRESS, V_EMPTY_REG, (uint16_t)(V_EMPTY / VOLTAGE_MULTIPLIER)); 
      writeRegister16(this->_wire, DEVICE_ADDRESS, DESIGN_CAP_REG, (uint16_t)(CAPACITY / CAP_MULTIPLIER));
      writeRegister16(this->_wire, DEVICE_ADDRESS, I_CHG_TERM_REG, (uint16_t)(101 / CURRENT_MULTIPLIER));
      Serial.println("setting battery configuration");

      writeRegister16(this->_wire, DEVICE_ADDRESS, MODEL_CFG_REG, 0x8000);                    // Write ModelCFG

      // do not continue until ModelCFG.Refresh==0
      /*
      while (readBitFromRegister(this->_wire, DEVICE_ADDRESS, MODEL_CFG_REG, MODEL_CFG_REFRESH_BIT)==0) {
         delay(10);
         Serial.println("waiting for config to be set");
      }
      */

      writeRegister16(this->_wire, DEVICE_ADDRESS, HIB_CFG_REG, tempHibCfgReg); // Restore Original HibCFG value
      replaceRegisterBits(this->_wire, DEVICE_ADDRESS, STATUS_REG, 0, 0x01, POR_BIT);

      Serial.println("done");
  }
}


bool Battery::isConnected(){
  uint16_t statusRegister = readRegister16(this->_wire, DEVICE_ADDRESS, STATUS_REG);
  //Serial.println("Insertion bit: " +  String(getBitFromOffset(statusRegister, BATTERY_STATUS_BIT)));
  //replaceRegisterBits(this->_wire, DEVICE_ADDRESS, STATUS_REG, 0, 0x01, 11);
  //Serial.println("Removal bit: " + String(getBitFromOffset(statusRegister, BATTERY_STATUS_BIT)));
  //replaceRegisterBits(this->_wire, DEVICE_ADDRESS, STATUS_REG, 0, 0x01, 15);
  return getBitFromOffset(statusRegister, BATTERY_STATUS_BIT) == 0;
}


unsigned int Battery::readVoltage(){
  if(isConnected()){
    return readRegister16(this->_wire, DEVICE_ADDRESS, VCELL_REG) * VOLTAGE_MULTIPLIER;
  } else {
    return 0;
  }
}

unsigned int Battery::readVoltageAvg(){
  if(isConnected()){
      return readRegister16(this->_wire, DEVICE_ADDRESS, AVG_VCELL_REG) * VOLTAGE_MULTIPLIER;
  } else {
    return 0;
  }
}

int Battery::readTemp(){
  if(isConnected()){
    return readRegister16(this->_wire, DEVICE_ADDRESS, TEMP_REG) >> 8;
  } else {
    return 0;
  }
}

int Battery::readTempAvg(){
  if(isConnected()){
    return readRegister16(this->_wire, DEVICE_ADDRESS, AVG_TA_REG) >> 8;
  } else {
    return 0;
  }
  
}

int Battery::readCurrent(){
  if(isConnected()){
    return (int16_t)readRegister16(this->_wire, DEVICE_ADDRESS, CURRENT_REG) * CURRENT_MULTIPLIER;
  } else {
    return 0;
  }
}

int Battery::readCurrentAvg(){
  if(isConnected()){
      return (int16_t)readRegister16(this->_wire, DEVICE_ADDRESS, AVG_CURRENT_REG) * CURRENT_MULTIPLIER;
  } else {
    return 0;
  }
}

unsigned int Battery::readPercentage(){
  if(isConnected()){
      return readRegister16(this->_wire, DEVICE_ADDRESS, AV_SOC_REG) >> 8;
  } else {
    return 0;
  }

}

unsigned int Battery::readTimeToEmpty(){
  if(isConnected()){
     return readRegister16(this->_wire, DEVICE_ADDRESS, TTE_REG) * TIME_MULTIPLIER / 60000;
  } else {
    return 0;
  }
 
}

unsigned int Battery::readTimeToFull(){
  if(isConnected()){
    return readRegister16(this->_wire, DEVICE_ADDRESS, TTF_REG) * (TIME_MULTIPLIER / 60000);
  } else {
    return 0;
  }
 
}

unsigned int Battery::readRemainingCapacity(){
  if(isConnected()){
    return readRegister16(this->_wire, DEVICE_ADDRESS, REP_CAP_REG) * CAP_MULTIPLIER;
  } else {
    return 0;
  }
}

unsigned int Battery::readReportedCapacity(){
  if(isConnected()){
    return readRegister16(this->_wire, DEVICE_ADDRESS, FULL_CAP_REP_REG) * CAP_MULTIPLIER;
  } else {
    return 0;
  }
}


#endif