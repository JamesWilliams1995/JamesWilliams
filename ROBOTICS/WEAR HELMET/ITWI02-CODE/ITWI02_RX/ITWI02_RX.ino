#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
#include"gsm.h"
//#include "fingerenroll.h" 
#include "fingermatch.h"
/************PIN CONFIGURATION***************/
#define motor_positive 4
#define motor_negative 5

void gsm(String number, String data);
String data = "";
int f_id = 0;

//extern volatile char key_value;
//uint8_t getFingerprintID();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial.println("WELCOME");
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("    WELCOME    ");
  pinMode(motor_positive, OUTPUT);
  pinMode(motor_negative, OUTPUT);
  analogWrite(motor_positive, 0);
  analogWrite(motor_negative, 0);
//  finger_init();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  //  Serial.print(getFingerprintID());
  //  delay(1000);
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("place finger");
//  do {
//    getFingerprintID();
//    if (p == FINGERPRINT_NOTFOUND)
//    {
//      lcd.clear();
//      lcd.setCursor(0, 0);
//      lcd.print("UN AUTHORIZED");
////      Serial.print("UN AUTHORIZED");
//      analogWrite(motor_positive, 0);
//      analogWrite(motor_negative, 0);
//      //    key_value = 'x';
//    }
//  }

//  while (f_id == 0);
//  //  Serial.print("vanakam");
//  if (f_id == 1)
//  {
//    lcd.clear();
//    lcd.setCursor(0, 0);
////    Serial.print("FINGER MATCHED");
//    lcd.print("FINGER MATCHED");
//    delay(2000);
//    //    key_value = 'x';
    if (Serial.available() > 0)
    {
      char inchar = Serial.read();
      Serial.println(inchar);

      switch (inchar)
      {
        case'U':
          analogWrite(motor_positive, 0);
          analogWrite(motor_negative, 0);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("  WEAR HELMET  ");
//          Serial.println("WEAR HELMET");
          break;

        case'W':
          analogWrite(motor_positive, 100);
          analogWrite(motor_negative, 0);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("    ALCHOHOL    ");
//          Serial.println("ALCHOHOL CONSUMED");
          gsm("8189988347", "ALCHOHOL CONSUMED");
          break;

        case'X':
          analogWrite(motor_positive, 100);
          analogWrite(motor_negative, 0);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("DON'T SPEAK CALL");
//          Serial.println("DON'T SPEAK CALL");
          break;

        case'Y':
          analogWrite(motor_positive, 100);
          analogWrite(motor_negative, 0);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("    ALCHOHOL    ");
          lcd.setCursor(0, 1);
          lcd.print("DON'T SPEAK CALL");
//          Serial.println("ALCHOHOL CONSUMED AND DON'T SPEAK CALL");

        case'Z':
          analogWrite(motor_positive, 100);
          analogWrite(motor_negative, 0);
          lcd.clear();
          lcd.setCursor(1, 1);
          lcd.print("   ACCIDENT   ");
          gsm("8189988347", "EMERGENCY");
//          Serial.println("ACCIDENT OCCURED");
          break;

        case'F':
          analogWrite(motor_positive, 255);
          analogWrite(motor_negative, 0);
          lcd.clear();
          lcd.setCursor(1, 1);
          lcd.print("HAPPY JOURNEY");
//          Serial.println("HAPPY JOURNEY MAKKA");
          break;
      }
    }
  }
//  delay(1000);
//}
