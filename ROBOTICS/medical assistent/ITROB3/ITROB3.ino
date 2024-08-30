#include <Wire.h>

#include "lcd.h"
#include "rtc.h"
#include "iot.h"

//int motorpos1 = 3;
//int motorneg1 = 4;
//int motorpos2 = 5;
//int motorneg2 = 6;
int v1 = A0;
int v2 = A1;
int v3 = A2;
const int onhour = 9;
const int onmin1 = 01;
const int onmin2 = 03;
const int onmin3 = 05; 
int onsec;
int buzzer = A3;

void setup() {
  analogWrite(v1, HIGH);
  analogWrite(v2, HIGH);
  analogWrite(v3, HIGH);
//  analogWrite(buzzer,HIGH);
  // put your setup code here, to run once:
  Serial.begin(9600);//bluetooth
  ss.begin(9600);//iot
  pinMode(motorpos1, OUTPUT);
  pinMode(motorneg1, OUTPUT);
  pinMode(motorpos2, OUTPUT);
  pinMode(motorneg2, OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(v1, OUTPUT);
  pinMode(v2, OUTPUT);
  pinMode(v3, OUTPUT);
  lcd.begin(16, 2);

  rtc_begin();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("medical assistent");

  delay(2000);
}


void loop() {
  lcd.clear();

//  Serial.print("hi");
  rtc_check();
  lcd.setCursor(0, 1);
  lcd.print(Hor);
  lcd.setCursor(2, 1);
  lcd.print(':');
  lcd.setCursor(3, 1);
  lcd.print(Min);
  lcd.setCursor(5, 1);
  lcd.print(':');
  lcd.setCursor(6, 1);
  lcd.print(Sec);
  if (onhour == Hor && onmin1 == Min && onsec<10)
  {
    lcd.setCursor(0, 1);
    lcd.print("medicine 1");
    analogWrite(v1, LOW);
//    analogWrite(buzzer, LOW);
tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);
  }
  else {
    analogWrite(v1, HIGH);
//    analogWrite(buzzer, HIGH);
     noTone(buzzer);     // Stop sound...
  delay(1000);
  }

  if (onhour == Hor && onmin2 == Min && onsec<10)
  { lcd.setCursor(0, 1);
    lcd.print("medicine 2");
    analogWrite(v2, LOW);
    tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);
  }
  else {
    analogWrite(v2, HIGH);
     noTone(buzzer);     // Stop sound...
  delay(1000);
  }

  if (onhour == Hor && onmin3 == Min && onsec<10)
  {
    lcd.setCursor(0, 1);
    lcd.print("medicine 3");
    analogWrite(v3, LOW);
    tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);
  }
  else {
    analogWrite(v3, HIGH);
   noTone(buzzer);     // Stop sound...
  delay(1000);
  }

 iot();
  
//  delay(1000);
}
void serialEvent()
{while (Serial.available() > 0)
  {
       


    Serial.print("lp");
    char bt = Serial.read();
    Serial.print(bt);
    switch (bt) {
      case 'A':
        lcd.setCursor(3, 1);
        lcd.print("Forward");
        Serial.print("Forward");
        digitalWrite(motorpos1, LOW);
        digitalWrite(motorneg1, HIGH);
        digitalWrite(motorpos2, LOW);
        digitalWrite(motorneg2, HIGH);
        break;

      case 'B':
        lcd.setCursor(3, 1);
        lcd.print("backward");
        Serial.print("backward");
        digitalWrite(motorpos1, HIGH);
        digitalWrite(motorneg1, LOW);
        digitalWrite(motorpos2, HIGH);
        digitalWrite(motorneg2, LOW);
        break;

      case 'C':
        lcd.setCursor(3, 1);
        lcd.print("right");
        Serial.print("right");
        digitalWrite(motorpos1, HIGH);
        digitalWrite(motorneg1, LOW);
        digitalWrite(motorpos2, LOW);
        digitalWrite(motorneg2, LOW);
        break;

      case 'D':
        lcd.setCursor(3, 1);
        lcd.print("left");
        Serial.print("left");
        digitalWrite(motorpos1, LOW);
        digitalWrite(motorneg1, LOW);
        digitalWrite(motorpos2, HIGH);
        digitalWrite(motorneg2, LOW);
        break;
        
        case 'O':
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
