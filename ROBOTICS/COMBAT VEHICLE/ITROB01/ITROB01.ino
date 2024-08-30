#include "global.h"
#include "gps.h"
//#include "iot.h"

void iot(String s);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("COMBAT VEHICLE");
  myservo.attach(9);
  myservo1.attach(10);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
  U1.begin(A0, A1); //triger ,echo
  U2.begin(A2, A3); //triger ,echo
  myservo.write(0);
  myservo1.write(0);
  delay(1500);

}

void loop() {
  // put your main code here, to run repeatedly:

  cm1 = U1.ultra();
  cm2 = U2.ultra();
  Serial.print("  OBSTACLE :");
  Serial.println(cm1);
  Serial.print("ENEMY :");
  Serial.print(cm2);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("E_DIS :");
  lcd.print(String(cm2));

  if (cm1 < 20)
  {
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    myservo1.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    myservo1.write(pos);
    delay(15);
  }

  while (Serial.available() > 0)
  {
    char inchar = (char) Serial.read();
    Serial.print(inchar);

    switch (inchar)
    {
      case 'A': //enemy
        Serial.print("enemy");
        digitalWrite(LED, HIGH);
        digitalWrite(m1, LOW);
        digitalWrite(m2, LOW);
        digitalWrite(m3, LOW);
        digitalWrite(m4, LOW);
        lcd.setCursor(0, 0);
        lcd.print("ENEMY DETECT");
        iot("*" + String(lat6) + ',' + String(lon6) + "#");
        break;

      case 'B':
        Serial.print("Bye");
        digitalWrite(LED, LOW );
        digitalWrite(m1, HIGH);
        digitalWrite(m2, LOW);
        digitalWrite(m3, HIGH);
        digitalWrite(m4, LOW);
        break;
    }
  }
}

void serialEvent(void) //IOT
{
  while (Serial1.available() > 0)
  {
    char c = (char)Serial1.read();
    Serial1.print(c);

    if (c == 'F')
    {
      Serial1.println("forward");
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    }
    if (c == 'L')
    {
      Serial1.println("left");
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, HIGH);
    }

    if (c == 'R')
    {
      Serial1.println("right");
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    }

    if (c == 'E')
    {
      Serial1.println("reverse");
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, LOW);
      digitalWrite(m4, HIGH);
    }
    if (c == 'S')
    {
      Serial1.println("stop");
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
    }
  }
  delay(100);
}

void serialEvent1(void) //ZIGBEE
{
  while (Serial3.available() > 0)
  {
    char c = (char)Serial3.read();
    Serial3.print(c);

    if (c == 'F')
    {
      //      Serial2.println("forward");
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    }
    if (c == 'L')
    {
      //      Serial2.println("left");
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, HIGH);
    }

    if (c == 'R')
    {
      //      Serial2.println("right");
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    }

    if (c == 'E')
    {
      //      Serial2.println("reverse");
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, LOW);
      digitalWrite(m4, HIGH);
    }
    if (c == 'S')
    {
      //      Serial2.println("stop");
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
    }
  }
  delay(100);
}

void iot(String s)
{
  for (int i = 0; i < s.length(); i++)
  {
    Serial1.write(s[i]);
  }
  delay(100);
}
