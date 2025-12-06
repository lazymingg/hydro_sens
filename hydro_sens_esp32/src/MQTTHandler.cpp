#include <MQTTHandler.h>

MQTTHandler::MQTTHandler() : client(espClient) {
    ENVReader envReader("../.env");

    if (loadConfig(envReader)) {
        Serial.println("Tải cấu hình MQTT thành công.");
        // Gán server và port cho client ngay sau khi đọc config
        this->client.setServer(this->MQTT_SERVER.c_str(), this->MQTT_PORT);
    } else {
        Serial.println("Lỗi: thiếu cấu hình MQTT hoặc tải thất bại.");
    }
}


bool MQTTHandler::loadConfig(ENVReader& envReader) {
    if (!envReader.isLoaded()) return false;

    // Đọc các giá trị
    this->MQTT_SERVER = envReader.get("MQTT_SERVER");
    this->MQTT_PORT = envReader.get("MQTT_PORT").toInt(); 
    this->MQTT_CLIENT_ID = envReader.get("MQTT_CLIENT_ID");
    this->TEMP_TOPIC = envReader.get("TEMP_TOPIC");
    this->TDS_TOPIC = envReader.get("TDS_TOPIC");
    
    return !this->MQTT_SERVER.isEmpty() && this->MQTT_PORT > 0;
}

void MQTTHandler::reconnect() {
    // Vòng lặp cho đến khi kết nối thành công
    while (!client.connected()) {
        Serial.print("Kế nối MQTT ...");
        // Cố gắng kết nối
        if (client.connect(this->MQTT_CLIENT_ID.c_str())) {
            Serial.println("Đã kết nối");
        } else {
            Serial.print("Thất bại, rc=");
            Serial.print(client.state());
            Serial.println("Thử lại sau 5 giây");
            // Chờ 5 giây trước khi thử lại
            delay(5000);
        }
    }
}

void MQTTHandler::handleClient() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop(); // Xử lý các tác vụ MQTT nền
}

void MQTTHandler::begin(const char* ssid, const char* password) {
    // Kết nối wifi
    Serial.print("Đang kết nối WiFi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nMQTT WiFi đã được kết nối.");
    Serial.print("Địa chỉ IP: ");
    Serial.println(WiFi.localIP());
}

bool MQTTHandler::publishTemperature(float temperature) {
    if (!client.connected()) return false;

    // Chuyển đổi float sang chuỗi
    char payload[10];
    sprintf(payload, "%.2f", temperature); // Format 2 chữ số thập phân

    Serial.print("Publish TEMP tới ");
    Serial.print(this->TEMP_TOPIC.c_str());
    Serial.print(": ");
    Serial.println(payload);

    return client.publish(this->TEMP_TOPIC.c_str(), payload);
}

bool MQTTHandler::publishTDS(float tds) {
    if (!client.connected()) return false;

    char payload[10];
    sprintf(payload, "%.2f", tds); // Format 2 chữ số thập phân

    Serial.print("Publish TDS tới ");
    Serial.print(this->TDS_TOPIC.c_str());
    Serial.print(": ");
    Serial.println(payload);
    
    return client.publish(this->TDS_TOPIC.c_str(), payload);
}