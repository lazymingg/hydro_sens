#include "TDSHandler.h"

TDSHandler::TDSHandler(int tds_pin) {
    gravity_tds.setPin(tds_pin);
    gravity_tds.setAref(3.3);       // reference voltage on ADC: 5V (Arduino); 3.3V (ESP32) 
    gravity_tds.setAdcRange(4096);  // 1024 for 10-bit ADC (Arduino); 4096 for 12-bit ADC (ESP32)
    gravity_tds.begin();            // initialization
}

void TDSHandler::update(float temperature) {
    gravity_tds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravity_tds.update();
}

float TDSHandler::getValue() {
    return gravityTds.getTdsValue();
}

void TDSHandler::sendToCloud() {
    ThingSpeak.send(getValue());
}
