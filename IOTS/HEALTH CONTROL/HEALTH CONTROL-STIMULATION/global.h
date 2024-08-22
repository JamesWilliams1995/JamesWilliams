#ifndef GLOBAL_H
#define GLOBAL_H

/*********************#DEFINE VARIABLES*************************/

#define DHTPIN A0
#define DHTTYPE DHT11
#define res 2
#define HEART_SENSOR 5


void iot_send(String s);
int t;
//int r, count = 0, sum = 0;
int resp[] = {}, avg;



/****************************************************************/
/********************GLOBAL VARIABLES****************************/

/****************************************************************/

#endif
