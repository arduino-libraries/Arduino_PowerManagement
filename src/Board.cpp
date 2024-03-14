#include "Board.h"


Board::Board() {
 #if defined(ARDUINO_PORTENTA_C33)
        this -> pLowPower = new LowPower();
    #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_NICLA_VISION)
        if (CM7_CPUID == HAL_GetCurrentCPUID())
        {
            if (LowPowerReturnCode::success != LowPower.checkOptionBytes()){
                LowPower.prepareOptionBytes();
            }
            bootM4();
        }
    #endif 
}

bool Board::isUSBPowered() {
    uint16_t registerValue = PMIC.readPMICreg(Register::CHARGER_VBUS_SNS);
    return getBitFromOffset(registerValue, 2) == 0;
}

bool Board::isBatteryPowered() {
    uint8_t registerValue = PMIC.readPMICreg(Register::CHARGER_BATT_SNS);
    uint8_t batteryPower = extractBits(registerValue, 0, 2);
    return batteryPower == 0;
}

void Board::setExternalPowerEnabled(bool on) {
        if(on)
            PMIC.getControl()->turnSw2On(Sw2Mode::Normal);
        else
            PMIC.getControl()->turnSw2Off(Sw2Mode::Normal);
}

bool Board::setExternalVoltage(float v) {
        this -> setExternalPowerEnabled(false);
        uint8_t voltageRegisterValue = getRailVoltage(v, 4);
        if (voltageRegisterValue != emptyRegister){
            PMIC.writePMICreg(Register::PMIC_SW2_VOLT, voltageRegisterValue);
            if(PMIC.readPMICreg(Register::PMIC_SW2_VOLT) == voltageRegisterValue){
                this -> setExternalPowerEnabled(true);
                return true;
            } else 
                return false;
        } else {
            return false;
        }
}

void Board::setCameraPowerEnabled(bool on) {
    #if defined(ARDUINO_NICLA_VISION)
        if(on){
            PMIC.getControl()->turnLDO1On(Ldo1Mode::Normal);
            PMIC.getControl()->turnLDO2On(Ldo2Mode::Normal);
            PMIC.getControl()->turnLDO3On(Ldo3Mode::Normal);
        } else {
            PMIC.getControl()->turnLDO1Off(Ldo1Mode::Normal);
            PMIC.getControl()->turnLDO2Off(Ldo2Mode::Normal);
            PMIC.getControl()->turnLDO3Off(Ldo3Mode::Normal);
        }
    #else 
        #warning "This feature is currently only supported on the Nicla Vision Board"
    #endif
}

#if defined(ARDUINO_PORTENTA_C33) 
    void Board::enableWakeupFromPin(uint8_t pin, PinStatus direction){
        pLowPower->enableWakeupFromPin(pin, direction);
    }

#endif

#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
void Board::enableWakeupFromPin(){
    if(standbyType == lowPowerStandbyType::NONE){
        standbyType = lowPowerStandbyType::untilPinActivity;
    } else if (standbyType == lowPowerStandbyType::untilTimeElapsed){
        standbyType = lowPowerStandbyType::untilBoth;
    }
}

void Board::enableSleepWhenIdle(){
    LowPower.allowDeepSleep();
}
#endif


void Board::enableWakeupFromRTC(){
    #if defined(ARDUINO_PORTENTA_C33)
        pLowPower->enableWakeupFromRTC();
    #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
        if(standbyType == lowPowerStandbyType::NONE){
            standbyType = lowPowerStandbyType::untilTimeElapsed;
        } else if (standbyType == lowPowerStandbyType::untilPinActivity){
            standbyType = lowPowerStandbyType::untilBoth;
        }
    #endif
}


