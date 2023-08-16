#include "PowerManagement.h"


/**
 * @brief constructor for the PowerManagement 
*/
PowerManagement::PowerManagement(){
    #if defined(ARDUINO_PORTENTA_C33)
    static PF1550_IO_C33          io(&Wire3, PF1550_I2C_DEFAULT_ADDR);
    #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4)
    static PF1550_IO_Portenta_H7  io(&Wire1, PF1550_I2C_DEFAULT_ADDR);
    #elif defined(ARDUINO_NICLA_VISION)
    static PF1550_IO_Nicla_Vision io(&Wire1, PF1550_I2C_DEFAULT_ADDR);
    #else
    # error "No IO class defined for this board."
    #endif

    this-> pPMIC = new PF1550(io);
    this -> board = new Board(this-> pPMIC);
    this -> charger = new Charger(this->pPMIC);
    this -> battery = new Battery();   
}

/**
 * @brief start communication with the PMIC chip and the power gauge. 
*/
void PowerManagement::begin(){
    this -> pPMIC -> begin();
    this -> battery -> begin();
}


Board PowerManagement::getBoard() {
    return *board; // Return the dereferenced board pointer (actual Board instance)
}


Battery PowerManagement::getBattery() {
    return *battery; // Return the dereferenced battery pointer (actual Battery instance)
}

Charger PowerManagement::getCharger() {
    return *charger;
}
