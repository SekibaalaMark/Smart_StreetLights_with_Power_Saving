#include <WiFi.h>
#include <RTClib.h>
#include <Wire.h>

// Pin definitions
#define LDR_PIN 36          // LDR voltage divider connected to GPIO 36 (A0)
#define LED_PIN 2           // LED connected to digital pin 2
#define SDA_PIN 21          // I2C SDA pin for RTC
#define SCL_PIN 22          // I2C SCL pin for RTC

// Create RTC object
RTC_DS3231 rtc;

// Threshold values
int dayThreshold = 800;     // Very dark threshold for daytime
int nightThreshold = 1500;  // Normal darkness threshold for nighttime

// Time settings (24-hour format)
int nightStartHour = 18;    // 6:00 PM
int nightEndHour = 6;       // 6:00 AM

void setup() {
  Serial.begin(115200);
  
  // Initialize pins
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // Initialize I2C for RTC
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  // Check if RTC lost power and if so, set the time
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting time!");
    // Set to compile time (you can modify this to set current time)
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  Serial.println("ESP32 Smart Light Control System Initialized");
  Serial.println("LED will turn on if:");
  Serial.println("1. It's nighttime (6PM-6AM) AND it's dark");
  Serial.println("2. It's extremely dark during daytime");
  Serial.println("Use potentiometer to adjust LDR sensitivity in real-time");
}

void loop() {
  // Read LDR value (potentiometer acts as variable resistor in voltage divider)
  int ldrValue = analogRead(LDR_PIN);
  
  // Get current time
  DateTime now = rtc.now();
  int currentHour = now.hour();
  
  // Determine if it's night time
  bool isNightTime = false;
  if (nightStartHour > nightEndHour) {
    // Night spans midnight (e.g., 18:00 to 06:00)
    isNightTime = (currentHour >= nightStartHour || currentHour < nightEndHour);
  } else {
    // Night doesn't span midnight
    isNightTime = (currentHour >= nightStartHour && currentHour < nightEndHour);
  }
  
  // Determine if LED should be on
  bool shouldTurnOnLED = false;
  String reason = "";
  
  if (isNightTime && ldrValue < nightThreshold) {
    shouldTurnOnLED = true;
    reason = "Night time and dark";
  } else if (!isNightTime && ldrValue < dayThreshold) {
    shouldTurnOnLED = true;
    reason = "Extremely dark during day";
  }
  
  // Control LED
  if (shouldTurnOnLED) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON - " + reason);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  
  // Print debug information
  Serial.println("=== Status ===");
  Serial.printf("Time: %02d:%02d:%02d\n", now.hour(), now.minute(), now.second());
  Serial.printf("Date: %02d/%02d/%04d\n", now.day(), now.month(), now.year());
  Serial.println("Night time: " + String(isNightTime ? "Yes" : "No"));
  Serial.println("LDR Value: " + String(ldrValue) + " (lower = darker)");
  Serial.println("Day Threshold: " + String(dayThreshold) + " (LED on if LDR < this during day)");
  Serial.println("Night Threshold: " + String(nightThreshold) + " (LED on if LDR < this during night)");
  Serial.println("LED Status: " + String(shouldTurnOnLED ? "ON" : "OFF"));
  if (shouldTurnOnLED) {
    Serial.println("Reason: " + reason);
  }
  Serial.println("Potentiometer tip: Turn clockwise to make more sensitive to light");
  Serial.println("==================");
  
  delay(5000); // Check every 5 seconds
}

// Function to manually set RTC time (call this in setup if needed)
void setRTCTime(int year, int month, int day, int hour, int minute, int second) {
  rtc.adjust(DateTime(year, month, day, hour, minute, second));
  Serial.println("RTC time set successfully");
}