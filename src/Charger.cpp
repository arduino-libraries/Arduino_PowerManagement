#include "Charger.h"
#include <map>

std::map<uint16_t, ChargeCurrent> chargeCurrentMap = {
    {100, ChargeCurrent::I_100_mA},
    {150, ChargeCurrent::I_150_mA},
    {200, ChargeCurrent::I_200_mA},
    {250, ChargeCurrent::I_250_mA},
    {300, ChargeCurrent::I_300_mA},
    {350, ChargeCurrent::I_350_mA},
    {400, ChargeCurrent::I_400_mA},
    {450, ChargeCurrent::I_450_mA},
    {500, ChargeCurrent::I_500_mA},
    {550, ChargeCurrent::I_550_mA},
    {600, ChargeCurrent::I_600_mA},
    {650, ChargeCurrent::I_650_mA},
    {700, ChargeCurrent::I_700_mA},
    {750, ChargeCurrent::I_750_mA},
    {800, ChargeCurrent::I_800_mA},
    {850, ChargeCurrent::I_850_mA},
    {900, ChargeCurrent::I_900_mA},
    {950, ChargeCurrent::I_950_mA},
    {1000, ChargeCurrent::I_1000_mA}
};

std::map<float, ChargeVoltage> chargeVoltageMap = {
    {3.50, ChargeVoltage::V_3_50},
    {3.52, ChargeVoltage::V_3_52},
    {3.54, ChargeVoltage::V_3_54},
    {3.56, ChargeVoltage::V_3_56},
    {3.58, ChargeVoltage::V_3_58},
    {3.60, ChargeVoltage::V_3_60},
    {3.62, ChargeVoltage::V_3_62},
    {3.64, ChargeVoltage::V_3_64},
    {3.66, ChargeVoltage::V_3_66},
    {3.68, ChargeVoltage::V_3_68},
    {3.70, ChargeVoltage::V_3_70},
    {3.72, ChargeVoltage::V_3_72},
    {3.74, ChargeVoltage::V_3_74},
    {3.76, ChargeVoltage::V_3_76},
    {3.78, ChargeVoltage::V_3_78},
    {3.80, ChargeVoltage::V_3_80},
    {3.82, ChargeVoltage::V_3_82},
    {3.84, ChargeVoltage::V_3_84},
    {3.86, ChargeVoltage::V_3_86},
    {3.88, ChargeVoltage::V_3_88},
    {3.90, ChargeVoltage::V_3_90},
    {3.92, ChargeVoltage::V_3_92},
    {3.94, ChargeVoltage::V_3_94},
    {3.96, ChargeVoltage::V_3_96},
    {3.98, ChargeVoltage::V_3_98},
    {4.00, ChargeVoltage::V_4_00},
    {4.02, ChargeVoltage::V_4_02},
    {4.04, ChargeVoltage::V_4_04},
    {4.06, ChargeVoltage::V_4_06},
    {4.08, ChargeVoltage::V_4_08},
    {4.10, ChargeVoltage::V_4_10},
    {4.12, ChargeVoltage::V_4_12},
    {4.14, ChargeVoltage::V_4_14},
    {4.16, ChargeVoltage::V_4_16},
    {4.18, ChargeVoltage::V_4_18},
    {4.20, ChargeVoltage::V_4_20},
    {4.22, ChargeVoltage::V_4_22},
    {4.24, ChargeVoltage::V_4_24},
    {4.26, ChargeVoltage::V_4_26},
    {4.28, ChargeVoltage::V_4_28},
    {4.30, ChargeVoltage::V_4_30},
    {4.32, ChargeVoltage::V_4_32},
    {4.34, ChargeVoltage::V_4_34},
    {4.36, ChargeVoltage::V_4_36},
    {4.38, ChargeVoltage::V_4_38},
    {4.40, ChargeVoltage::V_4_40},
    {4.42, ChargeVoltage::V_4_42},
    {4.44, ChargeVoltage::V_4_44}
};

std::map<uint16_t, EndOfChargeCurrent> endOfChargeCurrentMap = {
    {5, EndOfChargeCurrent::I_5_mA},
    {10, EndOfChargeCurrent::I_10_mA},
    {20, EndOfChargeCurrent::I_20_mA},
    {30, EndOfChargeCurrent::I_30_mA},
    {50, EndOfChargeCurrent::I_50_mA}
};

std::map<uint16_t, InputCurrentLimit> inputCurrentLimitMap = {
    {10, InputCurrentLimit::I_10_mA},
    {15, InputCurrentLimit::I_15_mA},
    {20, InputCurrentLimit::I_20_mA},
    {25, InputCurrentLimit::I_25_mA},
    {30, InputCurrentLimit::I_30_mA},
    {35, InputCurrentLimit::I_35_mA},
    {40, InputCurrentLimit::I_40_mA},
    {45, InputCurrentLimit::I_45_mA},
    {50, InputCurrentLimit::I_50_mA},
    {100, InputCurrentLimit::I_100_mA},
    {150, InputCurrentLimit::I_150_mA},
    {200, InputCurrentLimit::I_200_mA},
    {300, InputCurrentLimit::I_300_mA},
    {400, InputCurrentLimit::I_400_mA},
    {500, InputCurrentLimit::I_500_mA},
    {600, InputCurrentLimit::I_600_mA},
    {700, InputCurrentLimit::I_700_mA},
    {800, InputCurrentLimit::I_800_mA},
    {900, InputCurrentLimit::I_900_mA},
    {1000, InputCurrentLimit::I_1000_mA},
    {1500, InputCurrentLimit::I_1500_mA}
};


