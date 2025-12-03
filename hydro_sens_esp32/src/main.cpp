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

// Pin
int buttonPin = 5;
int ledPin = 18 ;
bool lastButtonState = HIGH;

// put function definitions here:
// read temperature
void readTemperature() {
  if (millis() - lastUpdateTime >= postingInterval) {
    // read temperature
    sensors.requestTemperatures();
    float temperature = sensors.getTempCByIndex(0);

    // check if device is connected
    if (temperature != DEVICE_DISCONNECTED_C) {
      Serial.print("Temperature: ");
      Serial.print(temperature);

      // post data to thingspeak
      int statusCode = ThingSpeak.writeField(channelNumber, fieldTemper, temperature, writeAPIKey); 
    }
  }

  lastUpdateTime = millis();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(11250);
  sensors.begin();

  // connect wifi
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // init thingspeak
  ThingSpeak.begin(client);

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
