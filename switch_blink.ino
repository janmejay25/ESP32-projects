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



// ✅ 1. Connect ESP32 to Breadboard
// Place the ESP32 on the left side of the breadboard, straddling the central groove so each row is accessible.

// ✅ 2. Connect Ground (GND)
// Use a red jumper wire from ESP32 GND pin to the blue rail of the breadboard (this will be your GND bus).

// Use black wires from the GND rail to:

// One leg of the push button

// The short leg (cathode) of the LED

// ✅ 3. Connect the Push Button
// Place the push button across the groove so each leg is on a different side of the breadboard.

// Connect:

// One leg of the button → GND rail

// Opposite leg of the button → GPIO 4 (D4) on ESP32 (use green jumper wire)

// ✅ 4. Connect the LED with Resistor
// Place the LED on the breadboard:

// Long leg (anode) → free row (not connected to GND rail)

// Short leg (cathode) → GND rail

// Connect:

// A 220Ω resistor from the anode row of the LED to another row

// A jumper wire from that resistor-connected row → GPIO 2 on ESP32 (use orange jumper wire)

// ✅ 5. Power the ESP32
// Use a USB cable to power your ESP32 from your PC or power source.