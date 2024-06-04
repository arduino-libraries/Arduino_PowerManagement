#include "WireUtils.h"
#include "BatteryConstants.h"

enum class FuelGaugeOperationMode {
    hibernate,
    shutdown,
    active
};

constexpr uint8_t DEFAULT_I2C_ADDRESS = 0x36;

class MAX1726Driver {
private:
    TwoWire *wire;
    uint8_t i2cAddress;
public:
    bool setOperationMode(FuelGaugeOperationMode mode);
    MAX1726Driver(TwoWire *wire, uint8_t i2cAddress);
    ~MAX1726Driver();
};

MAX1726Driver::MAX1726Driver(TwoWire *wire, uint8_t i2cAddress = DEFAULT_I2C_ADDRESS) {
    this->wire = wire;
    this->i2cAddress = i2cAddress;
}

MAX1726Driver::~MAX1726Driver(){}

bool MAX1726Driver::setOperationMode(FuelGaugeOperationMode mode) {
    if(mode == FuelGaugeOperationMode::active){
        // See section "Soft-Wakeup" in user manual https://www.analog.com/media/en/technical-documentation/user-guides/max1726x-modelgauge-m5-ez-user-guide.pdf
        writeRegister16Bits(this->wire, i2cAddress, HIB_CFG_REG, 0x0);      // Exit Hibernate Mode
        writeRegister16Bits(this->wire, i2cAddress, SOFT_WAKEUP_REG, 0x90); // Wakes up the fuel gauge from hibernate mode to reduce the response time of the IC to configuration changes  
        writeRegister16Bits(this->wire, i2cAddress, SOFT_WAKEUP_REG, 0x0);  // This command must be manually cleared (0x0000) afterward to keep proper fuel gauge timing
    } else if(mode == FuelGaugeOperationMode::hibernate){
        // Enters hibernate mode somewhere between 2.812s and 5.625s if the threshold conditions are met
        replaceRegisterBit(this->wire, I2C_ADDRESS, HIB_CFG_REG, 1, EN_HIBERNATION_BIT); // Enter Hibernate Mode
    } else if(mode == FuelGaugeOperationMode::shutdown){
        // Enter active mode
        // TODO use function instead        
        replaceRegisterBit(this->wire, I2C_ADDRESS, HIB_CFG_REG, 0, EN_HIBERNATION_BIT); // Exit Hibernate Mode
        // TODO check if we can enter shutdown quicker by setting CTR manually in ShdnTimer
        // The default shutdown timeout is 45s
        replaceRegisterBit(this->wire, I2C_ADDRESS, CONFIG_REG, 1, SHDN_BIT); // Command shutdown mode
    }
    
    return false;
}