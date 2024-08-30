#ifndef SENSOR_H
#define SENSOR_H
#include "global.h"
#include "iot.h"
#include "lcd.h"

void F_sensor_data() {


  soil_value  = digitalRead(D_soil_sensor);
  water_value = analogRead(A_waterlevel_sensor);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    NODE 1    ");
  lcd.setCursor(0, 1);
  lcd.print("soil:");
  lcd.print(soil_value);
  lcd.print(8, 1);
  lcd.print("water:");
  lcd.print(water_value);
  delay(1000);

  if (soil_value == 1 && water_value < 900)
  {
    Serial.println("MOTOR ON");
    digitalWrite(P_pump_motor, HIGH);
    digitalWrite(N_pump_motor, LOW);
    motor = "MOTOR ON";
  }
  else
  {
    Serial.println("MOTOR OFF");
    digitalWrite(P_pump_motor, LOW);
    digitalWrite(N_pump_motor, LOW);
    motor = "MOTOR OFF";

  }

  Serial.println("NODE1 soil_value:" + String(soil_value) + "water_level:" + String(water_value));
  iot_send("*soil_value" + String(soil_value) + "water_level" + String(water_value) + "#");

}
#endif
