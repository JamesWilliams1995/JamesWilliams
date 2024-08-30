#ifndef IOT_H
#define IOT_H
#include<SoftwareSerial.h>
SoftwareSerial ss(7, 2);
int motorpos1 = 3;
int motorneg1 = 4;
int motorpos2 = 5;
int motorneg2 = 6;

void iot(){
  while (ss.available() > 0)
  {
   Serial.print("h");
    char b = ss.read();
    Serial.print(b);
    switch (b) {
      case 'F' :
        lcd.setCursor(3, 1);
        lcd.print("Forward");
        Serial.print("Forward");
        digitalWrite(motorpos1, LOW);
        digitalWrite(motorneg1, HIGH);
        digitalWrite(motorpos2, LOW);
        digitalWrite(motorneg2, HIGH);
        break;

      case 'E':
        lcd.setCursor(3, 1);
        lcd.print("backward");
        Serial.print("backward");
        digitalWrite(motorpos1, HIGH);
        digitalWrite(motorneg1, LOW);
        digitalWrite(motorpos2, HIGH);
        digitalWrite(motorneg2, LOW);
        break;

      case 'R':
        lcd.setCursor(3, 1);
        lcd.print("right");
        Serial.print("right");
        digitalWrite(motorpos1, HIGH);
        digitalWrite(motorneg1, LOW);
        digitalWrite(motorpos2, LOW);
        digitalWrite(motorneg2, LOW);
        break;

      case 'L':
        lcd.setCursor(3, 1);
        lcd.print("left");
        Serial.print("left");
        digitalWrite(motorpos1, LOW);
        digitalWrite(motorneg1, LOW);
        digitalWrite(motorpos2, HIGH);
        digitalWrite(motorneg2, LOW);
        break;

         case 'S':
        lcd.setCursor(3, 1);
        lcd.print("stop");
        Serial.print("stop");
        digitalWrite(motorpos1, LOW);
        digitalWrite(motorneg1, LOW);
        digitalWrite(motorpos2, LOW);
        digitalWrite(motorneg2, LOW);
        break;


    }
  }
}
#endif
