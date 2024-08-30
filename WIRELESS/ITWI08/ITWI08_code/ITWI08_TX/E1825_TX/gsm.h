#ifndef gsm_H
#define gsm_H
#include"gps.h"
void gsm(String number, String data)
{

  Serial3.println("AT");
  delay(1000);
  Serial3.println("AT+CMGF=1");
  delay(1000);
  Serial3.println("AT+CMGS=\"+91" + String(number) + "\"\r");
  delay(1000);
  Serial3.println(data);
  Serial3.print("https://www.google.com/maps/place/Panimalar+Engineering+College/@13.0489049,80.0732755,17z/data=!3m1!4b1!4m6!3m5!1s0x3a5261c68a9f3031:0xab41c8bdcf32ad47!8m2!3d13.0489049!4d80.0754642!16s%2Fm%2F03d0n7q");
  Serial3.print(lat3,5);
//  Serial.print("13.0461006");
  Serial3.print(",");
  Serial3.print(lon3,5);
//  Serial.print("80.2209664");

  delay(1000);
  Serial3.write(char(26));
  ////  lcd.setCursor(9, 1);
  ////  lcd.print("   ");  delay(1000);
}

#endif
