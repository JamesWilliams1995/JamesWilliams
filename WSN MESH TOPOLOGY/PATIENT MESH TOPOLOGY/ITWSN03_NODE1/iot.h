#ifndef IOT_H
#define IOT_H

void iot_send(String data1)
{
  for (int i = 0; i < data1.length(); i++)
  {
    Serial.write(data1[i]);
  }
  delay(1000);
}
#endif
