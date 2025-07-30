#include <Wire.h>
#include <RTClib.h>

// I2C Pins for ESP32
#define SDA_PIN 21
#define SCL_PIN 22

RTC_DS3231 rtc;

void setup() {
  Serial.begin(115200);

  // Start I2C on specified pins
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("❌ Couldn't find RTC. Check connections!");
    while (1);
  }

  // If RTC lost power, set time to compile time (optional)
  if (rtc.lostPower()) {
    Serial.println("⚠️ RTC lost power, setting time to compile time");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Uses sketch compile time
  }

  Serial.println("✅ RTC_DS3231 Initialized");
}

// Optional function to manually set RTC time
void setRTCTime(int year, int month, int day, int hour, int minute, int second) {
  rtc.adjust(DateTime(year, month, day, hour, minute, second));
  Serial.println("⏳ RTC time set manually");
}

void loop() {
  DateTime now = rtc.now();

  // Print current time and date
  Serial.printf("Time: %02d:%02d:%02d\n", now.hour(), now.minute(), now.second());
  Serial.printf("Date: %02d/%02d/%04d\n", now.day(), now.month(), now.year());
  Serial.println("----------------------------");

  delay(1000); // Update every second
}
