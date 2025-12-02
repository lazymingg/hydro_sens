#include <Arduino.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// --- THINGSPEAK AND WIFI SETUP ---
// wifi
const char* ssid = "";
const char* password = "";

// thingspeak
const unsigned long channelNumber = 3188907;
const char* writeAPIKey = "8L4TSEG5LE104NA5";
const char* readAPIKey = "YSKOZREQCAL1H3LP";
const int fieldTemper = 1;
const int fieldWaterLev = 2;
const int fieldTDS = 3;

const unsigned long postingInterval = 600000; // post data every 60s
unsigned long lastUpdateTime = 0;

WiFiClient client;

// --- DS18B20 SENSOR SETUP ---
const int oneWireBus = 2;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

int buttonPin = 5;
int ledPin = 18 ;
bool lastButtonState = HIGH;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(buttonPin , INPUT_PULLUP);
  pinMode(ledPin , OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
  int state = digitalRead(buttonPin);
  if(state == LOW) digitalWrite(ledPin, HIGH);
  if(state == HIGH) digitalWrite(ledPin, LOW);

}
