#include "Board.h"

// Constructor
Board::Board() {

}

Board::Board(PF1550 * _pPMIC) {
    this -> pPMIC = _pPMIC;
}


// Check if the board is powered through USB

bool Board::isUSBPowered() {
    uint16_t reg_val = this -> pPMIC ->  readPMICreg(Register::CHARGER_VBUS_SNS);
    return getBitFromOffset(reg_val, 2) == 0;
}

bool Board::isBatteryPowered() {
    uint8_t reg_val = this -> pPMIC ->  readPMICreg(Register::CHARGER_BATT_SNS);
    uint8_t batPower = extractBits(reg_val, 0, 2);
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
        if(on)
            this -> pPMIC -> getControlPointer() -> turnLDO1On(Ldo1Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO2On(Ldo2Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO3On(Ldo3Mode::Normal);
        else
            this -> pPMIC -> getControlPointer() -> turnLDO1Off(Ldo1Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO2Off(Ldo2Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO3Off(Ldo3Mode::Normal);
}
#endif

#if defined(ARDUINO_PORTENTA_C33)

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

