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

void Charger::setInputCurrentLimit(InputCurrentLimit current) {
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
    switch (extractBits(reg_val, 0, 3)) {
        case 0:
            return ChargeStatus::PreCharge;
        case 1:
            return ChargeStatus::FastChargeConstantCurrent;
        case 2:
            return ChargeStatus::FastChargeConstantVoltage;
        case 3:
            return ChargeStatus::EndOfCharge;
        case 4:
            return ChargeStatus::Done;
        case 6:
            return ChargeStatus::TimerFaultError;
        case 7:
            return ChargeStatus::ThermistorSuspendError;
        case 8:
            return ChargeStatus::ChargerDisabled;
        case 9:
            return ChargeStatus::BatteryOvervoltageError;
        case 12:
            return ChargeStatus::ChargerBypassMode;
        default:
            return ChargeStatus::None;
    }
}