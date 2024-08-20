#include"lcd.h"
#include"dht11.h"
#include"heart.h"
#include"gsm.h"
#include"iot.h"
#include "global.h"
#include "gyro.h"
#include "ss.h"
DHT dht;
void heart(void);
void gyro(void);
void setup()
{
  Serial.begin(9600);
//  lcd.begin(16, 2);
//  pinMode(HEART_SENSOR, INPUT_PULLUP);
//  pinMode(buzzer, OUTPUT);
//  digitalWrite(buzzer, LOW);
//  lcd.clear();
//  lcd.setCursor(3, 0);
//  lcd.print("PATIENT");
//  lcd.setCursor(0, 1);
//  lcd.print("SUPPORT SYSTEM");
////  delay(1000);
//  lcd.clear();
//  Wire.begin();                      //SENSOR 1  (sensor that is placed on the shank)
//  Wire.beginTransmission(MPU1);
//  Wire.write(0x6B);
//  Wire.write(0);
//  Wire.endTransmission(true);
  
}
void loop() {
//  dht.dht_read(A0);
//  t = dht.temperature;
//  t = (t * 1.8) + 32;
//  //  Serial.println("temp:");
//  //  Serial.print(t);
////  delay(500);
//  if (t < 100)
//  {
//    Serial.print(F("TEMP:"));
//    Serial.println(t);
//    Serial.println("Body Tem Normal");
//    lcd.setCursor(0, 0);
//    lcd.print("TEM:");
//    lcd.print(t);
//    digitalWrite(buzzer, LOW);
//    iot_send("*" + String(t) + "#");
//  }
//  else
//  {
//    Serial.println(F("T-HIGH:"));
//    digitalWrite(buzzer, HIGH);
   gsm("8189988347", "BODY TEMPERATURE HIGH");
//  }
//  if (G_i < 199)
//  {
//    heart();
//    Serial.print("HEART RATE:");
//    Serial.println(G_i);
//    Serial.println("heart beat normal");
//    lcd.setCursor(6, 0);
//    lcd.print("HR:");
//    lcd.print(G_i);
//    digitalWrite(buzzer, LOW);
//    iot_send("@" + String(G_i) + "#");
//  }
//  else
//  {
//    Serial.println("Heart beat abnormal");
//    digitalWrite(buzzer, HIGH);
//    gsm("8189988347", "HEART BEAT HIGH");
//  }
////  delay(500);
//  gyro();
//  if (GYX > 40)
//  {
//    Serial.println("NEED FOOD");
////    lcd.clear();
//    lcd.setCursor(0, 11);
//    lcd.print("FOOD");
//  }
//  else if (GYX < 40)
//  {
//    Serial.println("NEED WATER5");
//    lcd.clear();
//    lcd.setCursor(0, 1);
//    lcd.print("WATER");
//  }
////  delay(1000);
//  if (GYX > 90)
//  {
//    Serial.println("NEED MADICINE");
////    lcd.clear();
//    lcd.setCursor(5, 1);
//    lcd.print("MADICINE");
//  }
//  else if (GYX < 90)
//  {
//    Serial.println("TAKE BATH");
//    lcd.clear();
//    lcd.setCursor(13, 0);
//    lcd.print("TAKE BATH");
//  }
}
