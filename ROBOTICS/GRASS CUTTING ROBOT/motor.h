#ifndef MOTOR_H
#define MOTOR_H
#include"global.h"
void F_motor_state(void)
{
  switch (E_MOTOR_STATE)
  {
    case FORWARD:
      digitalWrite(motor1_positive, HIGH);
      digitalWrite(motor1_negative, LOW);
      digitalWrite(motor2_positive, HIGH);
      digitalWrite(motor2_negative, LOW);
        //Serial.print("Hello");
        
      break;
    case REVERSE:
      digitalWrite(motor1_positive, LOW);
      digitalWrite(motor1_negative, HIGH);
      digitalWrite(motor2_positive, LOW);
      digitalWrite(motor2_negative, HIGH);
      break;
    case LEFT:
      digitalWrite(motor1_positive, HIGH);
      digitalWrite(motor1_negative, LOW);
      digitalWrite(motor2_positive, LOW);
      digitalWrite(motor2_negative, HIGH);
      break;
    case RIGHT:
      digitalWrite(motor1_positive, LOW);
      digitalWrite(motor1_negative, HIGH);
      digitalWrite(motor2_positive, HIGH);
      digitalWrite(motor2_negative, LOW);
      break;
    case M_OFF:
      digitalWrite(motor1_positive, LOW);
      digitalWrite(motor1_negative, LOW);
      digitalWrite(motor2_positive, LOW);
      digitalWrite(motor2_negative, LOW);
      break;
  }
}
#endif