Charger::Charger(){}

bool Charger::begin(){
    return PMIC.begin() == 0;
}

bool Charger::setChargeCurrent(uint16_t current) {
    #if defined(ARDUINO_NICLA_VISION)
        return false; // Not supported on Nicla Vision
    #endif

    if (chargeCurrentMap.find(current) != chargeCurrentMap.end()) {
        ChargeCurrent convertedCurrent = chargeCurrentMap[current];
        PMIC.getControl() -> setFastChargeCurrent(convertedCurrent);
        return true;
    }
    return false;
}

uint16_t Charger::getChargeCurrent() {
    auto currentValue = PMIC.readPMICreg(Register::CHARGER_CHG_CURR_CFG);
    currentValue = (currentValue & REG_CHG_CURR_CFG_CHG_CC_mask);
    ChargeCurrent current = static_cast<ChargeCurrent>(currentValue);
    for (auto const& [key, val] : chargeCurrentMap) {
        if (val == current) {
            return key;
        }
    }
    return -1;
}

float Charger::getChargeVoltage() {
    uint8_t currentValue = PMIC.readPMICreg(Register::CHARGER_BATT_REG);
    currentValue = (currentValue & REG_BATT_REG_CHCCV_mask);
    ChargeVoltage voltageValue = static_cast<ChargeVoltage>(currentValue);

    // Lookup the value in the map
    for (auto const& [key, val] : chargeVoltageMap) {
        if (val == voltageValue) {
            return key;
        }
    }
    return -1;
}

bool Charger::setChargeVoltage(float voltage) {
    if(chargeVoltageMap.find(voltage) != chargeVoltageMap.end()) {
        ChargeVoltage convertedVoltage = chargeVoltageMap[voltage];
        PMIC.getControl() -> setFastChargeVoltage(convertedVoltage);
        return true;
    }
    return false;
}

bool Charger::setEndOfChargeCurrent(uint16_t current) {
    #if defined(ARDUINO_NICLA_VISION)
        return false; // Not supported on Nicla Vision
    #endif
    if(endOfChargeCurrentMap.find(current) != endOfChargeCurrentMap.end()) {
        EndOfChargeCurrent convertedCurrent = endOfChargeCurrentMap[current];
        PMIC.getControl() -> setEndOfChargeCurrent(convertedCurrent);
        return true;
    }
    return false;
}

uint16_t Charger::getEndOfChargeCurrent() {
    uint8_t currentValue = PMIC.readPMICreg(Register::CHARGER_CHG_EOC_CNFG);
    currentValue = (currentValue & REG_CHG_EOC_CNFG_IEOC_mask);
    EndOfChargeCurrent current = static_cast<EndOfChargeCurrent>(currentValue);
    for (auto const& [key, val] : endOfChargeCurrentMap) {
        if (val == current) {
            return key;
        }
    }
    return -1;
}

bool Charger::setInputCurrentLimit(uint16_t current) {
    if(inputCurrentLimitMap.find(current) != inputCurrentLimitMap.end()) {
        InputCurrentLimit convertedCurrent = inputCurrentLimitMap[current];
        PMIC.getControl() -> setInputCurrentLimit(convertedCurrent);
        return true;
    }
    return false;
}

uint16_t Charger::getInputCurrentLimit() {
    uint8_t currentValue = PMIC.readPMICreg(Register::CHARGER_VBUS_INLIM_CNFG);
    currentValue = (currentValue & REG_VBUS_INLIM_CNFG_VBUS_LIN_INLIM_mask);
    InputCurrentLimit current = static_cast<InputCurrentLimit>(currentValue);
    for (auto const& [key, val] : inputCurrentLimitMap) {
        if (val == current) {
            return key;
        }
    }
    return -1;
}

bool Charger::isEnabled(){
    return PMIC.readPMICreg(Register::CHARGER_CHG_OPER) == 0x02;
}

bool Charger::setEnabled(bool enabled){
    if(enabled){
        PMIC.writePMICreg(Register::CHARGER_CHG_OPER, 0x02);
        return PMIC.readPMICreg(Register::CHARGER_CHG_OPER) == 0x02;
    } else {
        PMIC.writePMICreg(Register::CHARGER_CHG_OPER, 0x01);
        return PMIC.readPMICreg(Register::CHARGER_CHG_OPER) == 0x01;
    }
}

ChargingState Charger::getState(){
    uint8_t reg_val = PMIC.readPMICreg(Register::CHARGER_CHG_SNS);
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
