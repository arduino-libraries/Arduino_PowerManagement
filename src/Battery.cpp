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
  // PMIC already initializes the I2C bus, so no need to call Wire.begin() for the fuel gauge
  if(PMIC.begin() != 0){
    return false;
  }

  // If hardware / software power-on-reset (POR) event has occurred, reconfigure the battery gauge, otherwise, skip the configuration
  if (!enforceReload && getBit(this->wire, FUEL_GAUGE_ADDRESS, STATUS_REG, POR_BIT) != 1) {
    return true;
  }

  if(!awaitDataReady()){
    return false; // Timeout while waiting for the battery gauge to be ready
  }

  uint16_t tempHibernateConfigRegister = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, HIB_CFG_REG);
  releaseFromHibernation();
  configureBatteryCharacteristics();

  if(!refreshBatteryGaugeModel()){
    return false;
  }
  
  // Restore the original Hibernate Config Register value
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, HIB_CFG_REG, tempHibernateConfigRegister); // Restore Original HibCFG value
  replaceRegisterBit(this->wire, FUEL_GAUGE_ADDRESS, STATUS_REG, POR_BIT, 0x0); // Clear POR bit after reset
  return true;
}

bool Battery::awaitDataReady(uint16_t timeout){
  unsigned long startTime = millis();

  while (true){
    bool dataIsReady = getBit(this->wire, FUEL_GAUGE_ADDRESS, F_STAT_REG, DNR_BIT) == 0;
    if (dataIsReady) {
      return true;
    }

    if (millis() - startTime > timeout) {
      return false;
    }

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
  // TODO to preserve the hiberation config, probably better to only set bit 15 to 0
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, HIB_CFG_REG, 0x0);      // Exit Hibernate Mode
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, SOFT_WAKEUP_REG, 0x90); // Wakes up the fuel gauge from hibernate mode to reduce the response time of the IC to configuration changes  
  writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, SOFT_WAKEUP_REG, 0x0);  // This command must be manually cleared (0x0000) afterward to keep proper fuel gauge timing
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
  return writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, MAXMIN_VOLT_REG, MAXMIN_VOLT_INITIAL_VALUE) == 0;
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
    // In order to support this, probably more configuration is needed
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

uint8_t Battery::internalTemperature(){
  if(!isConnected()){
    return -1;
  }

  setTemperatureMeasurementMode(false);  
  // TODO also see DieTemp Register (034h) for the internal die temperature p. 24 in DS  
  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, TEMP_REG) * TEMPERATURE_MULTIPLIER_C;
}

uint8_t Battery::averageInternalTemperature(){
  if(!isConnected()){
    return -1;
  }

  setTemperatureMeasurementMode(false);
  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, AVG_TA_REG) * TEMPERATURE_MULTIPLIER_C;
}

uint8_t Battery::batteryTemperature(){
  if(!isConnected()){
    return -1;
  }

  setTemperatureMeasurementMode(true);
  // TODO possibly await a couple of readings before getting a meaningful temperature
  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, TEMP_REG) * TEMPERATURE_MULTIPLIER_C;
}

uint8_t Battery::averageBatteryTemperature(){
  if(!isConnected()){
    return -1;
  }

  setTemperatureMeasurementMode(true);
  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, AVG_TA_REG) * TEMPERATURE_MULTIPLIER_C;
}

int16_t Battery::current(){
  if(!isConnected()){
    return -1;
  }
  
  return (int16_t)readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, CURRENT_REG) * CURRENT_MULTIPLIER_MA;
}

int16_t Battery::averageCurrent(){
  if(!isConnected()){
    return -1;
  }

  return (int16_t)readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, AVG_CURRENT_REG) * CURRENT_MULTIPLIER_MA;
}

int16_t Battery::minimumCurrent(){
  if(!isConnected()){
    return -1;
  }

  uint16_t registerValue = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, MAXMIN_CURRENT_REG);
  if(registerValue == MAXMIN_CURRENT_INITIAL_VALUE){
    return 0; // The minimum current is not valid
  }

  int8_t lowerByte = static_cast<int8_t>( registerValue & 0xFF);
  return static_cast<int16_t>(lowerByte * MAXMIN_CURRENT_MULTIPLIER_MA);
}

int16_t Battery::maximumCurrent(){
  if(!isConnected()){
    return -1;
  }

  uint16_t registerValue = readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, MAXMIN_CURRENT_REG);
  if(registerValue == MAXMIN_CURRENT_INITIAL_VALUE){
    return 0; // The minimum current is not valid
  }

  // The maximum current is stored in the upper byte
  int8_t upperByte = static_cast<int8_t>( registerValue >> 8);  
  return static_cast<int16_t>(upperByte * MAXMIN_CURRENT_MULTIPLIER_MA);
}

bool Battery::resetMaximumMinimumCurrent(){
  return writeRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, MAXMIN_CURRENT_REG, MAXMIN_CURRENT_INITIAL_VALUE) == 0;
}

int16_t Battery::power(){
  if(!isConnected()){
    return -1;
  }

  return (int16_t)readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, POWER_REG) * POWER_MULTIPLIER_MW;
}

int16_t Battery::averagePower(){
  if(!isConnected()){
    return -1;
  }

  return (int16_t)readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, AVG_POWER_REG) * POWER_MULTIPLIER_MW;
}

uint8_t Battery::percentage(){
  if(!isConnected()){
    return -1;
  }

  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, REP_SOC_REG) * PERCENTAGE_MULTIPLIER;
}

 uint16_t Battery::remainingCapacity(){
  if(!isConnected()){
    return -1;
  }
  
  if(characteristics.capacity == 0){
    return -1;
  }
  
  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, REP_CAP_REG) * CAPACITY_MULTIPLIER_MAH;
}

uint16_t Battery::fullCapacity(){
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

bool Battery::chargingComplete(){
  // TODO This needs to be tested, probably it's a valua that only temporarily indicates the end-of-charge condition.
  // TODO there is also a FULL_DET_BIT in the STATUS2 register but the datasheet does not explain it
  // return getBit(this->wire, FUEL_GAUGE_ADDRESS, STATUS2_REG, FULL_DET_BIT) == 1;
  return getBit(this->wire, FUEL_GAUGE_ADDRESS, F_STAT_REG, FQ_BIT) == 1;
}

int32_t Battery::timeToEmpty(){
  if(!isConnected()){
    return -1;
  }

  int16_t current = this->averageCurrent();
  if(current >= 0){
    return -1; // The battery is charging, so the time to empty is not valid
  }

  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, TTE_REG) * TIME_MULTIPLIER_S;
}

int32_t Battery::timeToFull(){
  if(!isConnected()){
    return -1;
  }

  int16_t current = this->averageCurrent();
  if(current <= 0){
    return -1; // The battery is discharging, so the time to full is not valid
  }

  return readRegister16Bits(this->wire, FUEL_GAUGE_ADDRESS, TTF_REG) * TIME_MULTIPLIER_S;
}
