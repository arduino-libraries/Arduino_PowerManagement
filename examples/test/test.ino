#include "r_lpm.h"
#include "PowerManagement.h"


lpm_instance_ctrl_t p_api_ctrl;
lpm_cfg_t p_cfg;

#define WAKE_PIN A3
#define SLEEP_PIN 0



bool doSleep = false;
bool ledState = false;

PowerManagement manager;
Board board; 

void toggleLed(uint8_t led, int n, int sleep){
  for (int i=0;i<n;i++){
    if(ledState){
        digitalWrite(led, LOW);
    } else {
        digitalWrite(led, HIGH);
    }

    delay(sleep);
    ledState = !ledState;
  }

   digitalWrite(led, HIGH);
}

void pmicStuff(){

  //PMIC.configLDO1(Ldo1Voltage::V_3_30, false, false, false);
  //PMIC.configLDO2(Ldo2Voltage::V_3_30, false, false, false);
  PMIC.configLDO3(Ldo3Voltage::V_1_20, state, state, state);
  PMIC.configSw1(Sw1Voltage::V_3_30, Sw1Voltage::V_3_30, Sw1Voltage::V_3_30, Sw1CurrentLimit::I_1_5_A, state, state, state);
  PMIC.configSw1(Sw2Voltage::V_3_30, Sw2Voltage::V_3_30, Sw2Voltage::V_3_30, Sw1CurrentLimit::I_1_5_A, state, state, state);

}

void setup() {
    Serial.begin(115200);
    while(!Serial);
    p_cfg.low_power_mode = LPM_MODE_DEEP;
    p_cfg.standby_wake_sources = LPM_STANDBY_WAKE_SOURCE_IRQ8;
    p_cfg.deep_standby_cancel_source =  LPM_DEEP_STANDBY_CANCEL_SOURCE_IRQ8_RISING;
   // p_cfg.dtc_state_in_snooze = LPM_SNOOZE_DTC_DISABLE; // LPM_SNOOZE_DTC_ENABLE LPM_SNOOZE_DTC_DISABLE
    p_cfg.power_supply_state = LPM_POWER_SUPPLY_DEEP_STANDBY_MODE1; // LPM_POWER_SUPPLY_DEEPCUT0, LPM_POWER_SUPPLY_DEEPCUT1, LPM_POWER_SUPPLY_DEEPCUT3
    p_cfg.output_port_enable = LPM_OUTPUT_PORT_ENABLE_HIGH_IMPEDANCE; // LPM_OUTPUT_PORT_ENABLE_RETAIN LPM_OUTPUT_PORT_ENABLE_HIGH_IMPEDANCE
    p_cfg.io_port_state = LPM_IO_PORT_RESET;  // LPM_IO_PORT_NO_CHANGE LPM_IO_PORT_RESET
    p_cfg.lpm_ldo_standby_

    R_LPM_Open(&p_api_ctrl, &p_cfg);

    pinMode(LEDB, OUTPUT);
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);

    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDB, HIGH);
    digitalWrite(LEDG, HIGH);


    attachInterrupt(digitalPinToInterrupt(WAKE_PIN), wake, RISING);
    attachInterrupt(digitalPinToInterrupt(SLEEP_PIN), sleep, RISING);

    manager.begin();
    board = manager.getBoard();
    board.setCommunicationSwitch(true);
    delay(10);
}



void sleep(){
    doSleep = true;
}

void wake(){
  Serial.println("AWAKE");
}



void loop() {
  if(doSleep){
        toggleLed(LEDR, 5, 100);
        digitalWrite(LEDR, HIGH );
        digitalWrite(LEDB, HIGH);
        digitalWrite(LEDG, HIGH); 
        board.setCommunicationSwitch(false);
        R_LPM_LowPowerModeEnter(&p_api_ctrl);
        doSleep = false;
  }

  toggleLed(LEDB, 1, 500);
}
