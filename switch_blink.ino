// blink the led on esp32 using push button
#include <Arduino.h>
#define LED_PIN 2
#define BUTTON_PIN 0
#define DEBOUNCE_DELAY 50 // milliseconds
volatile bool ledState = false;
volatile unsigned long lastDebounceTime = 0;
void IRAM_ATTR handleButtonPress() {
  unsigned long currentTime = millis();
  if (currentTime - lastDebounceTime > DEBOUNCE_DELAY) {
    ledState = !ledState; // Toggle the LED state
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    lastDebounceTime = currentTime;
  }
}
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistor
  digitalWrite(LED_PIN, LOW); // Start with LED off
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonPress, FALLING);
}
void loop() {
  // Nothing to do here, everything is handled in the interrupt
  delay(100); // Just to prevent watchdog timer reset
}
