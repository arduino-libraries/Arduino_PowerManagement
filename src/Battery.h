#ifndef Battery_H
#define Battery_H

#include "Arduino.h"
#include "Wire.h"
#include "BatteryConstants.h"
#include "WireUtils.h"

constexpr int FUEL_GAUGE_ADDRESS = 0x36; // I2C address of the fuel gauge
constexpr int DEFAULT_BATTERY_EMPTY_VOLTAGE = 3300; // mV

/**
 * @brief This class provides a detailed insight into the battery's health and usage.
*/
class Battery {
    public: 
        /**
         * @brief Initializes the battery object with default values for capacity (0mAh) and empty voltage (3.3V). 
        */
        Battery();

        /**
         * @brief Constructs a new instance of the Battery class with the specified capacity and empty voltage.
         * @param capacityInMilliAmpereHours The capacity of the battery in milliampere-hours (mAh).
         * @param emptyVoltageInMilliVolts The voltage in millivolts (mV) at which the battery is considered empty.
        */
        Battery(int capacityInMilliAmpereHours, int emptyVoltageInMilliVolts = DEFAULT_BATTERY_EMPTY_VOLTAGE); 

        /**
         * @brief Initializes the battery communication and configuration.
         * @return True if the initialization was successful, false otherwise.
        */
        bool begin();

        /**
         * @brief Checks if a battery is connected to the system. 
         * @return True if a battery is connected, false otherwise
        */
        boolean isConnected();

        /**
         * @brief Reads the current voltage of the battery.
         * Voltage is usually between 3.0V and 4.2V.
         * @return The current voltage in volts (V).
        */
        float voltage();

        /**
         * @brief Reads the current flowing from the battery at the moment.
         * Negative values indicate that the battery is charging, 
         * positive values indicate that the battery is discharging.
         * When no battery is connected, the value is -1.
         * @return The current flowing from the battery in amperes (A).
        */
        float current();

        /**
         * @brief Reads the current temperature of the battery.
         * Note: This only works if the battery is equipped with a thermistor.
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
         * @return The average current in amperes (A).
        */
        float averageCurrent();

        /**
         * @brief Reads the average voltage of the battery.
         * @return The average voltage in volts (V). 
        */
        float averageVoltage();

        /** 
         * @brief Refreshes the battery gauge model. This is required when
         * changing the battery's characteristics and is used by the EZ algorithm (battery characterization).
         * EZ stands for "Easy" and highlights how the algorithm makes it easy to
         * use the battery gauge without needing to provide precise battery characteristics.
         * 
         * @return true if the battery gauge model was successfully refreshed, false otherwise.
         */
        bool refreshBatteryGaugeModel();

        int batteryCapacityInMiliampereHours;
        int batteryEmptyVoltage;

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