#ifndef XGZP6847D_H
#define XGZP6847D_H
#include "global.h"
int K= 256;
#include "XGZP6897D.h"
XGZP6897D mysensor(K);
float pressure, temperature;
int cmh2o_function()
{
  int cmh20 = pressure * 0.010197162129779;
  

 //Serial.print(String(" pres  ") + pressure); Serial.println(String(" cmh20  ") + cmh20);
return cmh20;
}

int xgzp6894d_temperature()
{

//Serial.print(String("  temp  ") + temperature);
return temperature;
  
}
#endif
