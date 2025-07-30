#include <Arduino.h>

// Pin definitions
#define LDR_PIN 34   // Analog pin connected to LDR
#define LED_PIN 2    // LED pin (can be built-in LED or external)
#define LIGHT_THRESHOLD 3000  // Adjust based on your environment

// PWM setup
const int pwmChannel = 0;
const int pwmFreq = 5000;
const int pwmResolution = 8;  // 8-bit resolution (0–255)

void setup() {
  Serial.begin(115200);

  // Initialize PWM on LED pin
  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(LED_PIN, pwmChannel);
  ledcWrite(pwmChannel, 0); // Start with LED off

  Serial.println("LDR-based Light Control Initialized");
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);  // Read LDR analog value

  Serial.println("LDR Value: " + String(ldrValue));

  if (ldrValue > LIGHT_THRESHOLD) {
    // It’s dark → turn LED ON (you can adjust brightness here)
    ledcWrite(pwmChannel, 255);  // Full brightness
    Serial.println("LED: ON");
  } else {
    // It’s bright → turn LED OFF
    ledcWrite(pwmChannel, 0);  // Turn off LED
    Serial.println("LED: OFF");
  }

  delay(2000); // Wait 2 seconds before next read
}
