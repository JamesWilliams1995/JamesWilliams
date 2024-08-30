#ifndef GLOBAL_H
#define GLOBAL_H

#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

#include <ultrasonic.h>

Servo myservo, myservo1;
int pos = 0;

#define servo1_motor 9
#define servo2_motor 10
#define m1 7
#define m2 6
#define m3 5
#define m4 4
#define LED 3
float lat6 = 13.0461006;
float lon6 = 80.2209664;

ULTRASONIC U1;
ULTRASONIC U2;
int cm1 , cm2;

#endif
