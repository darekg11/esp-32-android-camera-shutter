#include <Arduino.h>
#include <BleKeyboard.h>

#define LED_POWER_INDICATOR_PIN 2
#define LED_PAIRING_INDICATOR_PIN 4
#define BTN_SHUTTER_TRIGGER_PIN 18
#define BTN_SHUTTER_DEBOUNCE_TIME_MS 20

bool buttonState = HIGH; // HIGH BY DEFAULT, WHEN PRESSED IT BECOMES LOW BECAUSE OF INTERNAL PULL UP RESISTOR
bool bounceLastReading = HIGH; 
unsigned long buttonDebounceTime = 0;

BleKeyboard bleKeyboard("CameraS", "ESP32", 100);

void setup() {
  Serial.begin(115200);

  pinMode(LED_POWER_INDICATOR_PIN, OUTPUT);
  digitalWrite(LED_POWER_INDICATOR_PIN, HIGH);

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
        Serial.println("BUTTON PRESSED");
      }
    }
  }

  bounceLastReading = currentButtonState;
}