#if defined(ARDUINO_PORTENTA_C33)
bool Board::sleepFor(int hours, int minutes, int seconds, void (* const callbackFunction)(), RTClock * rtc){
    RTCTime currentTime;
    if (!rtc -> getTime(currentTime)) {
        Serial.println("Failed to get current time"); 
        return false; 
    }
    delay(1);


    // Convert current time to UNIX timestamp and add the desired interval
    time_t currentTimestamp = currentTime.getUnixTime();
    currentTimestamp += hours * 3600 + minutes * 60 + seconds;

    // Convert back to RTCTime
    RTCTime alarmTime(currentTimestamp);

    // Configure the alarm match criteria
    AlarmMatch match;
    match.addMatchSecond(); // Trigger the alarm when the seconds match
    match.addMatchMinute(); // Trigger the alarm when the minutes match
    match.addMatchHour();   // Trigger the alarm when the hours match

    // Set the alarm callback (assuming you have a callback function named alarmCallback)
    if (!rtc -> setAlarmCallback(callbackFunction, alarmTime, match)) {
        return false; // Failed to set the alarm
    }
    delay(1);
    return true;   
}

bool Board::sleepFor(int hours, int minutes, int seconds, void (* const callbackFunction)()){
    return this -> sleepFor(hours, minutes, seconds, callbackFunction, &RTC);
}
#endif

    
bool Board::sleepFor(int hours, int minutes, int seconds){
    #if defined(ARDUINO_PORTENTA_C33)
        return this -> sleepFor(hours, minutes, seconds, NULL, &RTC);
    #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
        this -> rtcWakeupDelay = RTCWakeupDelay(hours, minutes, seconds);
    #endif
}

    
#if defined(ARDUINO_PORTENTA_C33)
void Board::sleepUntilWakeupEvent(){
    pLowPower -> sleep();
}
#endif

