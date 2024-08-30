#ifndef SENSORS_H
#define SENSORS_H

#include <ultrasonic.h>
ULTRASONIC U1;
int ir_value;
int cm ;

void FUNTION_STATE() {

  ir_value  = digitalRead(D2);
  cm = U1.ultra();
  Serial.println("NODE3 irvalue:" + String(ir_value) + "ULTRASONIC:" + String(cm));

  //gas_value  = analogRead(A0);
  //Serial.println(gas_value);


  //  Serial.println(cm);

  delay(100);

}
#endif
