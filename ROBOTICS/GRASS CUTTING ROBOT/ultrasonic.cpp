#include"ultrasonic.h"
void begin(int trigger_pin, int echo_pin);
int ultra(void);

void ULTRASONIC::begin(int trigPin, int echoPin)
{
  trig = trigPin;
  echo = echoPin;
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}
int ULTRASONIC::ultra()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  dist = pulseIn(echo, HIGH);
  dist = (dist / 2) / 29.1;
  return dist;  
}
