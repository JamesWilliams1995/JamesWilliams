#include <Servo.h>
#include"lcd.h"
#include "keypad.h"

Servo myservo;
int pos = 0;
void PSW(void);

//String data1;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(R0, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(C0, INPUT_PULLUP);
  pinMode(C1, INPUT_PULLUP);
  pinMode(C2, INPUT_PULLUP);
  pinMode(C3, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  myservo.attach(3);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BANK LOCKER");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() )
  {
    char inchar = Serial.read();
//    Serial.println(inchar);

    switch (inchar)
    {
      case'A':

        //        Serial.println("YOUR FACE MATCHED");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FACE MATCHED");
        delay(1000);
        PSW();
//        Serial.print("PW:" + String(password));
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PASS:" + String(password));
        
        if (data == password)
        {
          //          Serial.println("UnLocked");
          digitalWrite(led, HIGH);
          lcd.setCursor(0, 1);
          lcd.print("UNLOCKED DOOR");
          delay(1000);
          for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);
          }
        }
        else
        {
          //          Serial.println("Locked");
          Serial.print('A');
          Serial.write('A');
          
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("   LOCKED   ");
          digitalWrite(led, LOW);
          for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          delay(500);
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("SENDING SMS");
        }
        break;
      case'B':
//        Serial.print("YOUR FACE NOT MATCHED");
        digitalWrite(led, LOW);
        lcd.setCursor(0, 1);
        lcd.print("FACE ! MATCH");
        break;
    }
    password = "";
    delay(500);
  }
}

void zigbee(String s)
{
  for (int i = 0; i < s.length(); i++)
  {
    Serial.write(s[i]);
  }
  delay(1000);
}