void Board::deepSleepUntilWakeupEvent(){
    #if defined(ARDUINO_PORTENTA_C33)
        pLowPower -> deepSleep();
    #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
        if(standbyType == lowPowerStandbyType::untilBoth)
            LowPower.standbyM7(LowPowerStandbyType::untilPinActivity | LowPowerStandbyType::untilTimeElapsed, rtcWakeupDelay);
        else if (standbyType == lowPowerStandbyType::untilPinActivity)
            LowPower.standbyM7(LowPowerStandbyType::untilPinActivity);
        else if (standbyType == lowPowerStandbyType::untilTimeElapsed)
           LowPower.standbyM7(LowPowerStandbyType::untilTimeElapsed, rtcWakeupDelay);

    #endif
}

    void Board::setAllPeripheralsPower(bool on){
        #if defined(ARDUINO_PORTENTA_C33)
            this -> setCommunicationPeripheralsPower(on);
            this -> setExternalPowerEnabled(on);
            this -> setAnalogDigitalConverterPower(on);
            Wire3.end();
        #else if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4)
        if(on){
            PMIC.getControl() -> turnLDO2On(Ldo2Mode::Normal);
            PMIC.getControl() -> turnLDO2On(Ldo2Mode::Sleep);
            PMIC.getControl() -> turnLDO2On(Ldo2Mode::Standby);
            PMIC.getControl() -> turnLDO1On(Ldo1Mode::Normal);
            PMIC.getControl() -> turnLDO1On(Ldo1Mode::Sleep);
            PMIC.getControl() -> turnLDO1On(Ldo1Mode::Standby);
            PMIC.getControl() -> turnLDO3On(Ldo3Mode::Normal);
            PMIC.getControl() -> turnLDO3On(Ldo3Mode::Sleep);
            PMIC.getControl() -> turnLDO3On(Ldo3Mode::Standby);
            PMIC.getControl() -> turnSw1On(Sw1Mode::Normal);
            PMIC.getControl() -> turnSw1On(Sw1Mode::Sleep);
            PMIC.getControl() -> turnSw1On(Sw1Mode::Standby);
        } else {
            PMIC.getControl() -> turnLDO2Off(Ldo2Mode::Normal);
            PMIC.getControl() -> turnLDO2Off(Ldo2Mode::Sleep);
            PMIC.getControl() -> turnLDO2Off(Ldo2Mode::Standby);
            PMIC.getControl() -> turnLDO1Off(Ldo1Mode::Normal);
            PMIC.getControl() -> turnLDO1Off(Ldo1Mode::Sleep);
            PMIC.getControl() -> turnLDO1Off(Ldo1Mode::Standby);
            PMIC.getControl() -> turnLDO3Off(Ldo3Mode::Normal);
            PMIC.getControl() -> turnLDO3Off(Ldo3Mode::Sleep);
            PMIC.getControl() -> turnLDO3Off(Ldo3Mode::Standby);
            PMIC.getControl() -> turnSw1Off(Sw1Mode::Normal);
            PMIC.getControl() -> turnSw1Off(Sw1Mode::Sleep);
            PMIC.getControl() -> turnSw1Off(Sw1Mode::Standby);
            Wire1.end();
        }
           
        #endif

        /*
        if(on){


            PMIC.getControl()->clrBit(Register::PMIC_VSNVS_CTRL, (uint8_t)5);
            PMIC.getControl()->turnLDO1On(Ldo1Mode::Normal);
            PMIC.getControl()->turnLDO1On(Ldo1Mode::Sleep);
            PMIC.getControl()->turnLDO1On(Ldo1Mode::Standby);

            PMIC.getControl()->turnLDO2On(Ldo2Mode::Normal);
            PMIC.getControl()->turnLDO2On(Ldo2Mode::Sleep);
            PMIC.getControl()->turnLDO2On(Ldo2Mode::Standby);

            PMIC.getControl()->turnLDO3On(Ldo3Mode::Normal);
            PMIC.getControl()->turnLDO3On(Ldo3Mode::Sleep);
            PMIC.getControl()->turnLDO3On(Ldo3Mode::Standby);

            PMIC.getControl()->turnSw2On(Sw2Mode::Normal);
            PMIC.getControl()->turnSw2On(Sw2Mode::Sleep);
            PMIC.getControl()->turnSw2On(Sw2Mode::Standby);

            PMIC.getControl()->turnSw1On(Sw1Mode::Normal);
            PMIC.getControl()->turnSw1On(Sw1Mode::Sleep);
            PMIC.getControl()->turnSw1On(Sw1Mode::Standby);
        } else {
            PMIC.getControl()->turnLDO1Off(Ldo1Mode::Normal);
            PMIC.getControl()->turnLDO1Off(Ldo1Mode::Sleep);
            PMIC.getControl()->turnLDO1Off(Ldo1Mode::Standby);

            PMIC.getControl()->turnLDO2Off(Ldo2Mode::Normal);
            PMIC.getControl()->turnLDO2Off(Ldo2Mode::Sleep);
            PMIC.getControl()->turnLDO2Off(Ldo2Mode::Standby);

            PMIC.getControl()->turnLDO3Off(Ldo3Mode::Normal);
            PMIC.getControl()->turnLDO3Off(Ldo3Mode::Sleep);
            PMIC.getControl()->turnLDO3Off(Ldo3Mode::Standby);

            PMIC.getControl()->turnSw2Off(Sw2Mode::Normal);
            PMIC.getControl()->turnSw2Off(Sw2Mode::Sleep);
            PMIC.getControl()->turnSw2Off(Sw2Mode::Standby);

            PMIC.getControl()->turnSw1Off(Sw1Mode::Normal);
            PMIC.getControl()->turnSw1Off(Sw1Mode::Sleep);
            PMIC.getControl()->turnSw1Off(Sw1Mode::Standby);

            #if defined(ARDUINO_PORTENTA_C33)
                Wire3.end();
            #endif
        }
    */
    }

    void Board::setAnalogDigitalConverterPower(bool on){
        if(on){
            PMIC.getControl()->turnLDO1On(Ldo1Mode::Normal);
            PMIC.getControl()->turnLDO1On(Ldo1Mode::Sleep);
            PMIC.getControl()->turnLDO1On(Ldo1Mode::Standby);
        } else {
            PMIC.getControl()->turnLDO1Off(Ldo1Mode::Normal);
            PMIC.getControl()->turnLDO1Off(Ldo1Mode::Sleep);
            PMIC.getControl()->turnLDO1Off(Ldo1Mode::Standby);
        }
    }

    void Board::setCommunicationPeripheralsPower(bool on){
        if(on)
            PMIC.getControl()->turnSw1On(Sw1Mode::Normal);
        else
            PMIC.getControl()->turnSw1Off(Sw1Mode::Normal);
    }


