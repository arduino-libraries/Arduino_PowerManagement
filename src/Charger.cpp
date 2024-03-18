#include "Charger.h"


Charger::Charger(){}


void Charger::setChargeCurrent(ChargeCurrent current) {
    PMIC.getControl() -> setFastChargeCurrent(current);
}

void Charger::setChargeVoltage(ChargeVoltage voltage) {
    PMIC.getControl() -> setFastChargeVoltage(voltage);
}

void Charger::setEndOfChargeCurrent(EndOfChargeCurrent current) {
    PMIC.getControl() -> setEndOfChargeCurrent(current);
}

void Charger::setInputCurrentLimit(InputCurrentLimit current) {
    PMIC.getControl() -> setInputCurrentLimit(current);
}

bool Charger::enable(){
    PMIC.writePMICreg(Register::CHARGER_CHG_OPER, 0x02);
    return PMIC.readPMICreg(Register::CHARGER_CHG_OPER) == 0x02;
}

bool Charger::disable(){
    PMIC.writePMICreg(Register::CHARGER_CHG_OPER, 0x01);
    return PMIC.readPMICreg(Register::CHARGER_CHG_OPER) == 0x01;
}

ChargeStatus Charger::getChargeStatus(){
    uint16_t reg_val = PMIC.readPMICreg(Register::CHARGER_CHG_SNS);
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