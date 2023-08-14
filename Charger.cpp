#include "Charger.h"


Charger::Charger(){}

Charger::Charger(PF1550* _pPMIC) : pPMIC(_pPMIC) {}

void Charger::setChargeCurrent(ChargeCurrent i) {
    pPMIC -> getControlPointer() -> setFastChargeCurrent(i);
}

void Charger::setChargeVoltage(ChargeVoltage v) {
    pPMIC -> getControlPointer() -> setFastChargeVoltage(v);
}

void Charger::setEndOfChargeCurrent(EndOfChargeCurrent i) {
    pPMIC -> getControlPointer() -> setEndOfChargeCurrent(i);
}

void Charger::setMaxInputCurrent(MaxInputCurrent i) {
    pPMIC -> getControlPointer() -> setInputCurrentLimit(i);
}

bool Charger::enableCharger(){
    pPMIC -> writePMICreg(Register::CHARGER_CHG_OPER, 0x02);
    return pPMIC->readPMICreg(Register::CHARGER_CHG_OPER) == 0x02;
}

bool Charger::disableCharger(){
    pPMIC -> writePMICreg(Register::CHARGER_CHG_OPER, 0x01);
    return pPMIC->readPMICreg(Register::CHARGER_CHG_OPER) == 0x01;
}

ChargeStatus Charger::getChargeStatus(){
    uint16_t reg_val = this -> pPMIC ->  readPMICreg(Register::CHARGER_CHG_SNS);
    uint16_t bits3to0 = extractBits(reg_val, 0, 3);

    switch (bits3to0) {
        case 0:
            return PRECHARGE;
        case 1:
            return FAST_CHARGE_CC;
        case 2:
            return FAST_CHARGE_CV;
        case 3:
            return END_OF_CHARGE;
        case 4:
            return DONE;
        case 6:
            return TIMER_FAULT;
        case 7:
            return THERMISTOR_SUSPEND;
        case 8:
            return OFF;
        case 9:
            return BATTERY_OVERVOLTAGE;
        case 12:
            return LINEAR_ONLY;
        default:
            return NONE;
    }
}