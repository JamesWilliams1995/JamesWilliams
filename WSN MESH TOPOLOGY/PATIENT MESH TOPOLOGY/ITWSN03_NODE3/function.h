#ifndef SENSORS_H
#define SENSORS_H

//#define temp_pin D3
//#include <ultrasonic.h>
//ULTRASONIC U1;
//int ir_value;
//int cm ;
#include "dht11.h"
DHT dht;
int temp,hum;

void FUNTION_STATE() {

//  ir_value  = digitalRead(D2);
//  cm = U1.ultra();
dht.dht_read(D3);
temp=dht.temperature;
hum=dht.RH;
  Serial.println("NODE3 temperature:" + String(temp) + "humidity" + String(hum));

  //gas_value  = analogRead(A0);
  //Serial.println(gas_value);


  //  Serial.println(cm);

  delay(100);

}
#endif
