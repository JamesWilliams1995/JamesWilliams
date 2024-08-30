#ifndef SENSOR_H
#define SENSOR_H
#include "global.h"
#include "lcd.h"
#include "iot.h"
#include "heartrate.h"


void F_sensor_data() {
  dht.dht_read(D0);
   temp = dht.temperature;
   hum=dht.RH;
  Serial.print("Temperature:");
  Serial.println(temp);
  Serial.print("Humidity:");
  Serial.println(hum);
  
 
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("N");
    lcd.setCursor(0,1);
    lcd.print("1");
    lcd.setCursor(5,0);
    lcd.print("Temp");
    lcd.setCursor(5,1);
    lcd.print(temp);
    lcd.setCursor(12,0);
    lcd.print("Hum");
    lcd.setCursor(12,1);
    lcd.print(hum);
    delay(1000);
  Serial.println("NODE1 temperature:" + String(temp) + "humidity:" + String(hum));
  iot_send("*temperature" + String(temp) + "humidity" + String(hum) + "#");

}
#endif
