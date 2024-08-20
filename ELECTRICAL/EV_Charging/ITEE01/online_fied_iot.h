#ifndef IOT_H
#define IOT_H
//#include "ss.h"
iot_send(String data)
{
  for (int i = 0; i < data.length(); i++)
  {
    Serial.write(data[i]);
  }
  delay(2500);
}




#endif
