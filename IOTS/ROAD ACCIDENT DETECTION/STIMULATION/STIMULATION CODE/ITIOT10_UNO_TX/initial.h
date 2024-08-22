#ifndef INITIAL_H
#define INITIAL_H

#include"dht11.h"
DHT dht;
#include <LiquidCrystal.h>
LiquidCrystal lcd (13, 12, 11, 10, 9, 8);
#define VIBRATION 3
#define DHTPIN 4
#define IRSENSOR 2
#define MOTOR_PLUSE 5
#define MOTOR_MINUS 6
void VIB_SENSOR();
boolean flag1 =false;
float value = 0;
float rev = 0;
int rpm;
int t;
int oldtime = 0;
int ttime;
void isr() //interrupt service routine
{
  rev++;
}

#endif
