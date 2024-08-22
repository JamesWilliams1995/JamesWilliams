#ifndef HEART_H
#define HEART_H
#include"global.h"
#include "iot.h"

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
  iott("@" + String(G_i) + "#");
//  if (G_i > 100)
//  {
//    E_HEART_STATE = HEART_HIGH;
//  }
//  if ((G_i < 100) && (G_i > 60))
//  {
//    E_HEART_STATE = HEART_NORMAL;
//  }
//  if ((G_i < 60) && (G_i > 0))
//  {
//    E_HEART_STATE = HEART_LOW;
//  }
//  if (G_i == 0)
//  {
//    E_HEART_STATE = NO_FINGER;
//  }
}

#endif
