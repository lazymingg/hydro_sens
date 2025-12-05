#include "TemperHandler.h"

TemperHandler::TemperHandler(int temper_pin) : oneWire(temper_pin), sensors(&oneWire) {
// Khởi tạo OneWire và DallasTemperature bằng pin
}

void TemperHandler::begin() {
    this->sensors.begin();
}

float TemperHandler::getTemperature() {
    this->sensors.requestTemperatures();
    // Lấy giá trị từ cảm biến đầu tiên (index 0)
    return this->sensors.getTempCByIndex(0);
}

int TemperHandler::getField() {
    return this->TEMPER_FIELD;
}