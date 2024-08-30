#ifndef SENSORS_H
#define SENSORS_H

#define D_soil_sensor D0
#define A_waterlevel_sensor A0
#define P_pump_motor D1
#define N_pump_motor D2

int8_t soil_value;
int water_value;
String motor = "MOTOR OFF";

void FUNTION_STATE() {

  soil_value  = digitalRead(D_soil_sensor);
  water_value = analogRead(A_waterlevel_sensor);

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

  Serial.println("NODE2 soil_value:" + String(soil_value) + "water_level:" + String(water_value));

}
#endif
