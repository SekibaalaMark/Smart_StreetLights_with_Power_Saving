#include <Arduino.h> //Even though you’re programming for ESP32, the Arduino.h header is still required in certain contexts if you’re writing raw C++ sketches or separating code into .cpp files, without using the Arduino IDE directly.

// LED pin (must be PWM-capable)
#define LED_PIN 2  // Built-in LED on most ESP32 boards

// PWM configuration
const int pwmChannel = 0;// the led is on channel of the PWM controller
const int pwmFreq = 500;        // 5 kHz PWM frequency
const int pwmResolution = 8;     // 8-bit resolution: 0-255 brightness

void setup() {
  Serial.begin(115200);

  // Set up PWM on LED pin
  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(LED_PIN, pwmChannel);

  Serial.println(" LED PWM Brightness Control Initialized");
}

void loop() {
  // Gradually increase brightness
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    ledcWrite(pwmChannel, brightness);
    Serial.print("Brightness ↑: ");
    Serial.println(brightness);
    delay(30);
  }

  // Gradually decrease brightness
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    ledcWrite(pwmChannel, brightness);
    Serial.print("Brightness ↓: ");
    Serial.println(brightness);
    delay(300);
  }

  delay(500);// Pause before next cycle
}
