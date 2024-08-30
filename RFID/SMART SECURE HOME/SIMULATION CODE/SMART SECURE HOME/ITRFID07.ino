#include "global.h"
#include "RFID.h"
#include "LCD.h"
#include "GSM.h"
#include "PYH.h"
boolean flag = false;
int rfid();
void setup() {
  // put your setup code here, to run once:
  Init();
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial1.begin(9600);
  myservo.write(0);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("SMART SECURE");
  lcd.setCursor(6, 1);
  lcd.print("HOME");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

  int IR_value = digitalRead(ir_sensor);
  if (flag == true)
  {
    //flag = false;
    send_sms("8189988347" , "THEFT UR HOME     ");
    digitalWrite(crash, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("THEFT UR HOME");
    while (1);
  }
  else
  {
    lcd.clear();
    if (IR_value == 0)
    {
      lcd.setCursor(0, 0);
      lcd.print("TAP UR CARD");
      //    lcd.setCursor(0, 1);
      //    lcd.print(String(rfid()));
      if (rfid() == 1)
      {
        lcd.setCursor(0, 0);
        lcd.print("WAITING1...");
        switch (face())
        {
          case 'A' :
            myservo.write(90);
            // delay(1000);
            lcd.setCursor(0, 0);
            lcd.print("ACCESS TO ALLOW");
            break;
          case 'B' :
            //  for (int i = 90; i > 0; i++) {
            myservo.write(0);
            // }
            lcd.setCursor(0, 0);
            lcd.print("ACCESS DENIED");
            send_sms("8189988347" , "ACCESS DENIED");
            break;
        }
      }
      if (rfid() == 2)
      {
        lcd.setCursor(0, 0);
        lcd.print("WAITING2...");
        switch (face())
        {
          case 'C' :
            myservo.write(90);
            lcd.setCursor(0, 0);
            lcd.print("ACCESS TO ALLOW");
            break;
          case 'B' :
            myservo.write(0);

            lcd.setCursor(0, 0);
            lcd.print("ACCESS DENIED");
            send_sms("8189988347" , "ACCESS DENIED");
            break;
          case 'A' :
            // for (int i = 90; i > 0; i++) {
            myservo.write(0);

            lcd.setCursor(0, 0);
            lcd.print("FACEID MISMATCH");
            send_sms("8189988347" , "MISSMATCH FACEID");
            break;
        }
      }
    }

    else
    {

      lcd.setCursor(0, 0);
      lcd.print("NO PERSON DETECT");
    }
  }
  delay(1000);
}
void isr_state() {
  flag = true;
}
