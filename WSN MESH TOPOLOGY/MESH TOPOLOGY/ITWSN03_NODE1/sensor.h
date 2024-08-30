#ifndef SENSOR_H
#define SENSOR_H
#include "global.h"
#include "lcd.h"
#include "iot.h"

void F_sensor_data() {

  ir_value  = digitalRead(D2);
  cm = U1.ultra();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("     NODE 1     ");
  lcd.setCursor(0,1);
  lcd.print("IR:");
  lcd.print(ir_value);
  lcd.setCursor(8,1);
  lcd.print("UL:");
  lcd.print(cm);
  delay(1000);
  Serial.println("NODE1 ir_value:" + String(ir_value) + "ULTRASONIC:" + String(cm));
  iot_send("*ir_value" + String(ir_value) + " ULTRASONIC" + String(cm) + "#");

}
#endif
