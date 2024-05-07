#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>
#include <Arduino_PF1550.h>
#include "WireUtils.h"


#if defined(ARDUINO_PORTENTA_C33) 
    #include "Arduino_Portenta_C33_LowPower.h"
    #include "RTC.h"
#elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
    #include "Arduino_LowPowerPortentaH7.h"
#endif 

#define CONTEXT_LDO2 2
#define CONTEXT_SW1 3 
#define CONTEXT_SW2 4 

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

constexpr int EMPTY_REGISTER = 0xFF;

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


        #if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4)

        /**
         * Enables wakeup from pin GPIO0 on Portenta H7.
         * The pin is only accessible via high-density connectors.
         */
        void enableWakeupFromPin();


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

        
        /**
         * Enables wake-up of the device from the RTC.
         */
        void enableWakeupFromRTC();

        #if defined(ARDUINO_PORTENTA_C33)
        // TODO Do I needs to call enableWakeupFromRTC() before calling this function?
        /**
         * @brief Put the device in sleep mode for a specified amount of time. Restarts after waking up.
         * This function allows to use a custom RTC instance to put the device in sleep mode.
         * @param hours The number of hours to sleep.
         * @param minutes The number of minutes to sleep.
         * @param seconds The number of seconds to sleep.
         * @param callbackFunction The function to call when the device wakes up.
         * @param rtc The RTC instance to use for the sleep function.
         * @return True if successful, false otherwise.
        */
        bool sleepFor(int hours, int minutes, int seconds, void (* const callbackFunction)(), RTClock * rtc);

        /**
         * @brief Put the device in sleep mode for a specified amount of time.
         * This function uses the default RTC instance to put the device in sleep mode.
         * @param hours The number of hours to sleep.
         * @param minutes The number of minutes to sleep.
         * @param seconds The number of seconds to sleep.
         * @param callbackFunction The function to call when the device wakes up.
         * @return True if successful, false otherwise.
        */
        bool sleepFor(int hours, int minutes, int seconds, void (* const callbackFunction)());
        #endif

        /** 
         * @brief Put the device in sleep mode for a specified amount of time. It restarts after waking up.
         * This function uses the default RTC instance to put the device in sleep mode and 
         * does not call a function when the device wakes up.
         * @param hours The number of hours to sleep.
         * @param minutes The number of minutes to sleep.
         * @param seconds The number of seconds to sleep.
         * @return True if successful, false otherwise.
        */
        bool sleepFor(int hours, int minutes, int seconds);

        #if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4)        
        
        /**
         * Sleeps the board for a specified delay.
         * 
         * @param delay The delay as an RTCWakeupDelay object.
         * @return True if the board successfully sleeps, false otherwise.
         */
        bool sleepFor(RTCWakeupDelay delay);
        #endif
   

        #if defined(ARDUINO_PORTENTA_C33)
        // TODO How to use this with the RTC? enableWakeupFromRTC(), then sleepFor, then this?
        /**
         * Put the device into sleep mode until a wakeup event occurs
         * This sleep mode is ideal for applications requiring periodic wake-ups or 
         * brief intervals of inactivity and reduces consumption to a range between 
         * 6mA and 18mA depending on the state of the peripherals. 
         * This sleep mode resumes the operation from the last operation.
         * A wakeup event can be an interrupt on a pin or the RTC, 
         * depending on what you set with enableWakeupFromPin() and enableWakeupFromRTC().
         */
        void sleepUntilWakeupEvent();
        #endif

        // TODO Same as above
        /**
         * Put the device into deep sleep mode until a wakeup event occurs.
         * For scenarios demanding drastic power conservation, the Deep Sleep Mode significantly reduces 
         * the board's power usage to range between 90uA and 11mA depending on the state of the peripherals. 
         * This mode restarts the board on wake-up, effectively running the setup() function again.
         * A wakeup event can be an interrupt on a pin or the RTC, depending on what 
         * you set with enableWakeupFromPin() and enableWakeupFromRTC().
         */
        void deepSleepUntilWakeupEvent();

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
        
        #if defined(ARDUINO_PORTENTA_C33)
        /**
         * @brief Toggles the power of the analog digital converter on Portenta C33.
         * @param on True to turn on the power, false to turn it off.
        */
        void setAnalogDigitalConverterPower(bool on);

        #endif
        /**
         * @brief Set the reference voltage on Portenta C33. This value is used by the ADC to convert analog values to digital values.
         * This can be particularly useful to increase the accuracy of the ADC when working with low voltages
         * @param voltage Reference voltage value in volts. It can be anything between 1.80V and 3.30V in steps of 0.10V. 
         * Any value outside this range or with different steps will not be accepted by the library.
         * @return True if the voltage was set successfully, false otherwise.
        */
        bool setReferenceVoltage(float voltage);

        // TODO add function to shut down the fuel gauge / and hibernate mode

    private:
        static uint8_t getRailVoltage(float voltage, int context);

        #if defined(ARDUINO_PORTENTA_C33)
            LowPower * lowPower;
        #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
            StandbyType standbyType = StandbyType::none;
            RTCWakeupDelay rtcWakeupDelay = RTCWakeupDelay(0, 0, 0);
        #endif         
};

#endif