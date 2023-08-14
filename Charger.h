#include <Arduino_PMIC.h>
#include "wireUtils.h"

typedef VFastCharge ChargeVoltage;
typedef IFastCharge ChargeCurrent;
typedef IEndOfCharge EndOfChargeCurrent;
typedef IInputCurrentLimit MaxInputCurrent;

enum ChargeStatus {
    NONE = -1,
    PRECHARGE = 0,
    FAST_CHARGE_CC = 1,
    FAST_CHARGE_CV  = 2,
    END_OF_CHARGE = 3,
    DONE = 4,
    TIMER_FAULT = 6,
    THERMISTOR_SUSPEND = 7,
    OFF = 8,
    BATTERY_OVERVOLTAGE = 9,
    LINEAR_ONLY= 12
};

class Charger {
    public:
        Charger();
        Charger(PF1550 * _pPMIC);
        void setChargeCurrent(ChargeCurrent i);
        void setChargeVoltage(ChargeVoltage v);
        void setEndOfChargeCurrent(EndOfChargeCurrent i);
        void setMaxInputCurrent(MaxInputCurrent i);
        ChargeStatus getChargeStatus();
        bool enableCharger();
        bool disableCharger();
    private:
        PF1550 *pPMIC;
};