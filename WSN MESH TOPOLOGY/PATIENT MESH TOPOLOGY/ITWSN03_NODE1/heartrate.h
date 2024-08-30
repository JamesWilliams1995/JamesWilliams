 #ifndef HEARTRATE_H
 #define HEARTRATE_H

 
 void Heart_Rate()
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
