#ifndef GLOBAL_H
#define GLOBAL_H

/*********************#DEFINE VARIABLES*************************/
#define motor1_positive 7
#define motor1_negative 6
#define motor2_positive 5
#define motor2_negative 4
#define cutter_positive 3
#define cutter_negative 2
//#define trigPin A0
//#define echoPin A1

/****************************************************************/
/********************GLOBAL VARIABLES****************************/
int cm;
const char G_motor_names[5][17] = {"FORWARD", "REVERSE", "RIGHT", "LEFT", "M_OFF"};
const char G_cutter_names[5][17] = {"CUTTER_CW", "CUTTER_ACW", "CUTTER_OFF"};
char G_array[17] = {};
long duration;
char Incoming_value,val;
char voice[25];
String v_val;
enum
{
  FORWARD = 0,
  REVERSE = 1,
  LEFT = 2,
  RIGHT = 3,
  M_OFF = 4
} E_MOTOR_STATE;
enum
{
  CUTTER_CW = 0,
  CUTTER_ACW = 1,
  CUTTER_OFF = 2
} E_CUTTER_STATE;

/****************************************************************/

#endif
