#ifndef GLOBAL_H
#define GLOBAL_H
#include <Servo.h>
Servo myservo;
#define ir_sensor 5
#define servo_motor 7
#define crash 6
void isr_state();
void Init();
void Init()
{
  pinMode(ir_sensor, INPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), isr_state, RISING );
  myservo.attach(servo_motor);
  pinMode(crash, OUTPUT);
  digitalWrite(crash, HIGH);
}

#endif
