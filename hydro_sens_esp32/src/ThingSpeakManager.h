#ifndef THING_SPEAK_MANAGER_H
#define THING_SPEAK_MANAGER_H

#include <Arduino.h>
#include <string.h>
#include <ThingSpeak.h>
#include <WiFi.h>
#include <ENVReader.h>

class ThingSpeakManager {
private:
    WiFiClient& client;

    // Cấu hình
    String WRITE_API_KEY;
    String READ_API_KEY;
    unsigned long CHANNEL;

    // đọc cấu hình từ file môi trường
    bool loadConfig(ENVReader& envReader);
public:
    ThingSpeakManager(WiFiClient& client);

    // Khởi tạo ThingSpeak và kết nối wifi
    void begin(const char* ssid, const char* password);

    // Ghi dữ liệu vào field
    int writeData(int field, float value);
};

#endif // THING_SPEAK_MANAGER_H