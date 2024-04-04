#include "Battery.h"
#include "PF1550.h"

Battery::Battery() {
  Battery(BatteryCharacteristics());
}

Battery::Battery(BatteryCharacteristics batteryCharacteristics) : characteristics(batteryCharacteristics) {
}

bool Battery::begin(bool enforceReload) {
  if(PMIC.begin() != 0){
    return false;
  }

  // If hardware / software power-on-reset (POR) event has occurred, reconfigure the battery gauge, otherwise, skip the configuration
  if (!enforceReload && getBit(this->wire, FUEL_GAUGE_ADDRESS, STATUS_REG, POR_BIT) != 1) {
    return true;
  }

  Serial.println("Reconfiguring the battery gauge...");

  while (true){
    bool dataIsReady = getBit(this->wire, FUEL_GAUGE_ADDRESS, F_STAT_REG, DNR_BIT) == 0;
    if (dataIsReady) {
      break;
    }
    Serial.println("Waiting for the battery gauge to be ready...");
    delay(100); // Wait for the data to be ready. This takes 710ms from power-up
  }

  // See section "Soft-Wakeup" in user manual https://www.analog.com/media/en/technical-documentation/user-guides/max1726x-modelgauge-m5-ez-user-guide.pdf

  uint16_t tempHibernateConfigRegister = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, HIB_CFG_REG);

  // Release from hibernation
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, HIB_CFG_REG, 0x0);      // Exit Hibernate Mode
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, SOFT_WAKEUP_REG, 0x90); // Wakes up the fuel gauge from hibernate mode to reduce the response time of the IC to configuration changes  
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, SOFT_WAKEUP_REG, 0x0);  // This command must be manually cleared (0000h) afterward to keep proper fuel gauge timing

  // Set the battery characteristics
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, DESIGN_CAP_REG, characteristics.capacity / CAPACITY_MULTIPLIER_MAH);
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, I_CHG_TERM_REG, characteristics.endOfChargeCurrent / CURRENT_MULTIPLIER_MA);
  
  uint16_t emptyVoltageValue = (uint16_t)((characteristics.emptyVoltage * 1000) / EMPTY_VOLTAGE_MULTIPLIER_MV);
  uint8_t recoveryVoltageValue = (uint8_t)((characteristics.recoveryVoltage * 1000) / RECOVERY_VOLTAGE_MULTIPLIER_MV);
  uint16_t emptyVoltageRegisterValue = emptyVoltageValue << 7 | recoveryVoltageValue;
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, V_EMPTY_REG, emptyVoltageRegisterValue);

  if(!refreshBatteryGaugeModel()){
    return false;
  }
  
  // Restore the original Hibernate Config Register value
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, HIB_CFG_REG, tempHibernateConfigRegister); // Restore Original HibCFG value
  replaceRegisterBit(this->wire, FUEL_GAUGE_ADDRESS, STATUS_REG, 0x0, POR_BIT); // Clear POR bit after reset
  return true;
}

bool Battery::refreshBatteryGaugeModel(){
  uint16_t registerValue = 1 << MODEL_CFG_REFRESH_BIT;
  
  // Set NTC resistor option for 100k resistor
  if (characteristics.ntcResistor == NTCResistor::Resistor100K) {
    registerValue |= 1 << R100_BIT;
  }

  // Set the charge voltage option for voltages above 4.25V
  if(characteristics.chargeVoltage > 4.25f) {
    // Set bit 10 to 1
    registerValue |= 1 << 10;
  }

  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, MODEL_CFG_REG, registerValue);
  unsigned long startTime = millis();

  while (true) {
    // Read back the model configuration register to ensure the refresh bit is cleared
    bool refreshComplete = getBit(this->wire, FUEL_GAUGE_ADDRESS, MODEL_CFG_REG, MODEL_CFG_REFRESH_BIT) == 0;
    if (refreshComplete) {
      return true; // Exit the loop if the refresh bit is cleared
    }
    
    if (millis() - startTime > 1000) {
      return false; // Exit the loop if the refresh bit is not cleared after 1 second
    }
    delay(10);
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
  
  auto voltageInMV = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, VCELL_REG) * VOLTAGE_MULTIPLIER_MV;
  return voltageInMV / 1000.0f;
}

float Battery::averageVoltage(){
  if(!isConnected()){
    return -1;
  }
  
  auto voltageInMV = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, AVG_VCELL_REG) * VOLTAGE_MULTIPLIER_MV;
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
  
  return (int16_t)readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, CURRENT_REG) * CURRENT_MULTIPLIER_MA;
}

int Battery::averageCurrent(){
  if(!isConnected()){
    return -1;
  }

  return (int16_t)readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, AVG_CURRENT_REG) * CURRENT_MULTIPLIER_MA;
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
  
  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, REP_CAP_REG) * CAPACITY_MULTIPLIER_MAH;
}

bool Battery::isEmpty(){  
  return getBit(this->wire, FUEL_GAUGE_ADDRESS, STATUS_REG, E_DET_BIT) == 1;
}
