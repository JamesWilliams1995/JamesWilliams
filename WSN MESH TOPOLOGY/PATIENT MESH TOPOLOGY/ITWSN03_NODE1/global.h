#ifndef GLOBAL_H
#define GLOBAL_H

/******************PIN DEFINITION*****************************/

//#define D_soil_sensor D0
//#define A_waterlevel_sensor A0
//#define D_pump_motor D1
//#define temp_data D0
#define HEART_SENSOR D4

/*************************************************************/


/***********************GLOBAL VARIABLES*********************/

#include "dht11.h"
DHT dht;
//int ir_value;
//int cm ;
int temp, hum;
int G_i;

#endif
