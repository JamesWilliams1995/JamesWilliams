#include "dht11.h"
#include<LiquidCrystal.h>
#include "AC_sensor.h"
#include "voltage.h"
#include "EmonLib.h"
#include "rtc.h"
void voltag();
void ac_sensor();
void rtc();
int count = 0;

#define VOLT_CAL 168

EnergyMonitor emon1;
#define dht_pin 3
int relay1 = 2;
int relay2 = 4;
int relay3 = 5;
DHT dht;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
char bluetooth_data;
int LDR = A5;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  emon1.voltage(1, VOLT_CAL, 1.7);

  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);

  pinMode(LDR, INPUT);
  lcd.print("SMART HOME");
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);

  Serial.println("Calibrating... Ensure that no current flows through the sensor at this moment");
  sensor.calibrate();
  Serial.println("Done!");
  extern int Min_inc;
  extern int unit_count;

  //  Wire.begin();
  //  rtc.begin();
  //  rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //  rtc.setTime(9, 00, 00);    // Set the time to 12:00:00 (24hr format)
  //  rtc.setDate(12, 31, 2021);   // Set the date to January 1st, 2014
  delay(200);


}

void loop() {
  dht.dht_read(dht_pin);
  int LDR_VALUE = digitalRead(LDR);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.setCursor(2, 0);
  lcd.print(dht.temperature);

  lcd.setCursor(5, 0);
  lcd.print("L:");
  lcd.setCursor(7, 0);
  lcd.print(LDR_VALUE);
  lcd.setCursor(0, 1);
  lcd.print("F:");
  lcd.setCursor(6, 1);
  lcd.print("L:");



  if (dht.temperature > 33) {
    digitalWrite(relay2, HIGH);
    lcd.setCursor(2, 1);
    lcd.print("ON");
  }
  else
  {
    digitalWrite(relay2, LOW);
    lcd.setCursor(2, 1);
    lcd.print("OFF");
  }

  if (LDR_VALUE == 0)
  {
    digitalWrite(relay1, HIGH);
    lcd.setCursor(8, 1);
    lcd.print("ON");
    voltag();
    ac_sensor();
    lcd.setCursor(11, 1);
    lcd.print("I:" + String(I));
  }
  else
  {
    digitalWrite(relay1, LOW);
    lcd.setCursor(8, 1);
    lcd.print("OFF");
  }

  switch (bluetooth_data) {
    case '1':
      Serial.print("LIGHT ON");
      digitalWrite(relay1, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("light ON");
      count++;
      lcd.setCursor(0, 1);
      lcd.print(count);
      voltag();
      ac_sensor();
      lcd.setCursor(11, 1);
      lcd.print("I:" + String(I));
      iott("*LIGHT ON#");
      iott("@1#");
      break;
    case '2':
      Serial.print("LIGHT OFF");
      digitalWrite(relay1, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LIGHT OFF");
      count = 0;
      lcd.setCursor(0, 1);
      lcd.print(count);
      iott("*LIGHT OFF#");
      iott("@0#");
      break;
    case '3':
      Serial.print("FAN ON");
      digitalWrite(relay2, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FAN ON");
      iott("*FAN ON#");
      iott("$2#");
      break;
    case '4':
      Serial.print("FAN OFF");
      digitalWrite(relay2, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FAN OFF");
      iott("*FAN OFF#");
      iott("$0#");
      break;
    case '5':
      Serial.print("PLUG BOX ON");
      digitalWrite(relay3, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PLUG BOX ON");
      iott("*PLUG BOX ON#");
      iott("^3#");
      break;
    case '6':
      Serial.print("PLUG BOX OFF");
      digitalWrite(relay3, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PLUG BOX OFF");
      iott("*PLUG BOX OFF#");
      iott("^0#");
      break;
  }
  delay(100);
}
void iott(String data)
{
  for (int i = 0; i < data.length(); i++)
  {
    Serial.write(data[i]);
  }
  delay(3000);
}

void serialEvent()
{
  while (Serial.available() > 0)
  {
    char inchar = Serial.read();
    switch (inchar) {
      case '1':
        Serial.print("LIGHT ON IOT");
        bluetooth_data = '1';
        break;
      case '2':
        Serial.print("LIGHT ON IOT");
        bluetooth_data = '2';
        break;
      case '3':
        Serial.println("FAN ON IOT");
        bluetooth_data = '3';
        break;
      case '4':
        Serial.println("FAN OFF IOT");
        bluetooth_data = '4';
        break;
      case '5':
        bluetooth_data = '5';
        break;
      case '6':
        bluetooth_data = '6';
        break;
    }
  }
}
void voltag()
{

  emon1.calcVI(25, 1000);        // Calculate all. No.of half wavelengths (crossings), time-out

  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  if (supplyVoltage >= 100)
  {
    Serial.print("Voltage : ");
    Serial.println(supplyVoltage);
    lcd.setCursor(12, 0);
    lcd.print("V:");
    lcd.print(supplyVoltage);
  }
  else
  {
    Serial.println("Power OFF");
  }

}
