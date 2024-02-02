#include "Arduino.h"
#include "Wire.h"
#include "BatteryRegisters.h"
#include "wireUtils.h"


constexpr int fuelGaugeAddress = 0x36;
constexpr int defaultBatteryCapacityInMiliampereHours = 200;
constexpr int defaultEmptyVoltage = 3000;


/**
 * @brief Battery class definition and member function declarations.
*/
class Battery {
    public: 
        /**
         * @brief Constructor for the Battery class. Initializes the battery with default values for capacity and empty voltage. 
         * The default values are 200mAh and 3000mV respectively.
         * @see #Battery(int, int)
         * @see #defaultBatteryCapacityInMiliampereHours
         * @see #defaultEmptyVoltage
        */
        Battery();

        /**
         * @brief Constructor for the Battery class. 
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
         * @return True if a battery has been connected, false otherwise
        */
        boolean isConnected();

        /**
         * @brief Reads the current voltage of the battery.
         * Voltage is usually between 3000mV and 4200mV.
         * @return The current voltage in millivolts (mV).
        */
        int voltage();

    
        /**
         * @brief Reads the average voltage of the battery.
         * @return The average voltage in millivolts (mV). 
        */
        unsigned int averageVoltage();


        /**
         * @brief Reads the current flowing from the battery at the moment.
         * @return The current flowing from the battery at the moment miliamperes (mA).
        */
        int current();

        /**
         * @brief Reads the average current of the battery.
         * @return The average current in millivolts (mV). 
        */
        int averageCurrent();


        /**
         * @brief Reads the current temperature of the battery.
         * @return The current temperature in degrees Celsius.
        */
        int temperature();


        /**
         * @brief Reads the average temperature of the battery.
         * @return The current temperature in degrees Celsius.
        */
        int averageTemperature();
        
        /**
         * @brief Reads the battery's state of charge (SOC). 
         * This value is based on both the voltage and the current of the battery as well as compensation for the battery's age and temperature and discharge rate.
         * @return The state of charge as a percentage.
        */
        int percentage();

        /**
         * @brief Reads the remaining capacity of the battery.
         * @return The remaining capacity in milliampere-hours (mAh).
        */
        int remainingCapacity();

    private:
        int batteryCapacityInMiliampereHours = defaultBatteryCapacityInMiliampereHours;
        int batteryEmptyVoltage = defaultEmptyVoltage;
          #if defined(ARDUINO_PORTENTA_C33)
                TwoWire *  wire = &Wire3;
            #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4)
                TwoWire * wire = &Wire1;
            #elif defined(ARDUINO_NICLA_VISION) 
                TwoWire * wire = &Wire1;
            #endif
};