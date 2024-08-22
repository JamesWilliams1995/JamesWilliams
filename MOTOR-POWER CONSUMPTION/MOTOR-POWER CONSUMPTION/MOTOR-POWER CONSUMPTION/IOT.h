#ifndef IOT_H
#define IOT_H




void iot_send(String data)
{
  for (int i = 0; i < data.length(); i++)
  {
    Serial.write(data[i]);
  }
  delay(3000);
}

#endif
