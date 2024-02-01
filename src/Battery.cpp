#ifndef Battery_H
#define Battery_H



#include "Battery.h"

Battery::Battery() {
}

Battery::Battery(int capacityInMilliAmpereHours, int emptyVoltageInMilliVolts) {
  batteryCapacityInMiliampereHours = capacityInMilliAmpereHours;
  batteryEmptyVoltage = emptyVoltageInMilliVolts;
}

bool Battery::begin(){
    if(readBitFromRegister(this->wire, fuelGaugeAddress, STATUS_REG, POR_BIT)){

      uint16_t tempHibCfgReg = readRegister16(this->wire, fuelGaugeAddress, HIB_CFG_REG);

      // release from hibernation
      writeRegister16(this->wire, fuelGaugeAddress, SOFT_WAKEUP_REG, 0x90); // Exit Hibernate Mode step 1
      writeRegister16(this->wire, fuelGaugeAddress, HIB_CFG_REG, 0x0);      // Exit Hibernate Mode step 2
      writeRegister16(this->wire, fuelGaugeAddress, SOFT_WAKEUP_REG, 0x0);  // Exit Hibernate Mode step 3


      // set battery configuration
      writeRegister16(this->wire, fuelGaugeAddress, V_EMPTY_REG, (uint16_t)(batteryEmptyVoltage / VOLTAGE_MULTIPLIER)); 
      writeRegister16(this->wire, fuelGaugeAddress, DESIGN_CAP_REG, (uint16_t)(batteryCapacityInMiliampereHours / CAP_MULTIPLIER));
      writeRegister16(this->wire, fuelGaugeAddress, I_CHG_TERM_REG, (uint16_t)(101 / CURRENT_MULTIPLIER));


      writeRegister16(this->wire, fuelGaugeAddress, MODEL_CFG_REG, 0x8000);                    // Write ModelCFG


      writeRegister16(this->wire, fuelGaugeAddress, HIB_CFG_REG, tempHibCfgReg); // Restore Original HibCFG value
      replaceRegisterBits(this->wire, fuelGaugeAddress, STATUS_REG, 0, 0x01, POR_BIT);
  }
}


bool Battery::isConnected(){
  uint16_t statusRegister = readRegister16(this->wire, fuelGaugeAddress, STATUS_REG);
  return getBitFromOffset(statusRegister, BATTERY_STATUS_BIT) == 0;
}


int Battery::voltage(){
  if(isConnected()){
    return readRegister16(this->wire, fuelGaugeAddress, VCELL_REG) * VOLTAGE_MULTIPLIER;
  } else {
    return -1;
  }
}

unsigned int Battery::averageVoltage(){
  if(isConnected()){
      return readRegister16(this->wire, fuelGaugeAddress, AVG_VCELL_REG) * VOLTAGE_MULTIPLIER;
  } else {
    return -1;
  }
}

int Battery::temperature(){
  if(isConnected()){
    return readRegister16(this->wire, fuelGaugeAddress, TEMP_REG) >> 8;
  } else {
    return -1;
  }
}

int Battery::temperatureAverage(){
  if(isConnected()){
    return readRegister16(this->wire, fuelGaugeAddress, AVG_TA_REG) >> 8;
  } else {
    return -1;
  }
  
}

int Battery::current(){
  if(isConnected()){
    return (int16_t)readRegister16(this->wire, fuelGaugeAddress, CURRENT_REG) * CURRENT_MULTIPLIER;
  } else {
    return -1;
  }
}

int Battery::averageCurrent(){
  if(isConnected()){
      return (int16_t)readRegister16(this->wire, fuelGaugeAddress, AVG_CURRENT_REG) * CURRENT_MULTIPLIER;
  } else {
    return -1;
  }
}

int Battery::percentage(){
  if(isConnected()){
      return readRegister16(this->wire, fuelGaugeAddress, AV_SOC_REG) >> 8;
  } else {
    return -1;
  }

}

 int Battery::remainingCapacity(){
  if(isConnected()){
    return readRegister16(this->wire, fuelGaugeAddress, REP_CAP_REG) * CAP_MULTIPLIER;
  } else {
    return -1;
  }
}



#endif