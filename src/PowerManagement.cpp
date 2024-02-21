#include "PowerManagement.h"

PowerManagement::PowerManagement(){


    this->board = new Board();
    this->charger = new Charger();
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
