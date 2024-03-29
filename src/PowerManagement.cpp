#include "PowerManagement.h"


PowerManagement::PowerManagement(){}

PowerManagement::~PowerManagement(){
    if (this->battery != nullptr) {
        delete this->battery;
    }
    if (this->board != nullptr) {
        delete this->board;
    }
    if (this->charger != nullptr) {
        delete this->charger;
    }
}

bool PowerManagement::begin(){
    return PMIC.begin() == 0;
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
