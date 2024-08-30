#ifndef GSM_H
#define GSM_H

void gsm(String number, String data)
{

  Serial.println("AT");
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+91" + String(number) + "\"\r");
  delay(1000);
  Serial.println(data);
  Serial.print("https://www.google.com/maps/");
  //  Serial.print(lat3,5);
  Serial.print("13.0461006");
  Serial.print(",");
  //  Serial.print(lon3,5);
  Serial.print("80.2209664");

  delay(1000);
  Serial.write(char(26));
  ////  lcd.setCursor(9, 1);
  ////  lcd.print("   ");  delay(1000);
}

#endif
