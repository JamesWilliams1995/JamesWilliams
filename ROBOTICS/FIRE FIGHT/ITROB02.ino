/************************************
   CLIENT ID:M0720
   PROJECT CODE:MO720-1(ROB02)
   STATUS:
   DATE:23.03.22
   DEVELOPER NAME:SANTHOSH KUMAR

 ***********************************/
#include<LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#include <Servo.h>
Servo myservo;
#define m1 24
#define m2 26
#define m3 28
#define m4 30

#define ir1 A8
#define ir2 A9
#define ir3 5
#define ir4 6
#define pump 52

#define buz A11
int image_flag = 2;

//#include"iot.h"
//void iott(String s);

void setup() {
  Serial.begin(9600);
//  Serial1.begin(9600);//iot   
  Serial2.begin(9600);//matlab BLUTOOTH
  Serial3.begin(9600); //ZIGBEE
  lcd.begin(16, 2);
  myservo.attach(22);//servo pin
  myservo.write(0);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FIRE FIGHT");
  lcd.setCursor(0, 1);
  lcd.print("ROBOT");

  digitalWrite(pump, LOW);//pump
  digitalWrite(A11, LOW);//buz

  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);

  pinMode(pump, OUTPUT);//pump
  pinMode(A11, OUTPUT);//buz

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);

  delay(2000); myservo.write(90);
}

void loop() {

  serialEvent2();
  serialEvent3();
  //Serial.println(digitalRead(A0));
  int ir1_read = digitalRead(ir1);

  int ir2_read = digitalRead(ir2);

  int ir3_read = digitalRead(ir3);

  int ir4_read = digitalRead(ir4);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(ir1_read);
  lcd.setCursor(2, 0);
  lcd.print(ir2_read);
  lcd.setCursor(4, 0);
  lcd.print(ir3_read);
  lcd.setCursor(6, 0);
  lcd.print(ir4_read);



  if (((!ir1_read) || (!ir2_read)))
  {
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    digitalWrite(buz,HIGH);
    image_flag = 2;
    digitalWrite(A11, 1);
    //myservo.write(0);
    digitalWrite(pump, HIGH);
    for (int i = 90; i > 0; i--) {
      myservo.write(i);
      delay(100);
    }
    digitalWrite(A11, LOW);
  }

  else if (((!ir3_read) || (!ir4_read)))
  {
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    digitalWrite(buz,HIGH);
    image_flag = 2;
    digitalWrite(A11, 1);
    //myservo.write(180);
    digitalWrite(pump, HIGH);
    for (int i = 90; i < 180; i++) {
      myservo.write(i);
      delay(100);
      
    }
    digitalWrite(A11, LOW);
  }
  else
  {
    myservo.write(0);
    digitalWrite(pump, LOW);
    digitalWrite(A11, LOW);
  }
  delay(1000);
}

void serialEvent2(void) //IOT
{
  while(Serial2.available() > 0)
  {
    char c = (char)Serial2.read();
    Serial2.println(c);

    if (c == 'F')
    {
      lcd.setCursor(0, 1);
      lcd.print("forward");
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
      delay(1000);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    //  iott("*forward#");
    }
    if (c == 'L')
    {
      lcd.setCursor(0, 1);
      lcd.print("left");
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
      delay(1000);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, HIGH);
      delay(1000);
    }

    if (c == 'R')
    {
      lcd.setCursor(0, 1);
      lcd.print("right");
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
      delay(1000);
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    //  iott("*right#");
    }

    if (c == 'E')
    {
      lcd.setCursor(0, 1);
      lcd.print("reverse");
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
      delay(1000);
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, LOW);
      digitalWrite(m4, HIGH);
    //  iott("*reverse#");
    }
    if (c == 'S')
    {
      lcd.setCursor(0, 1);
      lcd.print("stop");
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
      delay(1000);
     // iott("*stop#");
    }
    if (c == 'P')
    {
      lcd.setCursor(0, 1);
      lcd.print("Pumping");
     myservo.write(90);
      digitalWrite(pump, HIGH);
      digitalWrite(A11, HIGH);
      delay(3000);
      digitalWrite(A11, LOW);
     // iott("*pump#");
    }
  }
}

void serialEvent3(void) //MATLAB
{
  while(Serial3.available() > 0)
  {
    char d = (char)Serial3.read();
    if (d == 'A')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FIRE DETECTED");
      image_flag = 1; delay(2000);
    }
    if (d == 'B')
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NO FIRE");
      image_flag = 0; delay(2000);
    }
    if (d == 'F')
    {
      lcd.setCursor(0, 1);
      lcd.print("forward zig");
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
      delay(1000);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    }
    if (d == 'L')
    {
      lcd.setCursor(0, 1);
      lcd.print("left zig");
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
      delay(1000);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, HIGH);
      delay(1000);
    }

    if (d == 'R')
    {
      lcd.setCursor(0, 1);
      lcd.print("right zig");
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
      delay(1000);
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    }

    if (d == 'E')
    {
      lcd.setCursor(0, 1);
      lcd.print("reverse zig");
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
      delay(1000);
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, LOW);
      digitalWrite(m4, HIGH);
    }
    if (d == 'S')
    {
      lcd.setCursor(0, 1);
      lcd.print("stop");
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
      delay(1000);
    }    
    if (d == 'P'||image_flag==1)
    {
      myservo.write(90);
      digitalWrite(pump, HIGH);
      digitalWrite(A11, HIGH);
      delay(3000);
      digitalWrite(A11, LOW);
      image_flag = 0;
    }
  }

}