bool Board::setReferenceVoltage(float v) {
    uint8_t voltageRegisterValue = getRailVoltage(v, CONTEXT_LDO2);

    // If voltageRegisterValue is not empty, write it to the PMIC register and return the result of the comparison directly.
    if (voltageRegisterValue != emptyRegister) {
        PMIC.writePMICreg(Register::PMIC_LDO2_VOLT, voltageRegisterValue);
        return (PMIC.readPMICreg(Register::PMIC_LDO2_VOLT) == voltageRegisterValue);
    }

    return false;
}


 uint8_t Board::getRailVoltage(float voltage, int context) {
    switch (context) {
        case 2: // LDO2
            if (voltage == 1.80f) return static_cast<uint8_t>(Ldo2Voltage::V_1_80);
            else if (voltage == 1.90f) return static_cast<uint8_t>(Ldo2Voltage::V_1_90);
            else if (voltage == 2.00f) return static_cast<uint8_t>(Ldo2Voltage::V_2_00);
            else if (voltage == 2.10f) return static_cast<uint8_t>(Ldo2Voltage::V_2_10);
            else if (voltage == 2.20f) return static_cast<uint8_t>(Ldo2Voltage::V_2_20);
            else if (voltage == 2.30f) return static_cast<uint8_t>(Ldo2Voltage::V_2_30);
            else if (voltage == 2.40f) return static_cast<uint8_t>(Ldo2Voltage::V_2_40);
            else if (voltage == 2.50f) return static_cast<uint8_t>(Ldo2Voltage::V_2_50);
            else if (voltage == 2.60f) return static_cast<uint8_t>(Ldo2Voltage::V_2_60);
            else if (voltage == 2.70f) return static_cast<uint8_t>(Ldo2Voltage::V_2_70);
            else if (voltage == 2.80f) return static_cast<uint8_t>(Ldo2Voltage::V_2_80);
            else if (voltage == 2.90f) return static_cast<uint8_t>(Ldo2Voltage::V_2_90);
            else if (voltage == 3.00f) return static_cast<uint8_t>(Ldo2Voltage::V_3_00);
            else if (voltage == 3.10f) return static_cast<uint8_t>(Ldo2Voltage::V_3_10);
            else if (voltage == 3.20f) return static_cast<uint8_t>(Ldo2Voltage::V_3_20);
            else if (voltage == 3.30f) return static_cast<uint8_t>(Ldo2Voltage::V_3_30);
            break;
            
        case 3: // SW1
            if (voltage == 1.10f) return static_cast<uint8_t>(Sw1Voltage::V_1_10);
            else if (voltage == 1.20f) return static_cast<uint8_t>(Sw1Voltage::V_1_20);
            else if (voltage == 1.35f) return static_cast<uint8_t>(Sw1Voltage::V_1_35);
            else if (voltage == 1.50f) return static_cast<uint8_t>(Sw1Voltage::V_1_50);
            else if (voltage == 1.80f) return static_cast<uint8_t>(Sw1Voltage::V_1_80);
            else if (voltage == 2.50f) return static_cast<uint8_t>(Sw1Voltage::V_2_50);
            else if (voltage == 3.00f) return static_cast<uint8_t>(Sw1Voltage::V_3_00);
            else if (voltage == 3.30f) return static_cast<uint8_t>(Sw1Voltage::V_3_30);
            break;

        case 4: // Sw2
          if (voltage == 1.10f) return static_cast<uint8_t>(Sw2Voltage::V_1_10);
            else if (voltage == 1.20f) return static_cast<uint8_t>(Sw2Voltage::V_1_20);
            else if (voltage == 1.35f) return static_cast<uint8_t>(Sw2Voltage::V_1_35);
            else if (voltage == 1.50f) return static_cast<uint8_t>(Sw2Voltage::V_1_50);
            else if (voltage == 1.80f) return static_cast<uint8_t>(Sw2Voltage::V_1_80);
            else if (voltage == 2.50f) return static_cast<uint8_t>(Sw2Voltage::V_2_50);
            else if (voltage == 3.00f) return static_cast<uint8_t>(Sw2Voltage::V_3_00);
            else if (voltage == 3.30f) return static_cast<uint8_t>(Sw2Voltage::V_3_30);
            break;

            
        default:
            return emptyRegister;
            break;
    }
    

    return emptyRegister;
}