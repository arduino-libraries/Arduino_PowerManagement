#include "Charger.h"


Charger::Charger(){}

Charger::Charger(PF1550* pmic) : pmic(pmic) {
}

void Charger::setChargeCurrent(ChargeCurrent current) {
    pmic -> getControlPointer() -> setFastChargeCurrent(current);
}

void Charger::setChargeVoltage(ChargeVoltage voltage) {
    pmic -> getControlPointer() -> setFastChargeVoltage(voltage);
}

void Charger::setEndOfChargeCurrent(EndOfChargeCurrent current) {
    pmic -> getControlPointer() -> setEndOfChargeCurrent(current);
}

void Charger::setMaxInputCurrent(MaxInputCurrent i) {
    pmic -> getControlPointer() -> setInputCurrentLimit(current);
}

bool Charger::enable(){
    pmic -> writePMICreg(Register::CHARGER_CHG_OPER, 0x02);
    return pmic->readPMICreg(Register::CHARGER_CHG_OPER) == 0x02;
}

bool Charger::disable(){
    pmic -> writePMICreg(Register::CHARGER_CHG_OPER, 0x01);
    return pmic->readPMICreg(Register::CHARGER_CHG_OPER) == 0x01;
}

ChargeStatus Charger::getChargeStatus(){
    uint16_t reg_val = this -> pmic ->  readPMICreg(Register::CHARGER_CHG_SNS);
    uint16_t bits3to0 = extractBits(reg_val, 0, 3);

    // TODO: Unused variable
    uint16_t temp_reg = this -> pmic ->  readPMICreg(Register::CHARGER_THM_REG_CNFG);


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