#include "Battery.h"
#include "PF1550.h"

Battery::Battery() {
  Battery(BatteryCharacteristics());
}

Battery::Battery(BatteryCharacteristics batteryCharacteristics) : characteristics(batteryCharacteristics) {
}


bool Battery::begin() {
  if(PMIC.begin() != 0){
    return false;
  }

  // If power-on-reset (POR) event has occurred, reconfigure the battery gauge, otherwise, skip the configuration
  if (getBit(this->wire, FUEL_GAUGE_ADDRESS, STATUS_REG, POR_BIT) != 1) {
    return true;
  }

  uint16_t tempHibernateConfigRegister = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, HIB_CFG_REG);

  // Release from hibernation
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, SOFT_WAKEUP_REG, 0x90); // Exit Hibernate Mode step 1
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, HIB_CFG_REG, 0x0);      // Exit Hibernate Mode step 2
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, SOFT_WAKEUP_REG, 0x0);  // Exit Hibernate Mode step 3

  // Set the empty voltage
  uint16_t emptyVoltageValue = (uint16_t)((characteristics.emptyVoltage * 1000) / VOLTAGE_MULTIPLIER);
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, V_EMPTY_REG, emptyVoltageValue);

  // Set the battery capacity
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, DESIGN_CAP_REG, (uint16_t)(characteristics.capacity / CAP_MULTIPLIER));

  // Set the charge termination current
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, I_CHG_TERM_REG, (uint16_t)(5 / CURRENT_MULTIPLIER));

  if(!refreshBatteryGaugeModel()){
    return false;
  }

  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, HIB_CFG_REG, tempHibernateConfigRegister); // Restore Original HibCFG value
  replaceRegisterBit(this->wire, FUEL_GAUGE_ADDRESS, STATUS_REG, 0, POR_BIT); // Clear POR bit after reset
  return true;
}

bool Battery::refreshBatteryGaugeModel(){
  // uint16_t currentRegisterValue = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, MODEL_CFG_REG);

  // if(characteristics.chargeVoltage > 4.275f) {
  //   // Set bit 10 to 1
  //   currentRegisterValue |= 1 << 10;
  // } else {
  //   // Set bit 10 to 0
  //   currentRegisterValue &= ~(1 << 10);
  // }

  // // Set bit MODEL_CFG_REFRESH_BIT to 1
  // currentRegisterValue |= 1 << MODEL_CFG_REFRESH_BIT;

  // writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, MODEL_CFG_REG, currentRegisterValue);
  replaceRegisterBit(this->wire, FUEL_GAUGE_ADDRESS, MODEL_CFG_REG, 1, MODEL_CFG_REFRESH_BIT);

  unsigned long startTime = millis();

  while (true) {
    // Read back the model configuration register to ensure the refresh bit is cleared
    bool isRefreshBitSet = getBit(this->wire, FUEL_GAUGE_ADDRESS, MODEL_CFG_REG, MODEL_CFG_REFRESH_BIT) == 1;
    if (!isRefreshBitSet) {
      return true; // Exit the loop if the refresh bit is cleared
    }
    
    if (millis() - startTime > 2000) {
      return false; // Exit the loop if the refresh bit is not cleared after 2 seconds
    }
    delay(1);
  }
}

bool Battery::isConnected(){
  uint16_t statusRegister = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, STATUS_REG);
  return bitRead(statusRegister, BATTERY_STATUS_BIT) == 0;
}

float Battery::voltage(){
  if(!isConnected()){
    return -1;
  }
  
  auto voltageInMV = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, VCELL_REG) * VOLTAGE_MULTIPLIER;
  return voltageInMV / 1000.0f;
}

float Battery::averageVoltage(){
  if(!isConnected()){
    return -1;
  }
  
  auto voltageInMV = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, AVG_VCELL_REG) * VOLTAGE_MULTIPLIER;
  return voltageInMV / 1000.0f;
}

int Battery::temperature(){
  if(!isConnected()){
    return -1;
  }

  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, TEMP_REG) >> 8;
}

int Battery::averageTemperature(){
  if(!isConnected()){
    return -1;
  }

  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, AVG_TA_REG) >> 8;
}

int Battery::current(){
  if(!isConnected()){
    return -1;
  }
  
  return (int16_t)readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, CURRENT_REG) * CURRENT_MULTIPLIER;
}

int Battery::averageCurrent(){
  if(!isConnected()){
    return -1;
  }

  return (int16_t)readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, AVG_CURRENT_REG) * CURRENT_MULTIPLIER;
}

int Battery::percentage(){
  if(!isConnected()){
    return -1;
  }

  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, AV_SOC_REG) >> 8;
}

 int Battery::remainingCapacity(){
  if(!isConnected()){
    return -1;
  }
  
  if(characteristics.capacity == 0){
    return -1;
  }
  
  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, REP_CAP_REG) * CAP_MULTIPLIER;
}
