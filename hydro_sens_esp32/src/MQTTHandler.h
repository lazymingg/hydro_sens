#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ENVReader.h>

class MQTTHandler {
private:
    WiFiClient espClient;
    PubSubClient client;

    // cấu hình MQTT
    String MQTT_SERVER;
    String MQTT_CLIENT_ID;
    int MQTT_PORT;
    String TEMP_TOPIC;
    String TDS_TOPIC;

    // kết nối lại MQTT
    void reconnect();

    // đọc cấu hình từ file môi trường
    bool loadConfig(ENVReader& envReader);
public:
    MQTTHandler();

    // khởi tạo và kết nối MQTT
    void begin(const char* ssid, const char* password);
    // duy trì kết nối MQTT (cần gọi trong loop)
    void handleClient();

    // gửi dữ liệu
    bool publishTemperature(float temperature);
    bool publishTDS(float tds);
};

#endif // MQTT_HANDLER_H