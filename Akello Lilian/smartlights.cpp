#include <Wire.h>
#include <RTClib.h>

//define pins 
#define LED_PIN 2
#define LDR_PIN 34
#define PIR_PIN 15
#define SDA_PIN 21
#define SCL_PIN 22

//define dim period
#define DIM_PERIOD 500

//rtc object
RTC_DS3231 rtc;

//variables
int Darkness_Threshold = 1500;

int Night_hour = 18;

int Day_Hour = 6;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);

  //pin functionality
  pinMode(LED_PIN , OUTPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);

  //start I2C and RTC
  Wire.begin(21 ,22);
  rtc.begin();

  if (!rtc.begin()){
    Serial.println("RTC not connected");
    while (true);
  }

  if (rtc.lostPower()){
    Serial.println("RTC lost power");
    rtc.adjust(DateTime(__DATE__ , __TIME__));
  }

  //start with lights off
  digitalWrite(LED_PIN, LOW);
  int ldr_value = analogRead(LDR_PIN);
}


void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = rtc.now();
  int hour = now.hour();
  Serial.println("Current time is");
  Serial.println(hour);

 //read LDR and PIR values
  int ldr_value = analogRead(LDR_PIN);
  Serial.println("LDR value is ");
  Serial.println(ldr_value);

  int pir_value = digitalRead(PIR_PIN);

 //print current time, LDR and PIR values
  Serial.print("Time: ");
  Serial.print(hour);
  Serial.print(" : ");
  Serial.println(now.minute());
  Serial.print("LDR : ");
  Serial.println(ldr_value);
  Serial.print("PIR : ");
  Serial.println(pir_value);
  delay(3000);
  
 //night window logic
  if ((now.hour() >= Night_hour) || (now.hour() < Day_Hour) && (ldr_value >= Darkness_Threshold)){
      //integrating motion sensor
      if (pir_value == HIGH){
      digitalWrite(LED_PIN , HIGH);
      Serial.println("------------------");
      Serial.println("NIGHT and Dark");

  }
  else{
    digitalWrite(LED_PIN, HIGH);
    delay(DIM_PERIOD);
    digitalWrite(LED_PIN, LOW);
    delay(DIM_PERIOD);
    Serial.println("------------------");
    Serial.println("Dimming lights");
    
  }
  }

 
  //day window logic
  if ((now.hour() >= Day_Hour) && (now.hour() <  Night_hour) && (ldr_value >= Darkness_Threshold)){
    digitalWrite(LED_PIN, HIGH);
    Serial.println("------------------");
    Serial.println("DAY but Dark");
  }
   else if((now.hour() >= Day_Hour) && (now.hour() <  Night_hour) && (ldr_value <= Darkness_Threshold))
   {
    digitalWrite(LED_PIN , LOW);
    Serial.println("------------------");
    Serial.println("DAY and Bright enough");
   }

  
}

