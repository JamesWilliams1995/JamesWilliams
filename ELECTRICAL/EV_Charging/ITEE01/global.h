#ifndef GLOBAL_H
#define GLOBAL_H
/*****************PIN DEFINITION*************/
#define D_irsensor_1 7
#define D_irsensor_2 6
#define D_relay_1 5
#define D_relay_2 4
#define D_buzzer A0
#define D_switch A2
/*******************************************/

#define Min 60
#define MAX_AMOUNT 3
#define RC_MAX_AMOUNT 9

/**********global variables**********/
enum
{
  HOME = 1,
  CARD_READ = 2,
  MOBILE_RECHARGE = 3,
  PAYMENT = 4,
  CHARGING = 5
} STATES;


volatile uint8_t present_state = HOME;
volatile uint8_t previous_state = HOME;
volatile uint8_t card_amount = 0;
volatile uint8_t user_amount = 0;
volatile uint16_t time_period = 0;
int ir_value1, ir_value2,iot_count = 0;
bool slot1,slot2=false;
int switch_value;
bool iot_flag=true;


/****************************************/

#endif
