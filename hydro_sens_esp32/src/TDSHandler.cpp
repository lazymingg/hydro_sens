#include <TDSHandler.h>

TDSHandler::TDSHandler(int TDS_pin) {
    gravity_tds.setPin(TDS_pin);
    gravity_tds.setAref(3.3);       // reference voltage on ADC: 5V (Arduino); 3.3V (ESP32) 
    gravity_tds.setAdcRange(4096);  // 1024 for 10-bit ADC (Arduino); 4096 for 12-bit ADC (ESP32)
}

void TDSHandler::begin() {
    gravity_tds.begin();
}

void TDSHandler::update(int temperature) {
    gravity_tds.setTemperature(temperature);
    gravity_tds.update();
}

float TDSHandler::getTDS() {
    return gravity_tds.getTdsValue();
}

int TDSHandler::getField() {
    return this->TDS_FIELD;
}