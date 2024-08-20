#include<LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

#include "ss.h"
#define Bulb
#define Dc_fan
#define plug_ponit

const int relay1 = 2;
const int relay2 = 4;
const int relay3 = 5;

char bluetooth_data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GOGLE VOICE ASSIST");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (ss.available() > 0)
  {
    bluetooth_data = ss.read();
    Serial.println(bluetooth_data);
  }
  serialEvent();
  switch (bluetooth_data) {
    case '1':
      Serial.print("LIGHT ON");
      digitalWrite(relay1, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("light ON");
      iott("*LIGHT ON#");
      iott("@1#");
      break;
    case '2':
      Serial.print("LIGHT OFF");
      digitalWrite(relay1, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LIGHT OFF");
      iott("*LIGHT OFF#");
      iott("@0#");
      break;
    case '3':
      Serial.print("FAN ON");
      digitalWrite(relay2, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FAN ON");
      iott("*FAN ON#");
      iott("$2#");
      break;
    case '4':
      Serial.print("FAN OFF");
      digitalWrite(relay2, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FAN OFF");
      iott("*FAN OFF#");
      iott("$0#");
      break;
    case '5':
      Serial.print("PLUG BOX ON");
      digitalWrite(relay3, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PLUG BOX ON");
      iott("*PLUG BOX ON#");
      iott("^3#");
      break;
    case '6':
      Serial.print("PLUG BOX OFF");
      digitalWrite(relay3, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PLUG BOX OFF");
      iott("*PLUG BOX OFF#");
      iott("^0#");
      break;
  }
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
