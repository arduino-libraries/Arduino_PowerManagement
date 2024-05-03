#include "Battery.h"
#include "PF1550.h"
#include "WireUtils.h"
#include "BatteryConstants.h"

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

  awaitDataReady();
  uint16_t tempHibernateConfigRegister = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, HIB_CFG_REG);
  releaseFromHibernation();
  configureBatteryCharacteristics();

  if(!refreshBatteryGaugeModel()){
    return false;
  }
  
  // Restore the original Hibernate Config Register value
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, HIB_CFG_REG, tempHibernateConfigRegister); // Restore Original HibCFG value
  replaceRegisterBit(this->wire, FUEL_GAUGE_ADDRESS, STATUS_REG, 0x0, POR_BIT); // Clear POR bit after reset
  return true;
}

void Battery::awaitDataReady(){
  while (true){
    bool dataIsReady = getBit(this->wire, FUEL_GAUGE_ADDRESS, F_STAT_REG, DNR_BIT) == 0;
    if (dataIsReady) {
      return;
    }
    Serial.println("Waiting for the battery gauge to be ready...");
    delay(100); // Wait for the data to be ready. This takes 710ms from power-up
  } 
}

void Battery::configureBatteryCharacteristics(){
  uint16_t designCapacity = static_cast<uint16_t>(characteristics.capacity / CAPACITY_MULTIPLIER_MAH);
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, DESIGN_CAP_REG, designCapacity);

  uint16_t terminationCurrent = static_cast<uint16_t>(characteristics.endOfChargeCurrent / CURRENT_MULTIPLIER_MA);
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, I_CHG_TERM_REG, terminationCurrent);
  
  uint16_t emptyVoltageValue = static_cast<uint16_t>((characteristics.emptyVoltage * 1000) / EMPTY_VOLTAGE_MULTIPLIER_MV);
  uint8_t recoveryVoltageValue = static_cast<uint8_t>((characteristics.recoveryVoltage * 1000) / RECOVERY_VOLTAGE_MULTIPLIER_MV);
  uint16_t emptyVoltageRegisterValue = emptyVoltageValue << 7 | recoveryVoltageValue;
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, V_EMPTY_REG, emptyVoltageRegisterValue);
}

void Battery::releaseFromHibernation(){
  // See section "Soft-Wakeup" in user manual https://www.analog.com/media/en/technical-documentation/user-guides/max1726x-modelgauge-m5-ez-user-guide.pdf
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, HIB_CFG_REG, 0x0);      // Exit Hibernate Mode
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, SOFT_WAKEUP_REG, 0x90); // Wakes up the fuel gauge from hibernate mode to reduce the response time of the IC to configuration changes  
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, SOFT_WAKEUP_REG, 0x0);  // This command must be manually cleared (0000h) afterward to keep proper fuel gauge timing
}

bool Battery::refreshBatteryGaugeModel(){
  uint16_t registerValue = 1 << MODEL_CFG_REFRESH_BIT;
  
  // Set NTC resistor option for 100k resistor
  if (characteristics.ntcResistor == NTCResistor::Resistor100K) {
    registerValue |= 1 << R100_BIT;
  }

  // Set the charge voltage option for voltages above 4.25V according to the datasheet
  if(characteristics.chargeVoltage > 4.25f) {
    // Set bit 10 to 1
    registerValue |= 1 << VCHG_BIT;
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

float Battery::minimumVoltage(){
  if(!isConnected()){
    return -1;
  }
  uint16_t maxMinVoltageRegisterValue = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, MAXMIN_VOLT_REG);
  uint8_t minimumVoltageValue = maxMinVoltageRegisterValue & 0xFF; // The minimum voltage is stored in the lower byte
  return (minimumVoltageValue * MAXMIN_VOLT_MULTIPLIER_MV) / 1000.0f;
}

float Battery::maximumVoltage(){
  if(!isConnected()){
    return -1;
  }
  uint16_t maxMinVoltageRegisterValue = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, MAXMIN_VOLT_REG);
  uint8_t maximumVoltageValue = maxMinVoltageRegisterValue >> 8; // The maximum voltage is stored in the upper byte
  return (maximumVoltageValue * MAXMIN_VOLT_MULTIPLIER_MV) / 1000.0f;
}

bool Battery::resetMaximumMinimumVoltage(){
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, MAXMIN_VOLT_REG, MAXMIN_VOLT_INITIAL_VALUE) == 0;
}

