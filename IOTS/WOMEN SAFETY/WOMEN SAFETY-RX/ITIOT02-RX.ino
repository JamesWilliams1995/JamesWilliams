

/********************HEADER FILES*******************************/

//#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);
#define BUZZER_PIN 5
//#define LED_PIN 12

/***************************************************************/

void setup()
{
  Serial.begin(9600);
  //  pinMode(BUZZER_PIN, OUTPUT);
//  pinMode(LED_PIN, OUTPUT);
  lcd.begin(16, 2);
//  lcd.init();
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("WOMEN SAFETY");

  Serial.println("WELCOME");
  delay(1000);
}

void loop()
{
  while (Serial.available())
  {

    char inchar = Serial.read();
    Serial.println(inchar);

    switch (inchar)
    {
      case'A':
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("EMERGENCY");
        Serial.println("EMERGENCY");
        //        digitalWrite(BUZZER_PIN, HIGH);
//        digitalWrite(LED_PIN, HIGH);
        break;

      case'B':
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Fine");
        Serial.println("Fine");
        //        digitalWrite(LED_PIN, HIGH);
        break;

      case'C':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("HEART RATE HIGH");
        lcd.setCursor(4, 1);
        lcd.print("EMERGENCY");
        Serial.println("EMERGENCY");
//        digitalWrite(LED_PIN, HIGH);
        break;

      case'D':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("HEART RATE NRML");
        Serial.println("HEAR RATE NORMAL");
//        digitalWrite(LED_PIN, LOW);
        break;

      case'E':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("HEART RATE LOW");
        Serial.println("HEART RATE LOW");
//        digitalWrite(LED_PIN, LOW);
        break;

      case'F':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PLACE FINGER");
        Serial.println("PLACE FINGER");
//        digitalWrite(LED_PIN, HIGH);
        break;

    }
  }
  delay(500);
}
