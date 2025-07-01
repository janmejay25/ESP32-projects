#define LED_PIN 2         // Built-in LED or external LED connected to GPIO 2
#define BUTTON_PIN 4      // Push button connected to GPIO 4

bool ledState = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool lastButtonState = HIGH;
bool buttonState;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Use internal pull-up resistor
  digitalWrite(LED_PIN, ledState);
  Serial.begin(115200);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // Reset debounce timer
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && buttonState == HIGH) {
      ledState = !ledState;  // Toggle LED
      digitalWrite(LED_PIN, ledState);
    }
    buttonState = reading;
  }

  lastButtonState = reading;
}
