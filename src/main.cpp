#include <Arduino.h>
#include <BleKeyboard.h>

#define LED_POWER_INDICATOR_PIN 2
#define LED_PAIRING_INDICATOR_PIN 4
#define LED_PAIRING_BLINKING_INTERVAL_MS 500
#define BTN_SHUTTER_TRIGGER_PIN 18
#define BTN_SHUTTER_DEBOUNCE_TIME_MS 20

bool buttonState = HIGH; // HIGH BY DEFAULT, WHEN PRESSED IT BECOMES LOW BECAUSE OF INTERNAL PULL UP RESISTOR
bool bounceLastReading = HIGH; 
unsigned long buttonDebounceTime = 0;

bool pairingLedState = LOW;
unsigned long pairingLedLastToggleTime = 0;

BleKeyboard bleKeyboard("CameraS", "ESP32", 100);

void setup() {
  pinMode(LED_POWER_INDICATOR_PIN, OUTPUT);
  digitalWrite(LED_POWER_INDICATOR_PIN, HIGH);

  pinMode(LED_PAIRING_INDICATOR_PIN, OUTPUT);
  digitalWrite(LED_PAIRING_INDICATOR_PIN, LOW);

  pinMode(BTN_SHUTTER_TRIGGER_PIN, INPUT_PULLUP);

  bleKeyboard.begin();
}

void loop() {
  bool currentButtonState = digitalRead(BTN_SHUTTER_TRIGGER_PIN);

  if (currentButtonState != bounceLastReading) {
    buttonDebounceTime = millis();
  }

  if ((millis() - buttonDebounceTime) > BTN_SHUTTER_DEBOUNCE_TIME_MS) {
    if (currentButtonState != buttonState) {
      buttonState = currentButtonState;

      if (buttonState == LOW) {
        if (bleKeyboard.isConnected()) {
          bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
        }
      }
    }
  }

  if (bleKeyboard.isConnected()) {
    digitalWrite(LED_PAIRING_INDICATOR_PIN, HIGH);
  }
  else {
    if (millis() - pairingLedLastToggleTime >= LED_PAIRING_BLINKING_INTERVAL_MS) {
      pairingLedLastToggleTime = millis();
      pairingLedState = !pairingLedState;
      digitalWrite(LED_PAIRING_INDICATOR_PIN, pairingLedState);
    }
}

  bounceLastReading = currentButtonState;
}