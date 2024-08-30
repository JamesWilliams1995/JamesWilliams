#ifndef gsm_H
#define gsm_H
#include"gsm.h"

void gsm(String number, String data1)
{
  Serial.println("AT");
  delay(100);
  Serial.println("AT+CMGF=1");
  delay(100);
  Serial.println("AT+CMGS=\"+91" + String(number) + "\"\r");
  delay(100);
  Serial.println(data1);
  delay(100);
  Serial.println(char(26));
  delay(100);
}

#endif
