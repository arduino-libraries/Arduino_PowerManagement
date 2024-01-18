#include "Board.h"


Board::Board() {}

Board::Board(PF1550 * _pPMIC) {
    this -> pPMIC = _pPMIC;
    #if defined(ARDUINO_PORTENTA_C33)
    this -> pLowPower = new LowPower();
    #endif
}


bool Board::isUSBPowered() {
    uint16_t reg_val = this -> pPMIC ->  readPMICreg(Register::CHARGER_VBUS_SNS);
    return getBitFromOffset(reg_val, 2) == 0;
}

bool Board::isBatteryPowered() {
    uint8_t reg_val = this -> pPMIC ->  readPMICreg(Register::CHARGER_BATT_SNS);
    uint8_t batPower = extractBits(reg_val, 0, 2);
    Serial.println(batPower);
    return batPower == 0;
}

void Board::setExternalSwitch(bool on) {
        if(on)
            this -> pPMIC -> getControlPointer()  -> turnSw2On(Sw2Mode::Normal);    
        else 
            this -> pPMIC -> getControlPointer()  -> turnSw2Off(Sw2Mode::Normal); 
}

bool Board::setExternalVoltage(float v) {
        this -> setExternalSwitch(false);
        uint8_t voltage_reg = getRailVoltage(v, 4);
        if (voltage_reg != 0xFF){
            this -> pPMIC ->  writePMICreg(Register::PMIC_SW2_VOLT, voltage_reg);
            if(this -> pPMIC ->  readPMICreg(Register::PMIC_SW2_VOLT) == voltage_reg){
                this -> setExternalSwitch(true);
                return true;
            } else 
                return false;
        } else {
            return false;
        }
}




#if defined(ARDUINO_NICLA_VISION)
void Board::setCameraSwitch(bool on) {
        if(on){
            this -> pPMIC -> getControlPointer() -> turnLDO1On(Ldo1Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO2On(Ldo2Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO3On(Ldo3Mode::Normal);
        } else {
            this -> pPMIC -> getControlPointer() -> turnLDO1Off(Ldo1Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO2Off(Ldo2Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO3Off(Ldo3Mode::Normal);
        }
}
#endif

#if defined(ARDUINO_PORTENTA_C33)

    void Board::enableWakeupFromPin(uint8_t pin, PinStatus direction){
        pLowPower -> enableWakeupFromPin(pin, direction);
    }

    void Board::enableWakeupFromRTC(){
        pLowPower -> enableWakeupFromRTC();
    }


    bool Board::sleepFor(int hours, int minutes, int seconds, void (* const callbackFunction)(), RTClock * rtc){
    {
        
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
        }
    }

    void Board::sleepUntilWakeupEvent(){
        pLowPower -> sleep();
    }

    void Board::deepSleepUntilWakeupEvent(){
        pLowPower -> deepSleep();
    }

    void Board::turnPeripheralsOff(){
            this -> pPMIC -> getControlPointer() -> turnLDO1Off(Ldo1Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO1Off(Ldo1Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnLDO1Off(Ldo1Mode::Standby);

            this -> pPMIC -> getControlPointer() -> turnLDO2Off(Ldo2Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO2Off(Ldo2Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnLDO2Off(Ldo2Mode::Standby);

            this -> pPMIC -> getControlPointer() -> turnLDO3Off(Ldo3Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO3Off(Ldo3Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnLDO3Off(Ldo3Mode::Standby);

            this -> pPMIC -> getControlPointer() -> turnSw2Off(Sw2Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnSw2Off(Sw2Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnSw2Off(Sw2Mode::Standby);

            this -> pPMIC -> getControlPointer() ->  turnSw1Off(Sw1Mode::Normal);
            this -> pPMIC -> getControlPointer() ->  turnSw1Off(Sw1Mode::Sleep);
            this -> pPMIC -> getControlPointer() ->  turnSw1Off(Sw1Mode::Standby);

            Wire3.end();
    }

    void Board::turnPeripheralsOn(){
            this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_VSNVS_CTRL, (uint8_t)5);       
            this -> pPMIC -> getControlPointer() -> turnLDO1On(Ldo1Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO1On(Ldo1Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnLDO1On(Ldo1Mode::Standby);

            this -> pPMIC -> getControlPointer() -> turnLDO2On(Ldo2Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO2On(Ldo2Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnLDO2On(Ldo2Mode::Standby);

            this -> pPMIC -> getControlPointer() -> turnLDO3On(Ldo3Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO3On(Ldo3Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnLDO3On(Ldo3Mode::Standby);

            this -> pPMIC -> getControlPointer() -> turnSw2On(Sw2Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnSw2On(Sw2Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnSw2On(Sw2Mode::Standby);

            this -> pPMIC -> getControlPointer() ->  turnSw1On(Sw1Mode::Normal);
            this -> pPMIC -> getControlPointer() ->  turnSw1On(Sw1Mode::Sleep);
            this -> pPMIC -> getControlPointer() ->  turnSw1On(Sw1Mode::Standby);
    }

 

    void Board::setCommunicationSwitch(bool on){
        if(on)
            this -> pPMIC -> getControlPointer()  -> turnSw1On(Sw1Mode::Normal);     
        else
            this -> pPMIC -> getControlPointer()  -> turnSw1Off(Sw1Mode::Normal);   
    }

    bool Board::setAnalogVoltage(float v) {
        uint8_t voltage_reg = getRailVoltage(v, CONTEXT_LDO1);
        if (voltage_reg != 0xFF){
            this -> pPMIC ->  writePMICreg(Register::PMIC_LDO1_VOLT, voltage_reg);
            if(this -> pPMIC ->  readPMICreg(Register::PMIC_LDO1_VOLT) == voltage_reg)
                return true;
            else 
                return false;
        } else {
            return false;
        }
    }

    bool Board::setReferenceVoltage(float v){
        uint8_t voltage_reg = getRailVoltage(v, CONTEXT_LDO2);
        if (voltage_reg != 0xFF){
            this -> pPMIC ->  writePMICreg(Register::PMIC_LDO2_VOLT, voltage_reg);
            if(this -> pPMIC ->  readPMICreg(Register::PMIC_LDO2_VOLT) == voltage_reg)
                return true;
            else 
                return false;
        } else {
            return false;
        }
    }

#endif

