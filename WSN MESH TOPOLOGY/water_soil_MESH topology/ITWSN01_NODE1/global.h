#ifndef GLOBAL_H
#define GLOBAL_H

/******************PIN DEFINITION*****************************/

#define D_soil_sensor D0
#define A_waterlevel_sensor A0
#define P_pump_motor D3
#define N_pump_motor D4

/*************************************************************/


/***********************GLOBAL VARIABLES*********************/

int8_t soil_value;
int water_value;
String motor = "MOTOR OFF";


#endif
