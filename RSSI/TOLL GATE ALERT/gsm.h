#ifndef gsm_H
#define gsm_H
void gsm();
void gsm(String number,String s,String msg)
{
  Serial.print("aa");
  Serial.println("AT");
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+91"+String(number)+"\"\r");
  delay(1000);
  Serial.println(s);
  delay(1000);
  Serial.println(msg);
  delay(1000);
  Serial.write(char(26));
  delay(1000);
}
#endif
