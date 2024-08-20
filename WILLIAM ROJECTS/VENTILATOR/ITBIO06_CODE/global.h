#ifndef GLOBAL_H
#define GLOBAL_H

/*********************#DEFINE VARIABLES*************************/
#define D_motor_p A0
#define D_motor_n A1
#define D_temp A2
#define D_buzzer 6
#define D_relay1 39
#define D_relay2 41

/****************************************************************/
/********************GLOBAL VARIABLES****************************/
int motor_n = 0, d_value_f = 0, d_value_r = 0, motor_p = 0;
float value = 57722; //0.5sec
bool G_O2_flag = false;
int TempF;
String LVL = "0", a = "00";

int resp = 0;
bool r_flag=false;
/****************************************************************/
#endif
