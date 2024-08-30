#include"lcd.h"
#include"gsm.h"
#include<Servo.h>
#define buz A1
Servo Myservo;
int amount = 100, bamount = 0;
bool flag = true;
int s = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Myservo.attach(5);
  Myservo.write(0);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("TOLL GATE");
  lcd.setCursor(4, 1);
  lcd.print("ALERT");
  pinMode(s, INPUT_PULLUP);
  pinMode(buz, OUTPUT);//buz
  digitalWrite(buz, LOW);//buz
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int emer = digitalRead(s);
  int a = 1;
  if (emer == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("EMERGENCY VECHLE");
    Myservo.write(90);
  }
  else
  {
    Myservo.write(0);
    while (Serial.available() > 0)
    {
      char inchar = Serial.read();
      Serial.print(inchar);
      switch (inchar)
      {
        case '1' :    lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("CONNECTED");
          break;

        case '2' :     lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("NOT CONNECTED");
          break;

        case 'A' :   lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("GOES FREE");
          if ( a == 1)
          {
            Myservo.write(90);
            a = 0;
          }
          else
          {
            Myservo.write(0);
          }
          break;

        case 'B' :
          if (flag == true)
          {
            bamount = amount - 10;
            flag = false;
          }
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("AMOUNT DEBITED");
          lcd.setCursor(0, 1);
          lcd.print("BALANCE AMT:" + String(bamount));
          gsm("8189988347", "RS 10 DEBITED", "B_AMOUNT:" + String(bamount));
          digitalWrite(buz, HIGH);
          delay(1000);
          digitalWrite(buz, LOW);
          
          if (inchar != 'B') {
            break;
          }
          break;

        case 'C' :
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("VEHICLE COMMING");
          break;
      }
    }
  }
  //      if (emer == 0)
  //      {
  //        lcd.setCursor(0, 0);
  //        lcd.print("EMERGENCY VECHLE");
  //        Myservo.write(90);
  //      }
  //      else
  //      {
  //        Myservo.write(0);
  //      }

  delay(500);
}
