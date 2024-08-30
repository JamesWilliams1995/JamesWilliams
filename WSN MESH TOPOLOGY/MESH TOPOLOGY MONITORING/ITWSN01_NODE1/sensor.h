#ifndef SENSOR_H
#define SENSOR_H
#include "global.h"
#include "iot.h"
#include "lcd.h"
#include"dht11.h"
DHT dht;
void F_sensor_data() {


  dht_value  = digitalRead(D_DHT_sensor);
  gas_value = analogRead(A_GAS_sensor);
  Serial.print("TEMP:");
  Serial.println(dht_value);
  Serial.print("GAS:");
  Serial.println(gas_value);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    NODE 1    ");
  lcd.setCursor(0, 1);
  lcd.print("TEM:");
  lcd.print(dht_value);
  lcd.print(8, 1);
  lcd.print("GAS:");
  lcd.print(gas_value);
  delay(1000);
  

//  if (dht_value == 0 && gas_value < )
//  {
//    Serial.println("MOTOR ON");
//    digitalWrite(P_pump_motor, HIGH);
//    digitalWrite(N_pump_motor, LOW);
//    motor = "MOTOR ON";
//  }
//  else
//  {
//    Serial.println("MOTOR OFF");
//    digitalWrite(P_pump_motor, LOW);
//    digitalWrite(N_pump_motor, LOW);
//    motor = "MOTOR OFF";
//
//  }

  Serial.println("NODE1 dht_value:" + String(dht_value) + "gas_value:" + String(gas_value));
  iot_send("*dht_value" + String(dht_value) + "gas_level" + String(gas_value) + "#");

}
#endif
