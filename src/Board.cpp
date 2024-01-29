#include "Board.h"
#include "RTC.h"


Board::Board() {}

Board::Board(PF1550 * pmic) {
    this -> pmic = pmic;
    #if defined(ARDUINO_PORTENTA_C33)
    this -> lowPower = new LowPower();
    #endif
}


bool Board::isUSBPowered() {
    uint16_t registerValue = this->pmic->readPMICreg(Register::CHARGER_VBUS_SNS);
    return getBitFromOffset(registerValue, 2) == 0;
}

bool Board::isBatteryPowered() {
    uint8_t registerValue = this->pmic->readPMICreg(Register::CHARGER_BATT_SNS);
    uint8_t batteryPower = extractBits(registerValue, 0, 2);
    return batteryPower == 0;
}

void Board::setExternalSwitch(bool on) {
        if(on)
            this->pmic->getControlPointer()->turnSw2On(Sw2Mode::Normal);
        else
            this->pmic->getControlPointer()->turnSw2Off(Sw2Mode::Normal);
}

bool Board::setExternalVoltage(float v) {
        this -> setExternalSwitch(false);
        uint8_t voltageRegisterValue = getRailVoltage(v, 4);
        // TODO: Use a constant instead of 0xFF
        if (voltageRegisterValue != 0xFF){
            this -> pmic ->  writePMICreg(Register::PMIC_SW2_VOLT, voltageRegisterValue);
            if(this -> pmic ->  readPMICreg(Register::PMIC_SW2_VOLT) == voltageRegisterValue){
                this -> setExternalSwitch(true);
                return true;
            } else 
                return false;
        } else {
            return false;
        }
}


void Board::setCameraSwitch(bool on) {
    #if defined(ARDUINO_NICLA_VISION)
        if(on){
            this->pmic->getControlPointer()->turnLDO1On(Ldo1Mode::Normal);
            this->pmic->getControlPointer()->turnLDO2On(Ldo2Mode::Normal);
            this->pmic->getControlPointer()->turnLDO3On(Ldo3Mode::Normal);
        } else {
            this->pmic->getControlPointer()->turnLDO1Off(Ldo1Mode::Normal);
            this->pmic->getControlPointer()->turnLDO2Off(Ldo2Mode::Normal);
            this->pmic->getControlPointer()->turnLDO3Off(Ldo3Mode::Normal);
        }
    #else 
        #
    #endif
}

void Board::enableWakeupFromPin(uint8_t pin, PinStatus direction){
    #if defined(ARDUINO_PORTENTA_C33)
        lowPower->enableWakeupFromPin(pin, direction);
    #else 
        // TODO: What is happening here?
        #
    #endif
}

void Board::enableWakeupFromRTC(){
    #if defined(ARDUINO_PORTENTA_C33)
        lowPower->enableWakeupFromRTC();
    #else 
        // TODO: What is happening here?
        #
    #endif
}

bool Board::sleepFor(int hours, int minutes, int seconds, void (* const callbackFunction)()){
    RTC.begin();
    RTCTime currentTime;
    RTC->getTime(currentTime);
    // ...
}

