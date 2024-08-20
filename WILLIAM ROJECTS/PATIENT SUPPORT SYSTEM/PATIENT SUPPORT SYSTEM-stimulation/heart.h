#ifndef HEART_H
#define HEART_H
#include "global.h"



void heart(void)
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
 
 
}

#endif
