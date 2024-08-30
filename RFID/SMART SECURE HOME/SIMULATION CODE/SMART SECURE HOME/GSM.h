#ifndef GSM_H
#define GSM_H
void send_sms(String number, String data1 );
void send_sms(String number, String data1)
{
  
  Serial.println();
  Serial2.println("AT");
  delay(1000);
  Serial2.println("AT+CMGF=1");
  delay(1000);
  Serial2.println("AT+CMGS=\"+91"+number+"\"\r");
  delay(1000);
  Serial2.println(data1);
  delay(200);
  Serial2.println(char(26));
}
#endif
