#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <ultrasonic.h>
ULTRASONIC U1;
ULTRASONIC U2;
ULTRASONIC U3;
int cm1;
int cm2;
int cm3;

void ULTRA_SONIC1() 
{
 cm1= U1.ultra();
 Serial.println(cm1);
 delay(1000);
}

void ULTRA_SONIC2() 
{
 cm2= U2.ultra();
 Serial.println(cm2);
 delay(1000);
}

void ULTRA_SONIC3() 
{
 cm3= U3.ultra();
 Serial.println(cm3);
 delay(1000);
}
#endif
