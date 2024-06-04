#include "WireUtils.h"
#include "BatteryConstants.h"

enum class FuelGaugeOperationMode {
    hibernate,
    shutdown,
    active
};

constexpr uint8_t DEFAULT_I2C_ADDRESS = 0x36;

/**
 * @brief Driver class for the MAX1726 Fuel Gauge IC.
 */
class MAX1726Driver {
private:
    TwoWire *wire;
    uint8_t i2cAddress;
    /**
     * Enables or disables the hibernate mode.
     *
     * @param enabled - true to enable hibernate mode, false to disable it.
     */
    void setHibernateModeEnabled(bool enabled);
public:
    /**
     * Checks if the charging process is complete.
     *
     * @return true if the charging process is complete, false otherwise.
     */
    bool chargingComplete();
    /**
     * Sets the operation mode of the Fuel Gauge.
     *
     * @param mode The operation mode to set. Possible values are: hibernate, shutdown, active.
     * @return True if the operation mode was set successfully, false otherwise.
     */
    bool setOperationMode(FuelGaugeOperationMode mode);

    /**
     * @brief Constructs a new MAX1726Driver object.
     *
     * @param wire Pointer to the TwoWire object for I2C communication.
     * @param i2cAddress The I2C address of the MAX1726 device. The default value is 0x36.
     */
    MAX1726Driver(TwoWire *wire, uint8_t i2cAddress);
    ~MAX1726Driver();
};

MAX1726Driver::MAX1726Driver(TwoWire *wire, uint8_t i2cAddress = DEFAULT_I2C_ADDRESS) {
    this->wire = wire;
    this->i2cAddress = i2cAddress;
}

MAX1726Driver::~MAX1726Driver(){}

void MAX1726Driver::setHibernateModeEnabled(bool enabled){
    if(enabled){
        // Enters hibernate mode somewhere between 2.812s and 5.625s if the threshold conditions are met
        replaceRegisterBit(this->wire, i2cAddress, HIB_CFG_REG, EN_HIBERNATION_BIT, 1); // Enter Hibernate Mode
    } else {
        replaceRegisterBit(this->wire, i2cAddress, HIB_CFG_REG, EN_HIBERNATION_BIT, 0); // Exit Hibernate Mode
    }
}

bool MAX1726Driver::setOperationMode(FuelGaugeOperationMode mode) {
    if(mode == FuelGaugeOperationMode::active){
        // See section "Soft-Wakeup" in user manual https://www.analog.com/media/en/technical-documentation/user-guides/max1726x-modelgauge-m5-ez-user-guide.pdf
        replaceRegisterBit(this->wire, i2cAddress, HIB_CFG_REG, EN_HIBERNATION_BIT, 0); // Exit Hibernate Mode
        writeRegister16Bits(this->wire, i2cAddress, SOFT_WAKEUP_REG, 0x90); // Wakes up the fuel gauge from hibernate mode to reduce the response time of the IC to configuration changes  
        writeRegister16Bits(this->wire, i2cAddress, SOFT_WAKEUP_REG, 0x0);  // This command must be manually cleared (0x0000) afterward to keep proper fuel gauge timing
    } else if(mode == FuelGaugeOperationMode::hibernate){
        this->setHibernateModeEnabled(true);
    } else if(mode == FuelGaugeOperationMode::shutdown){        
        this->setHibernateModeEnabled(false); // Enter active mode
        // The default (minimum) shutdown timeout is 45s
        replaceRegisterBit(this->wire, i2cAddress, CONFIG_REG, SHDN_BIT, 1); // Command shutdown mode
    }
    
    return false;
}

/**
 * @brief Checks if the battery charging is complete.
 * 
 * @return true if the charging is complete, false otherwise.
 */
bool MAX1726Driver::chargingComplete(){
  // TODO This needs to be tested, probably it's a value that only temporarily indicates the end-of-charge condition.
  // There is also a FULL_DET_BIT in the STATUS2 register but the datasheet does not explain it:
  // return getBit(this->wire, i2cAddress, STATUS2_REG, FULL_DET_BIT) == 1;
  return getBit(this->wire, i2cAddress, F_STAT_REG, FQ_BIT) == 1;
}