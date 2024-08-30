 #ifndef HEARTRATE_H
 #define HEARTRATE_H
 #define HEART_SENSOR D4

 int G_i;
 void heart_rate()
 {
 int j = 120;
  int i = 0;
  while (j > 0)
  {
    if (digitalRead(HEART_SENSOR) == LOW)
      i++;
    j--;
    delay(14);
  }
  G_i = i;
  
  //Serial.print(G_i);
 }

 #endif