bool Board::sleepFor(int hours, int minutes, int seconds, void (* const callbackFunction)(), RTClock * rtc){
    #if defined(ARDUINO_PORTENTA_C33)    
        RTCTime currentTime;
        if (!rtc -> getTime(currentTime)) {
            Serial.println("Failed to get current time"); 
            return false; // Failed to get current time
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
    #else 
        // TODO: What is happening here?
        #
    #endif
}
    

void Board::sleepUntilWakeupEvent(){
    #if defined(ARDUINO_PORTENTA_C33)
        lowPower -> sleep();
    #else
        // TODO: What is happening here? 
        #
    #endif
}

void Board::deepSleepUntilWakeupEvent(){
    #if defined(ARDUINO_PORTENTA_C33)
        lowPower -> deepSleep();
    #else 
        // TODO: What is happening here?
        #
    #endif
}

    void Board::turnPeripheralsOff(){
        this->pmic->getControlPointer()->turnLDO1Off(Ldo1Mode::Normal);
        this->pmic->getControlPointer()->turnLDO1Off(Ldo1Mode::Sleep);
        this->pmic->getControlPointer()->turnLDO1Off(Ldo1Mode::Standby);

        this->pmic->getControlPointer()->turnLDO2Off(Ldo2Mode::Normal);
        this->pmic->getControlPointer()->turnLDO2Off(Ldo2Mode::Sleep);
        this->pmic->getControlPointer()->turnLDO2Off(Ldo2Mode::Standby);

        this->pmic->getControlPointer()->turnLDO3Off(Ldo3Mode::Normal);
        this->pmic->getControlPointer()->turnLDO3Off(Ldo3Mode::Sleep);
        this->pmic->getControlPointer()->turnLDO3Off(Ldo3Mode::Standby);

        this->pmic->getControlPointer()->turnSw2Off(Sw2Mode::Normal);
        this->pmic->getControlPointer()->turnSw2Off(Sw2Mode::Sleep);
        this->pmic->getControlPointer()->turnSw2Off(Sw2Mode::Standby);

        this->pmic->getControlPointer()->turnSw1Off(Sw1Mode::Normal);
        this->pmic->getControlPointer()->turnSw1Off(Sw1Mode::Sleep);
        this->pmic->getControlPointer()->turnSw1Off(Sw1Mode::Standby);

        // TODO: Is it always on Wire3?
        Wire3.end();
    }

    void Board::turnPeripheralsOn(){
        this->pmic->getControlPointer()->clrBit(Register::PMIC_VSNVS_CTRL, (uint8_t)5);
        this->pmic->getControlPointer()->turnLDO1On(Ldo1Mode::Normal);
        this->pmic->getControlPointer()->turnLDO1On(Ldo1Mode::Sleep);
        this->pmic->getControlPointer()->turnLDO1On(Ldo1Mode::Standby);

        this->pmic->getControlPointer()->turnLDO2On(Ldo2Mode::Normal);
        this->pmic->getControlPointer()->turnLDO2On(Ldo2Mode::Sleep);
        this->pmic->getControlPointer()->turnLDO2On(Ldo2Mode::Standby);

        this->pmic->getControlPointer()->turnLDO3On(Ldo3Mode::Normal);
        this->pmic->getControlPointer()->turnLDO3On(Ldo3Mode::Sleep);
        this->pmic->getControlPointer()->turnLDO3On(Ldo3Mode::Standby);

        this->pmic->getControlPointer()->turnSw2On(Sw2Mode::Normal);
        this->pmic->getControlPointer()->turnSw2On(Sw2Mode::Sleep);
        this->pmic->getControlPointer()->turnSw2On(Sw2Mode::Standby);

        this->pmic->getControlPointer()->turnSw1On(Sw1Mode::Normal);
        this->pmic->getControlPointer()->turnSw1On(Sw1Mode::Sleep);
        this->pmic->getControlPointer()->turnSw1On(Sw1Mode::Standby);
    }

 

    void Board::setCommunicationSwitch(bool on){
        if(on)
            this->pmic->getControlPointer()->turnSw1On(Sw1Mode::Normal);
        else
            this->pmic->getControlPointer()->turnSw1Off(Sw1Mode::Normal);
    }

    bool Board::setAnalogVoltage(float v) {
        uint8_t voltageRegisterValue = getRailVoltage(v, CONTEXT_LDO1);
        // TODO: Use a constant instead of 0xFF
        // TODO: Simplify boolean logic. Use catch clause and return directly the value of the comparison
        if (voltageRegisterValue != 0xFF){
            this->pmic->writePMICreg(Register::PMIC_LDO1_VOLT, voltageRegisterValue);
            if (this->pmic->readPMICreg(Register::PMIC_LDO1_VOLT) == voltageRegisterValue)
                return true;
            else 
                return false;
        } else {
            return false;
        }
    }

    bool Board::setReferenceVoltage(float v){
        uint8_t voltageRegisterValue = getRailVoltage(v, CONTEXT_LDO2);
        // TODO: Use a constant instead of 0xFF
        // TODO: Simplify boolean logic. Use catch clause and return directly the value of the comparison
        if (voltageRegisterValue != 0xFF){
            this->pmic->writePMICreg(Register::PMIC_LDO2_VOLT, voltageRegisterValue);
            if (this->pmic->readPMICreg(Register::PMIC_LDO2_VOLT) == voltageRegisterValue)
                return true;
            else 
                return false;
        } else {
            return false;
        }
    }


