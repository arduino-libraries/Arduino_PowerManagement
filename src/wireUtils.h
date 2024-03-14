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
        return 0; // You might want to return an appropriate error value here
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
    wire->write(msb);
    wire->write(lsb);
    return (wire->endTransmission());
}

/**
 * @brief Reads a 16-bit register from a specified address using the given I2C wire object.
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
    wire->endTransmission();
    wire->requestFrom(address, 2);
    uint16_t registerValue = (uint16_t)wire->read();
    registerValue |= (uint16_t)wire->read() << 8;
    wire->endTransmission();
    return registerValue;

}

/**
 * Checks if a specific bit is set in a register value.
 *
 * @param wire The I2C object used for communication.
 * @param address The address of the device.
 * @param reg The register to check.
 * @param offset The bit offset within the register value.
 * @return True if the bit is set, false otherwise.
 */
static inline bool bitIsSetInRegister(TwoWire *wire, uint8_t address, uint8_t reg, uint8_t offset) {
    uint16_t regValue = readRegister16Bits(wire, address, reg);
    return bitRead(regValue, offset) == 1;
}


// TODO: What is this function doing?
/**
 * Replaces specific bits in a register value of a device connected to the I2C bus.
 *
 * @param wire The I2C object representing the I2C bus.
 * @param address The address of the device on the I2C bus.
 * @param reg The register to modify.
 * @param data The new data to write to the register.
 * @param bits The bits to replace in the register.
 * @param offset The offset of the bits to replace.
 */
static inline void replaceRegisterBits(TwoWire *wire, uint8_t address, uint8_t reg, uint16_t data, uint16_t bits, uint8_t offset) {
    uint16_t registerValue = readRegister16Bits(wire, address, reg);

    // Left-shift the bits to the correct position in the register
    uint16_t shiftedBits = bits << offset;

    // Create a bit mask with all bits set to 1 except for the bits to be modified
    uint16_t bitMask = ~(shiftedBits);

    // Preserve the bits in the register that don't need to be modified
    uint16_t preservedBits = registerValue & bitMask;

    // Left-shift the new data to be written to the correct bit positions
    uint16_t shiftedData = data << offset;

    // Combine the preserved bits with the new data to obtain the updated value
    uint16_t updatedValue = preservedBits | shiftedData;

    writeRegister16Bits(wire, address, reg, updatedValue);
}

#endif