#ifndef GLOBAL_H
#define GLOBAL_H
#include<MPU6050.h>
#include<Wire.h>


/*********************#DEFINE VARIABLES*************************/

#define DHTPIN A0
#define DHTTYPE DHT11
#define HEART_SENSOR 5
#define buzzer 3
DHT dht(DHTPIN, DHTTYPE);

void iot_send(String s);
float t;
int G_i = 0;



/****************************************************************/
/********************GLOBAL VARIABLES****************************/

/****************************************************************/

#endif
