#include <Arduino.h>

#define LED_POWER_INDICATOR_PIN 2
#define LED_PAIRING_INDICATOR_PIN 4

void setup() {
  pinMode(LED_POWER_INDICATOR_PIN, OUTPUT);
  digitalWrite(LED_POWER_INDICATOR_PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
}