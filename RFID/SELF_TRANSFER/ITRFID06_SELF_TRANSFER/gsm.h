#ifndef GSM_H
#define GSM_H

char garray[11];

void send_sms(int number, String data, String data1 );
long int ph = 0;
extern int mob[10];
char ph_c[11];
void send_sms(int number, String data, String data1)
{
  
   for (int i = 0; i < 10; i++) {
     garray[i] = mob[i]+'0';
     Serial.print(garray[i]);    
    }
    garray[10]='\0';
  Serial.println();
  Serial3.println("AT");
  delay(1000);
  Serial3.println("AT+CMGF=1");
  delay(1000);
  Serial3.println("AT+CMGS=\"+91"+String(garray)+"\"\r");
  delay(1000);
  Serial3.println(data);
  Serial3.println(data1);
  delay(200);
  Serial3.println(char(26));
}
#endif
