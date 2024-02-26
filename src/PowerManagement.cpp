#include "PowerManagement.h"

PowerManagement::PowerManagement(){


    this->board = new Board();
    this->charger = new Charger();
    this->battery = new Battery();
}


bool PowerManagement::begin(){
    return PMIC.begin() == 0 && this->battery->begin();
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
