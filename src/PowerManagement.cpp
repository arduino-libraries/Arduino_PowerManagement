#include "PowerManagement.h"

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

    this->pmic = new PF1550(io);
    this->board = new Board(this->pmic);
    this->charger = new Charger(this->pmic);
    this->battery = new Battery();
}

 PowerManagement::~PowerManagement(){
    delete this->pmic;
    delete this->board;
    delete this->charger;
    delete this->battery;
}

bool PowerManagement::begin(){
    return this->pmic->begin() == 0 && this->battery->begin();
}

Board PowerManagement::getBoard() {
    return *board;
}

Battery PowerManagement::getBattery() {
    return *battery; 
}

Charger PowerManagement::getCharger() {
    return *charger;
}
