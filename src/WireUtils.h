#ifndef WIREUTILS_H
#define WIREUTILS_H

#include "Arduino.h"
#include "Wire.h"

/**
 * @brief Extracts a range of bits from an integer value.
 *
 * This function extracts a range of bits from the given integer value, starting from the startBit
 * and ending at the endBit (inclusive).
 *
 * @param value The integer value from which to extract the bits.
 * @param startBit The starting bit position.
 * @param endBit The ending bit position.
 * @return The extracted bits as an integer value.
 */
static inline int extractBits(int value, int startBit, int endBit) {
    if (startBit < 0 || startBit > 31 || endBit < 0 || endBit > 31 || startBit > endBit) {
        // Handle invalid bit range
        return -1;
    }    

    int mask = (1 << (endBit - startBit + 1)) - 1;
    return (value >> startBit) & mask;
}

/**
 * Writes a 16-bit data value to a register using the specified I2C wire object.
 *
 * @param wire The I2C wire object to use for communication.
 * @param address The I2C address of the device.
 * @param reg The register address to write to.
 * @param data The 16-bit data value to write.
 * @return The status of the write operation:
 * 0: success.
 * 1: data too long to fit in transmit buffer.
 * 2: received NACK on transmit of address.
 * 3: received NACK on transmit of data.
 * 4: other error.
 * 5: timeout
 */
static inline uint8_t writeRegister16Bits(TwoWire *wire, uint8_t address, uint8_t reg, uint16_t data)
{
    uint8_t msb, lsb;
    msb = (data & 0xFF00) >> 8;
    lsb = (data & 0x00FF);
    wire->beginTransmission(address);
    wire->write(reg);
    /**
     * See section "Data Order" in https://www.analog.com/media/en/technical-documentation/user-guides/max1726x-modelgauge-m5-ez-user-guide.pdf
     * With I2C communication, a byte of data consists of 8 bits ordered most significant bit (MSb) first.
     * The least significant bit (LSb) of each byte is followed by the Acknowledge bit. IC registers
     * comprising multibyte values are ordered least significant byte (LSB) first.
    */
    wire->write(lsb);
    wire->write(msb);
    return (wire->endTransmission());
}

/**
 * @brief Reads a 16-bit register from a specified address using the given I2C wire object.
 * The data order is LSB(yte) first.
 * 
 * @param wire The I2C wire object to use for communication.
 * @param address The address of the device to read from.
 * @param reg The register to read.
 * @return The value read from the register as a 16-bit integer.
 */
static inline uint16_t readRegister16Bits(TwoWire *wire, uint8_t address, uint8_t reg)
{
    wire->beginTransmission(address);
    wire->write(reg);
    wire->endTransmission(false);
    wire->requestFrom(address, 2, true);
    uint16_t registerValue = (uint16_t)wire->read(); // Read LSB
    registerValue |= (uint16_t)wire->read() << 8; // Read MSB
    return registerValue;
}

/** 
 * Gets the value of a specific bit in a register.
 * @param wire The I2C object used for communication.
 * @param address The address of the device.
 * @param reg The register to check.
 * @param index The bit index within the register value.
 * @return The value of the bit at the specified index. 
*/
static inline uint8_t getBit(TwoWire *wire, uint8_t address, uint8_t reg, uint8_t index) {
    uint16_t regValue = readRegister16Bits(wire, address, reg);
    return (regValue >> index) & 0x01;
}

/**
 * Replaces specific bits in a register value of a device connected to the I2C bus.
 *
 * @param wire The I2C object representing the I2C bus.
 * @param address The address of the device on the I2C bus.
 * @param reg The register to modify.
 * @param indexFrom The index of the first bit to replace starting from LSB (0)
 * @param indexTo The index of the last bit (included) to replace starting from LSB (0)
 * @param data The new data (bits) to write to the register.
 */
static inline void replaceRegisterBits(TwoWire *wire, uint8_t address, uint8_t reg, uint16_t indexFrom, uint8_t indexTo, uint16_t data) {
    uint16_t registerValue = readRegister16Bits(wire, address, reg);

    // Create a mask to clear the bits to be replaced
    uint16_t mask = 0;
    for (int i = indexFrom; i <= indexTo; i++) {
        mask |= (1 << i);
    }
    registerValue &= ~mask; // Clear the bits to be replaced
    registerValue |= (data << indexFrom); // Set the new bits
    writeRegister16Bits(wire, address, reg, registerValue);
}


/**
 * @brief Replaces a specific bit in a register of a given I2C device.
 *
 * This function replaces a specific bit in a register of a given I2C device.
 *
 * @param wire The TwoWire object representing the I2C bus.
 * @param address The address of the I2C device.
 * @param reg The register to modify.
 * @param index The index of the bit to replace.
 * @param data The new data (1 bit) to write to the register.
 */
static inline void replaceRegisterBit(TwoWire *wire, uint8_t address, uint8_t reg, uint16_t index, uint16_t data) {
    replaceRegisterBits(wire, address, reg, index, index, data);
}

#endif