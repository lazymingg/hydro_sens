#include <Arduino.h>

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
