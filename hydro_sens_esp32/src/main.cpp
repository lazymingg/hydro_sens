#include <Arduino.h>
#include <WiFi.h>
#include "ThingSpeakManager.h"
#include "TemperHandler.h"
#include "TDSHandler.h"
#include "ENVReader.h"

const unsigned long POSTING_INTERVAL = 60000; 
unsigned long lastUpdateTime = 0;
bool lastButtonState = HIGH;

// wifi config
const char* ssid = "";
const char* password = "";

// PIN
int buttonPin = 5;
int ledPin = 18 ;
int temperPin = 2;
int tdsPin = 34;


// Khai báo các đối tượng
WiFiClient client;
ThingSpeakManager *tsManager = nullptr;
TemperHandler *temperHandler = nullptr;
TDSHandler *tdsHandler = nullptr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(buttonPin , INPUT_PULLUP);
  pinMode(ledPin , OUTPUT);

  // khởi tạo các đối tượng
  tsManager = new ThingSpeakManager(client);
  temperHandler = new TemperHandler(temperPin);
  tdsHandler = new TDSHandler(tdsPin);

  tsManager->begin(ssid, password);
  temperHandler->begin();
  tdsHandler->begin();

  if (WiFi.status() == !WL_CONNECTED) {
    Serial.println("Kết nối Wifi thất bại!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int state = digitalRead(buttonPin);
  if(state == LOW) digitalWrite(ledPin, HIGH);
  if(state == HIGH) digitalWrite(ledPin, LOW);
  
  delay(10); // this speeds up the simulation
}