#include "Board.h"
#include <map>

std::map<float, Ldo2Voltage> ldo2VoltageMap = {
    {1.80f, Ldo2Voltage::V_1_80},
    {1.90f, Ldo2Voltage::V_1_90},
    {2.00f, Ldo2Voltage::V_2_00},
    {2.10f, Ldo2Voltage::V_2_10},
    {2.20f, Ldo2Voltage::V_2_20},
    {2.30f, Ldo2Voltage::V_2_30},
    {2.40f, Ldo2Voltage::V_2_40},
    {2.50f, Ldo2Voltage::V_2_50},
    {2.60f, Ldo2Voltage::V_2_60},
    {2.70f, Ldo2Voltage::V_2_70},
    {2.80f, Ldo2Voltage::V_2_80},
    {2.90f, Ldo2Voltage::V_2_90},
    {3.00f, Ldo2Voltage::V_3_00},
    {3.10f, Ldo2Voltage::V_3_10},
    {3.20f, Ldo2Voltage::V_3_20},
    {3.30f, Ldo2Voltage::V_3_30}
};

std::map<float, Sw1Voltage> sw1VoltageMap = {
    {1.10f, Sw1Voltage::V_1_10},
    {1.20f, Sw1Voltage::V_1_20},
    {1.35f, Sw1Voltage::V_1_35},
    {1.50f, Sw1Voltage::V_1_50},
    {1.80f, Sw1Voltage::V_1_80},
    {2.50f, Sw1Voltage::V_2_50},
    {3.00f, Sw1Voltage::V_3_00},
    {3.30f, Sw1Voltage::V_3_30}
};

std::map<float, Sw2Voltage> sw2VoltageMap = {
    {1.10f, Sw2Voltage::V_1_10},
    {1.20f, Sw2Voltage::V_1_20},
    {1.35f, Sw2Voltage::V_1_35},
    {1.50f, Sw2Voltage::V_1_50},
    {1.80f, Sw2Voltage::V_1_80},
    {2.50f, Sw2Voltage::V_2_50},
    {3.00f, Sw2Voltage::V_3_00},
    {3.30f, Sw2Voltage::V_3_30}
};

Board::Board() {
 #if defined(ARDUINO_PORTENTA_C33)
        this -> lowPower = new LowPower();
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
    return bitRead(registerValue, 2) == 0;
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

bool Board::setExternalVoltage(float voltage) {
        this -> setExternalPowerEnabled(false);
        uint8_t voltageRegisterValue = getRailVoltage(voltage, 4);

        if (voltageRegisterValue == EMPTY_REGISTER){                    
            return false;
        }

        PMIC.writePMICreg(Register::PMIC_SW2_VOLT, voltageRegisterValue);
        if(PMIC.readPMICreg(Register::PMIC_SW2_VOLT) == voltageRegisterValue){
            this -> setExternalPowerEnabled(true);
            return true;
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
    lowPower->enableWakeupFromPin(pin, direction);
}
#endif

#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
void Board::enableWakeupFromPin(){
    // If no wake up method is selected yet, set it to wake up from pin activity
    if(standbyType == LowPowerStandbyType::None){
        standbyType = LowPowerStandbyType::UntilPinActivity;
    // If there is already a wake up method selected, set it to wake up from both pin activity and time elapsed
    } else if (standbyType == LowPowerStandbyType::UntilTimeElapsed){
        standbyType = LowPowerStandbyType::UntilBothAreTrue;
    }
}

void Board::enableSleepWhenIdle(){
    LowPower.allowDeepSleep();
}
#endif


void Board::enableWakeupFromRTC(){
    #if defined(ARDUINO_PORTENTA_C33)
        lowPower->enableWakeupFromRTC();
    #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
       // If no wake up method is selected yet, set it to wake up from RTC
        if(standbyType == LowPowerStandbyType::None){
            standbyType = LowPowerStandbyType::UntilTimeElapsed;
        } else if (standbyType == LowPowerStandbyType::UntilPinActivity){
            standbyType = LowPowerStandbyType::UntilBothAreTrue;
        }
    #endif
}

#if defined(ARDUINO_PORTENTA_C33)
bool Board::sleepFor(int hours, int minutes, int seconds, void (* const callbackFunction)(), RTClock * rtc){
    RTCTime currentTime;
    if (!rtc -> getTime(currentTime)) {
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
        // TODO: Let's add an overload to accept RTCWakeupDelay as a parameter
        return this -> sleepFor(hours, minutes, seconds, NULL, &RTC);
    #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
        this -> rtcWakeupDelay = RTCWakeupDelay(hours, minutes, seconds);
    #endif
}
    
#if defined(ARDUINO_PORTENTA_C33)
void Board::sleepUntilWakeupEvent(){
    lowPower -> sleep();
}
#endif

void Board::deepSleepUntilWakeupEvent(){
    #if defined(ARDUINO_PORTENTA_C33)
        lowPower -> deepSleep();
    #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_NICLA_VISION)
        if(standbyType == LowPowerStandbyType::UntilBothAreTrue)
            LowPower.standbyM7(LowPowerStandbyType::UntilPinActivity | LowPowerStandbyType::UntilTimeElapsed, rtcWakeupDelay);
        else if (standbyType == LowPowerStandbyType::UntilPinActivity)
            LowPower.standbyM7(LowPowerStandbyType::UntilPinActivity);
        else if (standbyType == LowPowerStandbyType::UntilTimeElapsed)
           LowPower.standbyM7(LowPowerStandbyType::UntilTimeElapsed, rtcWakeupDelay);
    #endif
}

void Board::setAllPeripheralsPower(bool on){
    #if defined(ARDUINO_PORTENTA_C33)
        this -> setCommunicationPeripheralsPower(on);
        this -> setExternalPowerEnabled(on);
        this -> setAnalogDigitalConverterPower(on);
        // I2C needs to be shut down because the PMIC would still try
        // to communicate with the MCU.
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
        // I2C needs to be shut down because the PMIC would still try
        // to communicate with the MCU.
        Wire1.end();
    }
        
    #endif

    // TODO: What's going on here?
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


bool Board::setReferenceVoltage(float voltage) {
    uint8_t voltageRegisterValue = getRailVoltage(voltage, CONTEXT_LDO2);

    // If voltageRegisterValue is not empty, write it to the PMIC register 
    // and return the result of the comparison directly.
    if (voltageRegisterValue != EMPTY_REGISTER) {
        PMIC.writePMICreg(Register::PMIC_LDO2_VOLT, voltageRegisterValue);
        return (PMIC.readPMICreg(Register::PMIC_LDO2_VOLT) == voltageRegisterValue);
    }

    return false;
}

 uint8_t Board::getRailVoltage(float voltage, int context) {
    switch (context) {
        case CONTEXT_LDO2:
            if (ldo2VoltageMap.find(voltage) != ldo2VoltageMap.end()) {
                return static_cast<uint8_t>(ldo2VoltageMap[voltage]);
            }
            break;
            
        case CONTEXT_SW1:
            if (sw1VoltageMap.find(voltage) != sw1VoltageMap.end()) {
                return static_cast<uint8_t>(sw1VoltageMap[voltage]);
            }
            break;

        case CONTEXT_SW2:
            if (sw2VoltageMap.find(voltage) != sw2VoltageMap.end()) {
                return static_cast<uint8_t>(sw2VoltageMap[voltage]);
            }
            break;

        default:
            return EMPTY_REGISTER;
            break;
    }
    

    return EMPTY_REGISTER;
}
