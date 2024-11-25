#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>
#include <Arduino_PF1550.h>
#include "WireUtils.h"

#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_GENERIC_STM32H747_M4)
#define ARDUINO_PORTENTA_H7
#endif

#if defined(ARDUINO_PORTENTA_C33) 
    #include "Arduino_LowPowerPortentaC33.h"
    #include "RTC.h"
#elif defined(ARDUINO_PORTENTA_H7)
    // When used standalone the LowPowerPortentaH7 library will turn off the Ethernet interface to avoid issues with the line termination resistors, 
    // but in this library we can turn of the Ethernet interface using the PMIC, so we set the NO_ETHERNET_TURN_OFF flag to avoid turning off the Ethernet interface from both sides. 
    #define NO_ETHERNET_TURN_OFF
    #include "Arduino_LowPowerPortentaH7.h"
#elif defined(ARDUINO_NICLA_VISION)
    #include "Arduino_LowPowerNiclaVision.h"
#endif 

#define CONTEXT_LDO2 2 // LDO regulator: 1.8 V to 3.3 V, 400 mA
#define CONTEXT_SW1 3 // Buck converter: 1.0 A; 0.6 V to 1.3875 V 
#define CONTEXT_SW2 4 // Buck converter: 1.0 A; 0.6 V to 1.3875 V

enum class StandbyType : uint8_t {
    none = 0,
    untilPinActivity = 1,
    untilTimeElapsed = 2,
    untilEither = 3
};

inline constexpr StandbyType operator|(StandbyType x, StandbyType y){
    return static_cast<StandbyType>(static_cast<int>(x) | static_cast<int>(y));
}

inline constexpr StandbyType operator|=(StandbyType& x, StandbyType y){
    return x = x | y;
}

/**
 * @brief Represents a board with power management capabilities.
 * 
 * The Board class provides methods to check the power source, enable/disable power rails, 
 * set voltage levels, enable/disable wakeup from pins or RTC, 
 * put the device into sleep mode for a specified duration, and control peripherals' power.
 * 
 * Supported boards: Arduino Portenta H7, Arduino Portenta C33, Arduino Nicla Vision.
 */
class Board {
    public:
        /**
         * @brief Construct a new Board object.
        */
        Board();

        /**
         * @brief Destroy the Board object.
        */
        ~Board();

        /**
         * @brief Initializes the board by initiating the PMIC.
         * 
         * @return true if the board initialization is successful, false otherwise.
         */
        bool begin();

        /**
         * @brief Check if the board is powered through USB.
         * @return True if powered through USB, false otherwise.
        */
        bool isUSBPowered();

        /**
         * @brief Check if the board is powered by the battery.
         * @return True if powered by the battery, false otherwise.
        */
        bool isBatteryPowered();

        /**
         * Enables/disables the voltage on the external power rail.
         * This lane powers the pin labeled 3V3 on the board.
         * @param on True to enable this power rail, false to disable it.
         */
        void setExternalPowerEnabled(bool on);


        /**
         * Set the voltage for the external power rail.
         * This lane powers the pin labeled 3V3 on the board.
         * @param voltage float value of the voltage value to set. 
         * Value has to be one of the following (1.10, 1.20, 1.35, 1.50, 1.80, 2.50, 3.00, 3.30)
         * @return True the voltage was set successfully, false otherwise.
        */
        bool setExternalVoltage(float voltage); 
    
  
        /**
         * @brief Enables/disables the camera's power rail on boards with a built-in camera.
         * @param enabled True to turn on the camera, false to turn it off.
        */
        void setCameraPowerEnabled(bool enabled); 


        #if defined(ARDUINO_PORTENTA_H7)

        /**
         * Enables wakeup from pin GPIO0 on Portenta H7.
         * The pin is only accessible via high-density connectors.
         */
        void enableWakeupFromPin();
        #endif

        #if defined(ARDUINO_PORTENTA_H7) || defined(ARDUINO_NICLA_VISION)
        /**
         * Enables sleep mode when the board is idle.
         */
        void enableSleepWhenIdle();
        #endif 
        
