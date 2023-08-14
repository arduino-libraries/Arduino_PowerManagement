#ifndef Battery_H
#define Battery_H

#define CAPACITY 200
#define V_EMPTY 3000

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

unsigned int Battery::readVoltage(){
  return readRegister16(this->_wire, DEVICE_ADDRESS, VCELL_REG) * VOLTAGE_MULTIPLIER;

}

unsigned int Battery::readVoltageAvg(){
  return readRegister16(this->_wire, DEVICE_ADDRESS, AVG_VCELL_REG) * VOLTAGE_MULTIPLIER;
}

int Battery::readTemp(){
  return readRegister16(this->_wire, DEVICE_ADDRESS, TEMP_REG) >> 8;

}

int Battery::readTempAvg(){
  return readRegister16(this->_wire, DEVICE_ADDRESS, AVG_TA_REG) >> 8;

}

int Battery::readCurrent(){
  return (int16_t)readRegister16(this->_wire, DEVICE_ADDRESS, CURRENT_REG) * CURRENT_MULTIPLIER;

}

int Battery::readCurrentAvg(){
  return (int16_t)readRegister16(this->_wire, DEVICE_ADDRESS, AVG_CURRENT_REG) * CURRENT_MULTIPLIER;

}

unsigned int Battery::readPercentage(){
  return readRegister16(this->_wire, DEVICE_ADDRESS, AV_SOC_REG) >> 8;
}

unsigned int Battery::readTimeToEmpty()
{
  return readRegister16(this->_wire, DEVICE_ADDRESS, TTE_REG) * TIME_MULTIPLIER / 60000;
}

unsigned int Battery::readTimeToFull()
{
  return readRegister16(this->_wire, DEVICE_ADDRESS, TTF_REG) * (TIME_MULTIPLIER / 60000);
}

unsigned int Battery::readRemainingCapacity()
{
  return readRegister16(this->_wire, DEVICE_ADDRESS, REP_CAP_REG) * CAP_MULTIPLIER;
}

unsigned int Battery::readReportedCapacity()
{
  return readRegister16(this->_wire, DEVICE_ADDRESS, FULL_CAP_REP_REG) * CAP_MULTIPLIER;
}


#endif