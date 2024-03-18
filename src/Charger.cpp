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

ChargingState Charger::getState(){
    uint16_t reg_val = PMIC.readPMICreg(Register::CHARGER_CHG_SNS);
    switch (extractBits(reg_val, 0, 3)) {
        case 0:
            return ChargingState::PreCharge;
        case 1:
            return ChargingState::FastChargeConstantCurrent;
        case 2:
            return ChargingState::FastChargeConstantVoltage;
        case 3:
            return ChargingState::EndOfCharge;
        case 4:
            return ChargingState::Done;
        case 6:
            return ChargingState::TimerFaultError;
        case 7:
            return ChargingState::ThermistorSuspendError;
        case 8:
            return ChargingState::ChargerDisabled;
        case 9:
            return ChargingState::BatteryOvervoltageError;
        case 12:
            return ChargingState::ChargerBypassed;
        default:
            return ChargingState::None;
    }
}