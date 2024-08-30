#ifndef gsm_H
#define gsm_H
#include"gps.h"
void gsm(String number, String data)
{

  Serial2.println("AT");
  delay(1000);
  Serial2.println("AT+CMGF=1");
  delay(1000);
  Serial2.println("AT+CMGS=\"+91" + String(number) + "\"\r");
  delay(1000);
  Serial2.println(data);
  Serial2.print("https://www.google.com/maps/");
  Serial2.print(lat3,5);
//  Serial.print("13.0461006");
  Serial2.print(",");
  Serial2.print(lon3,5);
//  Serial.print("80.2209664");

  delay(1000);
  Serial2.write(char(26));
  ////  lcd.setCursor(9, 1);
  ////  lcd.print("   ");  delay(1000);
}

#endif
