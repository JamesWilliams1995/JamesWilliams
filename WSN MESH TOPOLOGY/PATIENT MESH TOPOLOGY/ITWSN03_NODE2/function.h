#ifndef SENSORS_H
#define SENSORS_H

//#define HEART_SENSOR D4

//#include <ultrasonic.h>
//ULTRASONIC U1;
//int ir_value;
//int gas_value;
//int cm ;
//#include "heartrate.h"
#include "dht11.h"
DHT dht;
int temp,hum;

void FUNTION_STATE() {
   dht.dht_read(D0);
   temp=dht.temperature;
   hum=dht.RH;

   
   
    Serial.println("NODE2 temperature:" + String(temp) + "humidity:" + String(hum));
 

  

}
#endif
