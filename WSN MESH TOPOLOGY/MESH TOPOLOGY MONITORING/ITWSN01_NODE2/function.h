#ifndef SENSORS_H
#define SENSORS_H

#define D_DHT_sensor D0
#define A_GAS_sensor A0
//#define P_pump_motor D1
//#define N_pump_motor D2

int8_t dht_value;
int gas_value;
//String motor = "MOTOR OFF";

void FUNTION_STATE() {

  dht_value  = digitalRead(D_DHT_sensor);
  gas_value = analogRead(A_GAS_sensor);
  Serial.println("TEMP:");
  Serial.print(dht_value);
  Serial.println("GAS:");
  Serial.print(gas_value);
              
  
  
//  if (soil_value == 0 && water_value < 900)
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

  Serial.println("NODE2 dht_value:" + String(dht_value) + "gas_level:" + String(gas_value));

}
#endif
