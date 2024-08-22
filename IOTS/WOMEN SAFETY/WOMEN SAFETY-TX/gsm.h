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
  Serial3.print("https://www.google.com/maps/");
  //  Serial.print(lat3,5);
  Serial3.print("13.0461006");
  Serial3.print(",");
  //  Serial.print(lon3,5);
  Serial3.print("80.2209664");

  delay(1000);
  Serial3.write(char(26));
  ////  lcd.setCursor(9, 1);
  ////  lcd.print("   ");  delay(1000);
}

#endif
