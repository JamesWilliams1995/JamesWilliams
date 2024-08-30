#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#include"rfid.h"
#include"softserial.h"
#define m1 7
#define m2 6
#define m3 5
#define m4 4
#define buz A0

//bool SCHOOL_STATUS = false;
//bool HOSPITAL_STATUS = false;
int r_id;
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
   rf.begin(9600);
  lcd.clear();

  digitalWrite(buz, LOW);
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);


  pinMode(buz, OUTPUT);//buz

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("AUTOMATIC SPEED");
  lcd.setCursor(2, 1);
  lcd.print(" CONTROL ");
  delay(3000);
  lcd.clear();
}

void loop() {

  lcd.setCursor(0, 0);
  lcd.print("Vehicle:");
  rfid();
  r_id = rfidno;
  if ((r_id == 1 || r_id == 2))
  {
    Serial.print("School Zone");
    lcd.setCursor(9, 0);
    lcd.print("SLOW   ");
    lcd.setCursor(0, 1);
    lcd.print("School Zone");
    digitalWrite(buz, HIGH);
    analogWrite(m1, 255);
    analogWrite(m2, 100);
    analogWrite(m3, 150);
    analogWrite(m4, 100);
    rfidno = 0;

  }
  else if ((r_id == 3 || r_id == 4))
  {
    lcd.setCursor(9, 0);
    lcd.print("SLOW   ");
    lcd.setCursor(0, 1);
    lcd.print("Hospital Zone");
    digitalWrite(buz, HIGH);
    analogWrite(m1, 255);
    analogWrite(m2, 100);
    analogWrite(m3, 150);
    analogWrite(m4, 100);
    rfidno = 0;
  }
}
void serialEvent()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vehicle:");
  while (Serial.available() > 0)
  {
    char inByte = (char)Serial.read();
    Serial.print(inByte);
    switch (inByte)
    {
      case 'F':
        lcd.setCursor(9, 0);
        lcd.print("FORWARD");
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
        delay(1000);
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
        digitalWrite(buz, LOW);
        break;
      case 'E':
        lcd.setCursor(9, 0);
        lcd.print("REVERSE");
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
        delay(1000);
        digitalWrite(m1, LOW);
        digitalWrite(m2, HIGH);
        digitalWrite(m3, LOW);
        digitalWrite(m4, HIGH);
        digitalWrite(buz, LOW);
        break;
      case 'R':
        lcd.setCursor(9, 0);
        lcd.print("RIGHT  ");
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);

        delay(1000);
        digitalWrite(m1, LOW);
        digitalWrite(m2, HIGH);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
        digitalWrite(buz, LOW);
        break;
      case 'L':
        lcd.setCursor(9, 0);
        lcd.print("LEFT   ");
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
        delay(1000);
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, HIGH);
        digitalWrite(buz, LOW);
        break;
      case 'S':
        lcd.setCursor(9, 0);
        lcd.print("STOP   ");
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
        digitalWrite(buz, LOW);
        break;
    }
  }
}
