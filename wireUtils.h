#ifndef WIREUTILS_H
#define WIREUTILS_H

#include "Arduino.h"
#include "Wire.h"


#define toLowByte(w)              ((uint8_t) ((w) & 0xff))
#define toHighByte(w)             ((uint8_t) ((w) >> 8))
#define toUint16(highB, lowB)     ((uint16_t)((uint8_t)highB << 8) + (uint8_t)lowB)
#define BV(bit)                   (1 <<(bit))
//#define setBit(byte, bit)         (byte |= BV(bit))
#define clearBit(byte, bit)       (byte &= ~BV(bit))
#define toggleBit(byte, bit)      (byte ^= BV(bit))

static inline int extractBits(int value, int startBit, int endBit) {
    if (startBit < 0 || startBit > 31 || endBit < 0 || endBit > 31 || startBit > endBit) {
        // Handle invalid bit range
        return 0; // You might want to return an appropriate error value here
    }

    int mask = (1 << (endBit - startBit + 1)) - 1;
    return (value >> startBit) & mask;
}

static inline uint8_t writeRegister16(TwoWire *wire, uint8_t address, uint8_t reg, uint16_t data)
{
  uint8_t msb, lsb;
  msb = (data & 0xFF00) >> 8;
  lsb = (data & 0x00FF);
  wire -> beginTransmission(address);
  wire -> write(reg);
  wire -> write(msb);
  wire -> write(lsb);
  return (wire -> endTransmission());
}

static inline uint16_t readRegister16(TwoWire *ptr, uint8_t address, uint8_t reg)
{

   uint16_t temp;
    ptr->beginTransmission(address);
    ptr->write(reg);
    ptr->endTransmission();
    ptr->requestFrom(address, 2);
    temp = (uint16_t)ptr->read();
    temp |= (uint16_t)ptr->read() << 8;
    ptr->endTransmission();
    return temp;

}

static inline uint16_t extractAndReverseBits(uint16_t value, int startBit, int endBit) {
    if (startBit < 0 || startBit > 15 || endBit < 0 || endBit > 15 || startBit > endBit) {
        // Handle invalid bit range
        return 0; // You might want to return an appropriate error value here
    }

    uint16_t result = 0;
    for (int i = endBit; i >= startBit; i--) {
        uint16_t bit = (value >> i) & 1;
        result = (result << 1) | bit;
    }

    return result;
}

static inline bool getBitFromOffset(uint16_t value, uint8_t offset) {
        if (offset < 16) {
            uint16_t bitmask = (1 << offset);
            return (value & bitmask) != 0;
        } else {
            return false;
        }
}

static inline bool readBitFromRegister(TwoWire *wire, uint8_t address, uint8_t reg, uint8_t offset) {
    uint16_t regValue = readRegister16(wire, address, reg);
    return getBitFromOffset(regValue, offset);
}


static inline void replaceRegisterBits(TwoWire *wire, uint8_t address, uint8_t reg, uint16_t data, uint16_t bits, uint8_t offset) {
    uint16_t value;
    uint16_t temp = readRegister16(wire, address, reg);

    // Left-shift the bits to the correct position in the register
    uint16_t shiftedBits = bits << offset;

    // Create a bit mask with all bits set to 1 except for the bits to be modified
    uint16_t bitMask = ~(shiftedBits);

    // Preserve the bits in the register that don't need to be modified
    uint16_t preservedBits = temp & bitMask;

    // Left-shift the new data to be written to the correct bit positions
    uint16_t shiftedData = data << offset;

    // Combine the preserved bits with the new data to obtain the updated value
    uint16_t updatedValue = preservedBits | shiftedData;

    writeRegister16(wire, address, reg, updatedValue);
}

#endif