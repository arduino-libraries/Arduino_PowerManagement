#include "PowerManagement.h"

PowerManagement::PowerManagement(){}

bool PowerManagement::begin(){
    return PMIC.begin() == 0 && this->getBattery().begin();
}

Board PowerManagement::getBoard() {
    if (this->board == nullptr) {
        this->board = new Board();
    }
    return *board;
}

Battery PowerManagement::getBattery() {
    if (this->battery == nullptr) {
        this->battery = new Battery();
    }
    return *battery; 
}

Charger PowerManagement::getCharger() {
    if (this->charger == nullptr) {
        this->charger = new Charger();
    }
    return *charger;
}
