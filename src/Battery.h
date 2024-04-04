#ifndef Battery_H
#define Battery_H

#include "Arduino.h"
#include "Wire.h"
#include "BatteryConstants.h"
#include "WireUtils.h"

constexpr int FUEL_GAUGE_ADDRESS = 0x36; // I2C address of the fuel gauge
constexpr float DEFAULT_BATTERY_EMPTY_VOLTAGE = 3.3f; // V
constexpr float DEFAULT_CHARGE_VOLTAGE = 4.2f; // V
constexpr int DEFAULT_END_OF_CHARGE_CURRENT = 50; // mA

enum class NTCResistor {
    Resistor10K,
    Resistor100K
};

struct BatteryCharacteristics {
    /// @brief The battery's capacity in milliampere-hours (mAh).
    int capacity = 0;
    
    /// @brief The voltage in volts (V) at which the battery is considered empty.
    /// If you don't know this value you can use the minimumVoltage() function to find out
    /// while you let the battery completely discharge.
    float emptyVoltage = DEFAULT_BATTERY_EMPTY_VOLTAGE;

    /// @brief The voltage in volts (V) at which the battery is being charged.
    float chargeVoltage = DEFAULT_CHARGE_VOLTAGE;

    /// @brief The current in milli amperes (mA) that is used to keep the battery charged at the end of the charging process.
    int endOfChargeCurrent = DEFAULT_END_OF_CHARGE_CURRENT;

    /// @brief The NTC resistor value used in the battery pack (10K or 100K Ohm).
    NTCResistor ntcResistor = NTCResistor::Resistor10K;

    float recoveryVoltage = 3.88f;
};

/**
 * @brief This class provides a detailed insight into the battery's health and usage.
*/
class Battery {
    public: 
        /**
         * @brief Initializes the battery object with default values for capacity (0mAh) and empty voltage (3.3V). 
        */
        Battery();

        Battery(BatteryCharacteristics batteryCharacteristics);

        /**
         * @brief Initializes the battery communication and configuration.
         * @param enforceReload If set to true, the battery gauge config will be reloaded.
         * @return True if the initialization was successful, false otherwise.
        */
        bool begin(bool enforceReload = false);

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
         * @brief Reads an average of voltage readings of the battery.
         * @return The average voltage in volts (V). 
        */
        float averageVoltage();

        float minimumVoltage();
        float maximumVoltage();

        bool resetMinimumMaximumVoltage();

        /**
         * @brief Reads the current flowing from the battery at the moment.
         * Negative values indicate that the battery is charging, 
         * positive values indicate that the battery is discharging.
         * When no battery is connected, the value is -1.
         * @return The current flowing from the battery in milli amperes (mA).
        */
        int current();

        /**
         * @brief Reads an average of current readings of the battery.
         * @return The average current in milli amperes (mA).
        */
        int averageCurrent();

        /**
         * @brief Reads the current temperature of the battery.
         * @return The current temperature in degrees Celsius.
        */
        int internalTemperature();

        /**
         * @brief Reads an average of temperature readings of the battery.
         * Note: If the battery temperature was read before,
         * this function will change the configuration to read the internal temperature.
         * You will have to await a couple of temperature readings before 
         * getting a meaningful average temperature.
         * @return The average temperature in degrees Celsius.
        */
        int averageInternalTemperature();

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

        /**
         * Returns the full capacity of the battery.
         * For this to work, the capacity of the battery must be set 
         * when initializing the battery object.
         * @return The full capacity of the battery.
         */
        int fullCapacity();

        /**
         * @brief Checks if the battery is empty.
         * // TODO: Check when this retruns true in the datasheet
         * @return true if the battery is empty, false otherwise.
         */
        bool isEmpty();

    private:
        /** 
         * @brief Refreshes the battery gauge model. This is required when
         * changing the battery's characteristics and is used by the EZ algorithm (battery characterization).
         * EZ stands for "Easy" and highlights how the algorithm makes it easy to
         * use the battery gauge without needing to provide precise battery characteristics.
         * 
         * @return true if the battery gauge model was successfully refreshed, false otherwise.
         */
        bool refreshBatteryGaugeModel();

        // TODO: Implement this function
        // TODO: DOcuemnt this function
        //  * Note: This only works if the battery is equipped with a thermistor.
        int batteryTemperature();

        // TODO: DOcuemnt this function
        int averageBatteryTemperature();

        void releaseFromHibernation();

        void awaitDataReady();

        void configureBatteryCharacteristics();

        void setTemperatureMeasurementMode(bool externalTemperature);

        BatteryCharacteristics characteristics;

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