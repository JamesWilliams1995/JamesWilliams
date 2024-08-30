#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include"Arduino.h"

class ULTRASONIC
{
  public:  
    int trig=0;
    int echo=0;
    int dist=0;
    void begin(int trigger_pin, int echo_pin);
    int ultra(void);  
};
#endif
