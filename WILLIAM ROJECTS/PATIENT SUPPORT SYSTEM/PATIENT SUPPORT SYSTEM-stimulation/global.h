#ifndef GLOBAL_H
#define GLOBAL_H
#include<MPU6050.h>
#include<Wire.h>


/*********************#DEFINE VARIABLES*************************/

#define DHTPIN A0
#define DHTTYPE DHT11
#define HEART_SENSOR 5
#define buzzer 3


void iot_send(String s);
int t;
int G_i = 0;



/****************************************************************/
/********************GLOBAL VARIABLES****************************/

/****************************************************************/

#endif