void Battery::setTemperatureMeasurementMode(bool externalTemperature){
  uint16_t configRegister = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, CONFIG_REG);
  uint8_t tselValue = bitRead(configRegister, TSEL_BIT);
  uint8_t ethrmValue = bitRead(configRegister, ETHRM_BIT);
  uint8_t tenValue = bitRead(configRegister, TEN_BIT);

  // TSEL value 0: internal die temperature, 1: thermistor temperature
  if(!externalTemperature && tselValue == 0 && tenValue == 1){
    // Serial.println("Temperature measurement mode is already set to internal die temperature.");
    return; // No need to change the configuration
  }

  // ETHRM bit must be set to 1 when TSel is 1.
  if(externalTemperature && tselValue == 1 && ethrmValue == 1 && tenValue == 1){
    // Serial.println("Temperature measurement mode is already set to external thermistor temperature.");
    return; // No need to change the configuration
  }

  if(externalTemperature){
    configRegister = bitSet(configRegister, TSEL_BIT);
    configRegister = bitSet(configRegister, ETHRM_BIT);
    // FIXME: The external thermistor temperature measurement is not working as expected
    // In oder to support this, probably more configuration is needed
    // Currently after taking the first reading, the battery gets reported as disconnected
    // plus the register value is reset to the default value.
  } else {
    configRegister = bitClear(configRegister, TSEL_BIT);
    configRegister = bitClear(configRegister, ETHRM_BIT);
  }

  // Enable temperature channel for both modes. 
  // It's not clear if this is necessary for the internal die temperature, but it's enabled by default.
  configRegister = bitSet(configRegister, TEN_BIT);

  uint16_t status2RegisterValue = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, STATUS2_REG);
  bool isInHibernateMode = bitRead(status2RegisterValue, HIB_BIT) == 1;
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, CONFIG_REG, configRegister);
  
  // Wait for the configuration to be updated
  // This takes 175ms in active mode, and 5.6 seconds in hibernate mode by default
  if(isInHibernateMode){
    delay(5700); // Wait a bit longer to ensure the configuration is updated
  } else {
    delay(250); // Wait a bit longer to ensure the configuration is updated
  }

}

int Battery::internalTemperature(){
  if(!isConnected()){
    return -1;
  }

  setTemperatureMeasurementMode(false);
  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, TEMP_REG) * TEMPERATURE_MULTIPLIER_C;
}

int Battery::averageInternalTemperature(){
  if(!isConnected()){
    return -1;
  }

  setTemperatureMeasurementMode(false);
  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, AVG_TA_REG) * TEMPERATURE_MULTIPLIER_C;
}

int Battery::batteryTemperature(){
  if(!isConnected()){
    return -1;
  }

  setTemperatureMeasurementMode(true);
  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, TEMP_REG) * TEMPERATURE_MULTIPLIER_C;
}

int Battery::averageBatteryTemperature(){
  if(!isConnected()){
    return -1;
  }

  setTemperatureMeasurementMode(true);
  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, AVG_TA_REG) * TEMPERATURE_MULTIPLIER_C;
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

  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, REP_SOC_REG) * PERCENTAGE_MULTIPLIER;
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

int Battery::fullCapacity(){
  if(!isConnected()){
    return -1;
  }

  if(characteristics.capacity == 0){
    return -1;
  }
  
  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, FULL_CAP_REP_REG) * CAPACITY_MULTIPLIER_MAH;
}

bool Battery::isEmpty(){  
  return getBit(this->wire, FUEL_GAUGE_ADDRESS, F_STAT_REG, E_DET_BIT) == 1;
}

// FIXME The battery is not detected as fully charged for some reason
bool Battery::isFullyCharged(){
  return getBit(this->wire, FUEL_GAUGE_ADDRESS, STATUS2_REG, FULL_DET_BIT) == 1;
}

int Battery::timeToEmpty(){
  if(!isConnected()){
    return -1;
  }

  int16_t current = this->averageCurrent();
  if(current >= 0){
    return -1; // The battery is charging, so the time to empty is not valid
  }

  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, TTE_REG) * TIME_MULTIPLIER_S;
}

int Battery::timeToFull(){
  if(!isConnected()){
    return -1;
  }

  int16_t current = this->averageCurrent();
  if(current <= 0){
    return -1; // The battery is discharging, so the time to full is not valid
  }

  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, TTF_REG) * TIME_MULTIPLIER_S;
}
