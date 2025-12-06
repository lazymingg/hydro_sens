#include <ThingSpeakManager.h>

ThingSpeakManager::ThingSpeakManager(WiFiClient& client) : client(client) {
    ENVReader envReader("../.env"); 

    if (loadConfig(envReader)) {
        Serial.println("Tải cấu hình ThingSpeak thành công.");
    } else {
        Serial.println("Lỗi: thiếu cấu hình ThingSpeak hoặc tải thất bại.");
    }
}

bool ThingSpeakManager::loadConfig(ENVReader& envReader) {
    if (!envReader.isLoaded()) return false;

    this->CHANNEL = envReader.get("CHANNEL").toInt();
    this->WRITE_API_KEY = envReader.get("WRITE_API_KEY");
    this->READ_API_KEY = envReader.get("READ_API_KEY");

    return !this->WRITE_API_KEY.isEmpty() && !this->READ_API_KEY.isEmpty() && this->CHANNEL > 0;
}

void ThingSpeakManager::begin(const char* ssid, const char* password) {
    // Kết nối wifi
    Serial.print("Đang kết nối WiFi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nThingSpeak WiFi đã được kết nối.");
    Serial.print("Địa chỉ IP: ");
    Serial.println(WiFi.localIP());

    // khởi tạo thingspeak
    ThingSpeak.begin(this->client);
}

int ThingSpeakManager::writeData(int field, float value) {
    int statusCode = ThingSpeak.writeField(this->CHANNEL, field, value, (this->WRITE_API_KEY).c_str());
    return statusCode;
}