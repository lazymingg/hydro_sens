#ifndef TEMPER_HANDLER_H
#define TEMPER_HANDLER_H

#include <OneWire.h>
#include <DallasTemperature.h>

class TemperHandler {
private:
    OneWire oneWire;
    DallasTemperature sensors;
    int TEMPER_FIELD=1;
public:
    // constructor với pin được chỉ định 
    TemperHandler(int temper_pin);

    // khởi tạo thư viện cho cảm biến
    void begin();
    // Đọc nhiệt độ từ thiết bị
    float getTemperature();
    // lấy field của dữ liệu
    int getField();
};

#endif // TEMPER_HANDLER_H