        #if defined(ARDUINO_PORTENTA_C33)
        /**
         * Enables wake-up of the device from a specified pin (A0, A1, A2, A3, A4, A5, D4, D7 ) on Arduino Portenta C33.
         * @param pin The pin number used for waking up the device.
         * @param direction The direction of the interrupt that will wake up the device. (RISING, FALLING)
         */
        void enableWakeupFromPin(uint8_t pin, PinStatus direction);
        #endif

        
        #if defined(ARDUINO_PORTENTA_C33)
        /**
         * @brief Enables wake-up of the device from the RTC.
         * This function allows to use a custom RTC instance to put the device in sleep mode.
         * @param hours The number of hours to sleep.
         * @param minutes The number of minutes to sleep.
         * @param seconds The number of seconds to sleep.
         * @param callbackFunction The function to call when the device wakes up.
         * If no callback function is provided, the device will wake up without calling any function.
         * @param rtc The RTC instance to use for the sleep function.
         * If no RTC instance is provided, the default RTC instance is used.
         * @return True if successful, false otherwise.
        */
        bool enableWakeupFromRTC(uint32_t hours, uint32_t minutes, uint32_t seconds, void (* const callbackFunction)(), RTClock * rtc = &RTC);

        /**
         * @brief Enables wake-up of the device from the RTC.
         * @param hours The number of hours to sleep.
         * @param minutes The number of minutes to sleep.
         * @param seconds The number of seconds to sleep.
         * @param rtc The RTC instance to use for the sleep function. Default is the shared RTC instance.
         * @return True if successful, false otherwise.
        */
        bool enableWakeupFromRTC(uint32_t hours, uint32_t minutes, uint32_t seconds, RTClock * rtc = &RTC);
        #endif

        #if defined(ARDUINO_PORTENTA_H7) || defined(ARDUINO_NICLA_VISION)
        /**
         * Enables wake-up of the device from the RTC.
         * @param hours The number of hours to sleep.
         * @param minutes The number of minutes to sleep.
         * @param seconds The number of seconds to sleep.
         * @return True if successful, false otherwise.
        */
        bool enableWakeupFromRTC(uint32_t hours, uint32_t minutes, uint32_t seconds);
        #endif


        #if defined(ARDUINO_PORTENTA_C33)
        /**
         * Put the device into sleep mode until a wakeup event occurs
         * This sleep mode is ideal for applications requiring periodic wake-ups or 
         * brief intervals of inactivity and reduces consumption to a range between 
         * 6mA and 18mA depending on the state of the peripherals. 
         * This sleep mode resumes the operation from the last operation without resetting the board.
         * A wakeup event can be an interrupt on a pin or the RTC, 
         * depending on what you set with enableWakeupFromPin() and enableWakeupFromRTC().
         */
        void sleepUntilWakeupEvent();
        #endif

    
        /**
         * Put the device into standby mode until a wakeup event occurs.
         * For scenarios demanding drastic power conservation, the standby Mode significantly reduces 
         * the board's power usage to micro amperes range depending on the state of the peripherals.
         * This mode restarts the board on wake-up, effectively running the setup() function again.
         * A wakeup event can be an interrupt on a pin or the RTC, depending on what 
         * you set with enableWakeupFromPin() and enableWakeupFromRTC().
         */
        void standByUntilWakeupEvent();

        /**
         * @brief Toggle the peripherals' power on Portenta C33 (ADC, RGB LED, Secure Element, Wifi and Bluetooth).
         * @param on True to turn on the power, false to turn it off.
        */
        void setAllPeripheralsPower(bool on);

        /**
         * @brief Toggles the communication peripherials' power on Portenta C33 (Wifi, Bluetooth and Secure Element)
         * @param on True to turn on the power, false to turn it off.
        */
        void setCommunicationPeripheralsPower(bool on);
        
        /**
         * @brief Toggles the power of the analog digital converter on Portenta C33.
         * This is not available on the Portenta H7.
         * @param on True to turn on the power, false to turn it off.
        */
        void setAnalogDigitalConverterPower(bool on);

        /**
         * @brief Set the reference voltage. This value is used by the ADC to convert analog values to digital values.
         * This can be particularly useful to increase the accuracy of the ADC when working with low voltages
         * @param voltage Reference voltage value in volts. It can be anything between 1.80V and 3.30V in steps of 0.10V. 
         * Any value outside this range or with different steps will not be accepted by the library.
         * @return True if the voltage was set successfully, false otherwise.
        */
        bool setReferenceVoltage(float voltage);

        /**
         * @brief Shuts down the fuel gauge to reduce power consumption.
         * The IC returns to active mode on any edge of any communication line.
         *  If the IC is power-cycled or the software RESET command is sent the IC 
         * returns to active mode of operation.
        */
        void shutDownFuelGauge();

    private:
        /**
        * Convert a numeric voltage value to the corresponding enum value for the PMIC library.
        */
        static uint8_t getRailVoltageEnum(float voltage, int context);

        #if defined(ARDUINO_PORTENTA_C33)
            LowPower * lowPower;
        #endif         
        
        StandbyType standbyType = StandbyType::none;
        uint32_t wakeupDelayHours;
        uint32_t wakeupDelayMinutes;
        uint32_t wakeupDelaySeconds;
};

#endif