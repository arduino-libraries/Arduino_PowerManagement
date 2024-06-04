#ifndef Battery_H
#define Battery_H

#include "Arduino.h"
#include "Wire.h"

constexpr int FUEL_GAUGE_ADDRESS = 0x36; // I2C address of the fuel gauge
constexpr float DEFAULT_BATTERY_EMPTY_VOLTAGE = 3.3f; // V
constexpr float DEFAULT_CHARGE_VOLTAGE = 4.2f; // V
constexpr int DEFAULT_END_OF_CHARGE_CURRENT = 50; // mA
constexpr float DEFAULT_RECOVERY_VOLTAGE = 3.88f; // V

enum class NTCResistor {
    Resistor10K,
    Resistor100K
};

/**
 * @brief This struct contains the characteristics of the battery.
*/
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

    /// @brief Sets the voltage level for clearing empty detection. Once the cell voltage rises above this point, empty voltage detection is re-enabled.
    float recoveryVoltage = DEFAULT_RECOVERY_VOLTAGE;
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

        /**
         * @brief Initializes the battery object with the given battery characteristics.
         * @param batteryCharacteristics The characteristics of the battery.
        */
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

        /**
         * @brief Returns the minimum voltage value measured since the last device reset.
         * At power-up the minimum voltage value is set to FFh (the maximum).
         * @return The minimum voltage value in volts (V).
         */
        float minimumVoltage();
        
        /**
         * @brief Returns the maximum voltage value measured since the last device reset.
         * At power-up the maximum voltage value is set to 00h (the minimum).
         * @return The maximum voltage value in volts (V).
         */
        float maximumVoltage();

        /**
         * @brief Resets the minimum and maximum voltage values.
         * @return True if the minimum and maximum voltage values were successfully reset, false otherwise.
         */
        bool resetMaximumMinimumVoltage();

        /**
         * @brief Reads the current flowing from the battery at the moment.
         * Negative values indicate that the battery is charging, 
         * positive values indicate that the battery is discharging.
         * When no battery is connected, the value is -1.
         * @return The current flowing from the battery in milli amperes (mA).
        */
        int16_t current();

        /**
         * @brief Reads an average of current readings of the battery.
         * @return The average current in milli amperes (mA).
        */
        int16_t averageCurrent();

        /**
         * @brief Reads the minimum current values measured since the last device reset.
         * Note: The resolution of the minimum current value is 160mA so the value
         * is rounded to the nearest 160mA.
         * @return The minimum current values in milli amperes (mA).
         */
        int16_t minimumCurrent();

        /**
         * @brief Reads the maximum current values measured since the last device reset.
         * Note: The resolution of the minimum current value is 160mA so the value
         * is rounded to the nearest 160mA.
         * @return The maximum current values in milli amperes (mA).
         */
        int16_t maximumCurrent();

        /**
         * @brief Resets the minimum and maximum current values.
         * @return True if the minimum and maximum current values were successfully reset, false otherwise.
        */
        bool resetMaximumMinimumCurrent();

        /**
         * @brief Reads the current power of the battery in milliwatts (mW).
         * This value is calculated based on the current and voltage of the battery.
         * @return The current power in milliwatts (mW).
        */
        int16_t power();

        /**
         * @brief Reads an average of power readings of the battery in milliwatts (mW).
         * This value is calculated based on the current and voltage of the battery.
         * @return The average power in milliwatts (mW).
        */
        int16_t averagePower();

        /**
         * @brief Reads the current temperature of the internal die of the battery gauge chip. 
         * @return The current temperature in degrees Celsius.
        */
        uint8_t internalTemperature();

        /**
         * @brief Reads an average of internal temperature readings of the battery.
         * Note: If the battery temperature was read before,
         * this function will change the configuration to read the internal temperature.
         * You will have to await a couple of temperature readings before 
         * getting a meaningful average temperature.
         * @return The average temperature in degrees Celsius.
        */
        uint8_t averageInternalTemperature();

        /**
         * @brief Reads the battery's state of charge (SOC). 
         * This value is based on both the voltage and the current of the battery as well as 
         * compensation for the battery's age and temperature and discharge rate.
         * @return The state of charge as a percentage (Range: 0% - 100%).
        */
        uint8_t percentage();

        /**
         * @brief Reads the remaining capacity of the battery.
         * In combination with current(), this value can be used to estimate 
         * the remaining time until the battery is empty.
         * @return The remaining capacity in milliampere-hours (mAh).
        */
        uint16_t remainingCapacity();

        /**
         * Returns the full capacity of the battery.
         * For this to work, the capacity of the battery must be set 
         * when initializing the battery object.
         * @return The full capacity of the battery.
         */
        uint16_t fullCapacity();

        /**
         * @brief Checks if the battery is empty.
         * Returns false once the cell voltage rises above the recovery threshold.
         * @return true if the battery is empty, false otherwise.
         */
        bool isEmpty();

        /**
         * Calculates the estimated time until the battery is empty.
         * @return The estimated time until the battery is empty, in seconds.
         * If the battery is charging, the function returns -1.
         */
        int32_t timeToEmpty();

        /**
         * Calculates the estimated time until the battery is fully charged.
         * The value is determined by learning from the experience of prior charge cycles.
         * @return The estimated time until the battery is fully charged in seconds.
         * If the battery is discharging, the function returns -1.
         */
        int32_t timeToFull();

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

        /**
         * @brief Reads the battery's temperature.
         * Note: This only works if the battery is equipped with a thermistor.
         * @return The battery temperature in degrees Celsius.
         */
        uint8_t batteryTemperature();

        /**
         * @brief Reads the average battery temperature.
         * Note: This only works if the battery is equipped with a thermistor.
         * @return The average battery temperature in degrees Celsius.
         */
        uint8_t averageBatteryTemperature();

        /**
         * @brief Releases the device from hibernation mode.
         * This is used during the initialization process to wake up the device.
         * 
         * This function is used to release the device from hibernation mode and resume normal operation.
         */
        void releaseFromHibernation();

        /**
         * Waits for the data of the EZ algorithm's output registers to be ready.
         * @return True when the data has become ready, false when the timeout is reached.
         */
        bool awaitDataReady(uint16_t timeout = 1000);

        /**
         * Configures the characteristics of the battery as part of the initialization process.
         */
        void configureBatteryCharacteristics();

        /**
         * Sets the temperature measurement mode for the battery.
         * 
         * @param externalTemperature Flag indicating whether to measeure the internal die temperature or the battery temperature.
         */
        void setTemperatureMeasurementMode(bool externalTemperature);

        BatteryCharacteristics characteristics;

        #if defined(ARDUINO_PORTENTA_C33)
            TwoWire *wire = &Wire3;
        #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_GENERIC_STM32H747_M4)
            TwoWire *wire = &Wire1;
        #elif defined(ARDUINO_NICLA_VISION)
            TwoWire *wire = &Wire1;
        #else
            #error "The selected board is not supported by the Battery class."
        #endif
};

#endif