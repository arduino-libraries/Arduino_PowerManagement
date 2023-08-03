#include "Board.h"

// Constructor
Board::Board() {

}

Board::Board(PF1550 * _pPMIC) {
    this -> pPMIC = _pPMIC;
}


// Check if the board is powered through USB

void Board::begin(){
    this -> pPMIC -> begin();
}


bool Board::isUSBPowered() {

    uint8_t reg_val = this -> pPMIC ->  readPMICreg(Register::CHARGER_VBUS_SNS);
    Serial.println(reg_val);
    return false;

}

bool Board::isCharging(){

    uint8_t reg_val = this -> pPMIC ->  readPMICreg(Register::CHARGER_CHG_SNS);
    Serial.println(reg_val);
    return false;

}

bool Board::isBatteryPowered() {

    uint8_t reg_val = this -> pPMIC ->  readPMICreg(Register::CHARGER_BATT_SNS);
    Serial.println(reg_val);
    return false;

}


#if defined(ARDUINO_NICLA_VISION)
void Board::toggleCameraPower(bool on) {
        if(on){
            Serial.println("Turning cameras on");
            this -> pPMIC ->  configLDO1(Ldo1Voltage::V_2_80, true, true, false); // 2v8 -> camera, ToF sensor
            this -> pPMIC ->  configLDO2(Ldo2Voltage::V_1_80, true, true, false); // 1v8 -> CAM_IO
            this -> pPMIC ->  configLDO3(Ldo3Voltage::V_1_80, true, true, false); // 1v8 -> CAM_CORE
        } else {
            Serial.println("Turning cameras off");
            this -> pPMIC ->  configLDO1(Ldo1Voltage::V_2_80, false, false, false); // 2v8 -> camera, ToF sensor
            this -> pPMIC ->  configLDO2(Ldo2Voltage::V_1_80, false, false, false); // 1v8 -> CAM_IO
            this -> pPMIC ->  configLDO3(Ldo3Voltage::V_1_80, false, false, false); // 1v8 -> CAM_CORE
        }
}

void Board::toggleExternalPower(bool on) {
        if(on){
            this -> pPMIC ->  configSw2(Sw2Voltage::V_3_30, 
                Sw2Voltage::V_3_30,
                Sw2Voltage::V_3_30,
                Sw2CurrentLimit::I_1_5_A,
                true,             
                true,
                true);         
        } else {
               this -> pPMIC ->  configSw2(Sw2Voltage::V_3_30, 
                Sw2Voltage::V_3_30,
                Sw2Voltage::V_3_30,
                Sw2CurrentLimit::I_1_5_A,
                false,             
                false,
                false); 
        }
}

#endif


    