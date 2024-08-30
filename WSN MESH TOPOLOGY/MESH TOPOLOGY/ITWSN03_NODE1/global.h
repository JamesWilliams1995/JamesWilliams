#ifndef GLOBAL_H
#define GLOBAL_H

/******************PIN DEFINITION*****************************/

//#define D_soil_sensor D0
#define A_waterlevel_sensor A0
#define D_pump_motor D1

/*************************************************************/


/***********************GLOBAL VARIABLES*********************/

#include <ultrasonic.h>
ULTRASONIC U1;
int ir_value;
int cm ;

#endif
