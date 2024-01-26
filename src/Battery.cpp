#ifndef Battery_H
#define Battery_H

#define CAPACITY 200
#define V_EMPTY 3000

#define BATTERY_STATUS_BIT 3 

#include "Battery.h"

Battery::Battery() {



}

void Battery::begin(){

    if(readBitFromRegister(this->wire, DEVICE_ADDRESS, STATUS_REG, POR_BIT)){

      uint16_t tempHibCfgReg = readRegister16(this->wire, DEVICE_ADDRESS, HIB_CFG_REG);

      // release from hibernation
      writeRegister16(this->wire, DEVICE_ADDRESS, SOFT_WAKEUP_REG, 0x90); // Exit Hibernate Mode step 1
      writeRegister16(this->wire, DEVICE_ADDRESS, HIB_CFG_REG, 0x0);      // Exit Hibernate Mode step 2
      writeRegister16(this->wire, DEVICE_ADDRESS, SOFT_WAKEUP_REG, 0x0);  // Exit Hibernate Mode step 3


      // set battery configuration
      writeRegister16(this->wire, DEVICE_ADDRESS, V_EMPTY_REG, (uint16_t)(V_EMPTY / VOLTAGE_MULTIPLIER)); 
      writeRegister16(this->wire, DEVICE_ADDRESS, DESIGN_CAP_REG, (uint16_t)(CAPACITY / CAP_MULTIPLIER));
      writeRegister16(this->wire, DEVICE_ADDRESS, I_CHG_TERM_REG, (uint16_t)(101 / CURRENT_MULTIPLIER));


      writeRegister16(this->wire, DEVICE_ADDRESS, MODEL_CFG_REG, 0x8000);                    // Write ModelCFG

      // do not continue until ModelCFG.Refresh==0
      /*
      while (readBitFromRegister(this->wire, DEVICE_ADDRESS, MODEL_CFG_REG, MODEL_CFG_REFRESH_BIT)==0) {
         delay(10);
         Serial.println("waiting for config to be set");
      }
      */


      Serial.println("done");
      writeRegister16(this->wire, DEVICE_ADDRESS, HIB_CFG_REG, tempHibCfgReg); // Restore Original HibCFG value
      replaceRegisterBits(this->wire, DEVICE_ADDRESS, STATUS_REG, 0, 0x01, POR_BIT);
  }
}


bool Battery::isConnected(){
  uint16_t statusRegister = readRegister16(this->wire, DEVICE_ADDRESS, STATUS_REG);
  return getBitFromOffset(statusRegister, BATTERY_STATUS_BIT) == 0;
}


unsigned int Battery::voltage(){
  if(isConnected()){
    return readRegister16(this->wire, DEVICE_ADDRESS, VCELL_REG) * VOLTAGE_MULTIPLIER;
  } else {
    return 0;
  }
}

unsigned int Battery::voltageAverage(){
  if(isConnected()){
      return readRegister16(this->wire, DEVICE_ADDRESS, AVG_VCELL_REG) * VOLTAGE_MULTIPLIER;
  } else {
    return 0;
  }
}

int Battery::temperature(){
  if(isConnected()){
    return readRegister16(this->wire, DEVICE_ADDRESS, TEMP_REG) >> 8;
  } else {
    return 0;
  }
}

int Battery::temperatureAverage(){
  if(isConnected()){
    return readRegister16(this->wire, DEVICE_ADDRESS, AVG_TA_REG) >> 8;
  } else {
    return 0;
  }
  
}

int Battery::current(){
  if(isConnected()){
    return (int16_t)readRegister16(this->wire, DEVICE_ADDRESS, CURRENT_REG) * CURRENT_MULTIPLIER;
  } else {
    return 0;
  }
}

int Battery::currentAverage(){
  if(isConnected()){
      return (int16_t)readRegister16(this->wire, DEVICE_ADDRESS, AVG_CURRENT_REG) * CURRENT_MULTIPLIER;
  } else {
    return 0;
  }
}

unsigned int Battery::percentage(){
  if(isConnected()){
      return readRegister16(this->wire, DEVICE_ADDRESS, AV_SOC_REG) >> 8;
  } else {
    return 0;
  }

}


unsigned int Battery::remainingCapacity(){
  if(isConnected()){
    return readRegister16(this->wire, DEVICE_ADDRESS, REP_CAP_REG) * CAP_MULTIPLIER;
  } else {
    return 0;
  }
}



#endif