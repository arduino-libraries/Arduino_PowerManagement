#ifndef Battery_H
#define Battery_H

#include "Arduino.h"
#include "Wire.h"
#include "BatteryRegisters.h"
#include "wireUtils.h"

constexpr int FUEL_GAUGE_ADDRESS = 0x36; // I2C address of the fuel gauge
constexpr int DEFAULT_BATTERY_CAPACITY = 200; // mAh
constexpr int DEFAULT_BATTERY_EMPTY_VOLTAGE = 3000; // mV

/**
 * @brief This class provides a detailed insight into the battery's health and usage.
*/
class Battery {
    public: 
        /**
         * @brief Initializes the battery object with default values for capacity and empty voltage. 
         * The default values are 200mAh and 3000mV respectively.
         * @see #Battery(int, int)
         * @see #DEFAULT_BATTERY_CAPACITY
         * @see #DEFAULT_BATTERY_EMPTY_VOLTAGE
        */
        Battery();

        /**
         * @brief Constructs a new instance of the Battery class with the specified capacity and empty voltage.
         * @param capacityInMilliAmpereHours The capacity of the battery in milliampere-hours (mAh).
         * @param emptyVoltageInMilliVolts The voltage at which the battery is considered empty in millivolts (mV).
        */
        Battery(int capacityInMilliAmpereHours, int emptyVoltageInMilliVolts); 

        /**
         * @brief Initializes the battery communication and configuration.
        */
        bool begin();

        /**
         * @brief Checks if a battery is connected to the system. 
         * @return True if a battery is connected, false otherwise
        */
        boolean isConnected();

        /**
         * @brief Reads the current voltage of the battery.
         * Voltage is usually between 3000mV and 4200mV.
         * @return The current voltage in millivolts (mV).
        */
        int voltage();

        /**
         * @brief Reads the current flowing from the battery at the moment.
         * Negative values indicate that the battery is charging, 
         * positive values indicate that the battery is discharging.
         * When no battery is connected, the value is 0.
         * @return The current flowing from the battery in milliamperes (mA).
        */
        int current();

        /**
         * @brief Reads the current temperature of the battery.
         * @return The current temperature in degrees Celsius.
        */
        int temperature();

        /**
         * @brief Reads the battery's state of charge (SOC). 
         * This value is based on both the voltage and the current of the battery as well as 
         * compensation for the battery's age and temperature and discharge rate.
         * @return The state of charge as a percentage (Range: 0% - 100%).
        */
        int percentage();

        /**
         * @brief Reads the remaining capacity of the battery.
         * In combination with current(), this value can be used to estimate 
         * the remaining time until the battery is empty.
         * @return The remaining capacity in milliampere-hours (mAh).
        */
        int remainingCapacity();

    private:
        /**
         * @brief Reads the average temperature of the battery.
         * @return The average temperature in degrees Celsius.
        */
        int averageTemperature();

        /**
         * @brief Reads the average current of the battery.
         * @return The average current in millivolts (mV). 
        */
        int averageCurrent();

        /**
         * @brief Reads the average voltage of the battery.
         * @return The average voltage in millivolts (mV). 
        */
        unsigned int averageVoltage();

        int batteryCapacityInMiliampereHours = DEFAULT_BATTERY_CAPACITY;
        int batteryEmptyVoltage = DEFAULT_BATTERY_EMPTY_VOLTAGE;

        #if defined(ARDUINO_PORTENTA_C33)
            TwoWire *wire = &Wire3;
        #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4)
            TwoWire *wire = &Wire1;
        #elif defined(ARDUINO_NICLA_VISION)
            TwoWire *wire = &Wire1;
        #else
            #error "The selected board is not supported by the Battery class."
        #endif
};

#endif