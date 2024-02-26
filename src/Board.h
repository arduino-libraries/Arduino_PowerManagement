#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>
#include <Arduino_PF1550.h>
#include "wireUtils.h"


#if defined(ARDUINO_PORTENTA_C33) 
    #include "Arduino_Portenta_C33_LowPower.h"
    #include "RTC.h"
#elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
    #include "Arduino_LowPowerPortentaH7.h"
#endif 

#define CONTEXT_LDO2 2
#define CONTEXT_SW 3 

enum class lowPowerStandbyType {
    NONE = 0,
    untilPinActivity = 1,
    untilTimeElapsed = 2,
    untilBoth = 3
};

constexpr int emptyRegister = 0xFF;

class Board {
    public:
        /**
         * @brief Default constructor for the Board class.
        */
        Board();


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
         * Set the voltage for the external power rail.
         * This lane powers the pin labeled 3V3 on the board.
         * @param on True to enable this power rail, false to disable it.
         */
        void setExternalPowerEnabled(bool on);


        /**
         * Set the voltage for the external power rail.
         * This lane powers the pin labeled 3V3 on the board.
         * @param voltage float value of the voltage value to set. `voltage` has to be one of the following (1.10, 1.20, 1.35, 1.50, 1.80, 2.50, 3.00 and 3.30)
         * @return True if successful, false otherwise.
        */
        bool setExternalVoltage(float voltage); 
    
  
        /**
         * @brief Set the camera power rail switch direction on boards with a built-in camera.
         * @param enabled True to turn on the switches, false to turn them off.
        */
        void setCameraPowerEnabled(bool enabled); 


        #if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
        void enableWakeupFromPin();
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
        /**
         * @brief Put the device in sleep mode for a specified amount of time.
         * @param hours The number of hours to sleep.
         * @param minutes The number of minutes to sleep.
         * @param seconds The number of seconds to sleep.
         * @param callbackFunction The function to call when the device wakes up.
         * @param RTC The RTC instance to use for the sleep function.
         * @return True if successful, false otherwise.
        */
        bool sleepFor(int hours, int minutes, int seconds, void (* const callbackFunction)(), RTClock * rtc);
   

        /**
         * @brief Put the device in sleep mode for a specified amount of time.
         * @param hours The number of hours to sleep.
         * @param minutes The number of minutes to sleep.
         * @param seconds The number of seconds to sleep.
         * @param callbackFunction The function to call when the device wakes up.
         * @return True if successful, false otherwise.
        */
        bool sleepFor(int hours, int minutes, int seconds, void (* const callbackFunction)());
    #endif

        /** 
         * @brief Put the device in sleep mode for a specified amount of time.
         * @param hours The number of hours to sleep.
         * @param minutes The number of minutes to sleep.
         * @param seconds The number of seconds to sleep.›
        */
        bool sleepFor(int hours, int minutes, int seconds);
   

        #if defined(ARDUINO_PORTENTA_C33)
        /**
         * Put the device into sleep mode until a wakeup event occurs
         * This sleep mode is ideal for applications requiring periodic wake-ups or brief intervals of inactivity and reduces consumption to a range between 6mA and 18mA depending on the state of the peripherals. 
         * This sleep mode resumes the operation from the last operation.
         * A wakeup event can be an interrupt on a pin or the RTC, depending on what you set with enableWakeupFromPin() and enableWakeupFromRTC().
         */
        void sleepUntilWakeupEvent();
        #endif

        /**
         * Put the device into deep sleep mode until a wakeup event occurs.
         * For scenarios demanding drastic power conservation, the Deep Sleep Mode significantly reduces the board's power usage to range between 90uA and 11mA depending on the state of the peripherals. 
         * This mode restarts the board on wakeup, effectively running the setup() function again.
         * A wakeup event can be an interrupt on a pin or the RTC, depending on what you set with enableWakeupFromPin() and enableWakeupFromRTC().
         */
        void deepSleepUntilWakeupEvent();

        /**
         * @brief Turn the peripherals on Portenta C33 (ADC, RGB LED, Secure Element, Wifi and Bluetooth) off.
        */
        void setAllPeripheralsPower(bool on);

        /**
         * @brief Set the communication power rail switch direction on Portenta C33 (Wifi, Bluetooth and Secure Element)
         * @param on True to turn on the switches, false to turn them off.
        */
        void setCommunicationPeripheralsPower(bool on);
        
        /**
         * @brief Set the analog digital converter power rail switch direction on Portenta C33.
         * @param on True to turn on the switches, false to turn them off.
        */
        void setAnalogDigitalConverterPower(bool on);

        /**
         * @brief Set the reference voltage on Portenta C33. This value is used by the ADC to convert analog values to digital values.
         * This can be particularly useful to increase the accuracy of the ADC when working with low voltages
         * @param voltage float value of the voltage value to set. It can be any value between 1.80V and 3.30V in steps of 0.10V. Any value outside this range or with different steps will not be accepted by the library.
         * @return True if successful, false otherwise.
        */
        bool setReferenceVoltage(float voltage);
        #endif
        
     

    private:
        PF1550 * pPMIC;
        static uint8_t getRailVoltage(float voltage, int context);

        #if defined(ARDUINO_PORTENTA_C33)
            LowPower * pLowPower;
        #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
            lowPowerStandbyType standbyType = lowPowerStandbyType::NONE;
            RTCWakeupDelay rtcWakeupDelay = RTCWakeupDelay(0, 0, 0);
        #endif 
        
};