#include <Arduino.h> // Even though you’re programming for ESP32, the Arduino.h header is still required in certain contexts if you’re writing raw C++ sketches or separating code into .cpp files, without using the Arduino IDE directly.

// Pin Definitions
#define PIR_PIN 15     // PIR output pin connected to GPIO 15
#define LED_PIN 2      // Onboard or external LED

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);      // PIR sensor as input
  pinMode(LED_PIN, OUTPUT);     // LED as output

  Serial.println("🚨 PIR Motion Detection Initialized (ESP32)");
}

void loop() {
  int pirState = digitalRead(PIR_PIN);  // Read PIR sensor state

  if (pirState == HIGH) {
    digitalWrite(LED_PIN, HIGH);        // Turn LED ON
    Serial.println("🔵 Motion Detected!");
  } else {
    digitalWrite(LED_PIN, LOW);         // Turn LED OFF
    Serial.println("⚪ No Motion");
  }

  delay(1000); // Check every second
}
