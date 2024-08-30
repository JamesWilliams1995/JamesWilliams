/***************************************************************
  TITLE :ITROB04 - GRASS CUTTING ROBOT
****************************************************************/

/********************HEADER FILES*******************************/
#include"global.h"
#include"lcd.h"
#include"cutter.h"
#include"motor.h"

//#include"ultrasonic.h"
//ULTRASONIC ultra;
/***************************************************************/

/**********************FUNCTION DECLRATION**********************/
void F_cutter_state(void);
void F_motor_state(void);
void  bluetooth(void);
int i;
//void  distance_LCD(void);
/****************************************************************/
void setup()
{
  Serial.begin(9600);

  E_CUTTER_STATE = CUTTER_OFF;
  E_MOTOR_STATE = M_OFF;
  lcd.begin(16, 2);
//  ultra.begin(A0, A1);
  pinMode(motor1_positive, OUTPUT);
  pinMode(motor1_negative, OUTPUT);
  pinMode(motor2_positive, OUTPUT);
  pinMode(motor2_negative, OUTPUT);
  pinMode(cutter_positive, OUTPUT);
  pinMode(cutter_negative, OUTPUT);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("GRASS CUTTING");
  lcd.setCursor(5, 1);
  lcd.print("ROBOT");
  delay(2000);
  lcd.clear();
}

void loop()
{
  i=0;
  lcd.setCursor(0,0);
  lcd.print("ROBOT STATUS");
  lcd.setCursor(0,1);
  lcd.print("RB:");
  lcd.setCursor(9,1);
  lcd.print("CT:");
  F_cutter_state();
  F_motor_state();
  bluetooth();

//  distance_LCD();
  delay(1000);
}

void  bluetooth(void)
{
  
    if(Serial.available() > 0)
    {
      Incoming_value = (char)Serial.read();
      val=Incoming_value; 
      //Serial.print(Incoming_value);
    }
  switch (val)
  {
    case '1':
      E_MOTOR_STATE = M_OFF;
      delay(1000);
      E_MOTOR_STATE = FORWARD;
      lcd.setCursor(3,1);
      lcd.print("FWD");
      break;
    case '2':     
      E_MOTOR_STATE = M_OFF;
      delay(1000);
      E_MOTOR_STATE = REVERSE;
      lcd.setCursor(3,1);
      lcd.print("RVS");
      break;
    case '3':    
      E_MOTOR_STATE = M_OFF;
      delay(1000);
      E_MOTOR_STATE = LEFT;
      lcd.setCursor(3,1);
      lcd.print("LfT");
      break;
    case '4':     
      E_MOTOR_STATE = M_OFF;
      delay(1000);
      E_MOTOR_STATE = RIGHT;
      lcd.setCursor(3,1);
      lcd.print("RyT");
      break;
    case '5':
      E_MOTOR_STATE = M_OFF;
      lcd.setCursor(3,1);
      lcd.print("OFF");
      break;
    case '6':
      E_CUTTER_STATE = CUTTER_OFF;
      delay(1000);
      E_CUTTER_STATE = CUTTER_CW;
      lcd.setCursor(12,1);
      lcd.print("FWD");
      break;
    case '7':
      E_CUTTER_STATE = CUTTER_OFF;
      delay(1000);
      E_CUTTER_STATE = CUTTER_ACW;
      lcd.setCursor(12,1);
      lcd.print("FVS");
      break;
    case '8':
      E_CUTTER_STATE = CUTTER_OFF;
      lcd.setCursor(12,1);
      lcd.print("OFF");
      break;
  }
  
}

//void  distance_LCD(void)
//{
//  lcd.clear();
//  lcd.setCursor (11, 0);
//  lcd.print("D:");
//  lcd.print(cm);
//  cm = ultra.ultra();
//  if (cm <= 30)
//  {
//    E_MOTOR_STATE = M_OFF;
//    E_CUTTER_STATE = CUTTER_OFF;
//    lcd.setCursor(0, 0);
//    lcd.print("OBSTACLE");
//    lcd.setCursor(0, 1);
//    lcd.print("M_OFF");
//    lcd.setCursor(11, 1);
//    lcd.print("C_OFF");
//  }
//  else
//  {
//    sprintf(G_array, "%-16s", G_motor_names[E_MOTOR_STATE]);
//    lcd.setCursor(0, 0);
//    lcd.print(G_array);
//    lcd.setCursor (11, 0);
//    lcd.print("D:");
//    lcd.print(cm);
//    sprintf(G_array, "%-16s", G_cutter_names[E_CUTTER_STATE]);
//    lcd.setCursor(0, 1);
//    lcd.print(G_array);
//  }
//}
