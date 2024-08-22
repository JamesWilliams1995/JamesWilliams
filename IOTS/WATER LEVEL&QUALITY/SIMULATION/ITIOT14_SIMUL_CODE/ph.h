#ifndef PH_H
#define PH_H
#include "global.h"
unsigned long int avgValue;
float b;
int buf[10], temp;

void ph_func(void);

/******************************************************************************************/
void ph_func()
{
  for (int i = 0; i < 10; i++)
  {
    buf[i] = analogRead(PH_PIN);
    delay(10);
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue=0;
  for (int i=2;i<8;i++)
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6;
  phValue = 3.5*phValue;
  Serial.print("PhValue : ");
  Serial.print(phValue);
  delay(800);
}
/*************************************************************************************************/
#endif
