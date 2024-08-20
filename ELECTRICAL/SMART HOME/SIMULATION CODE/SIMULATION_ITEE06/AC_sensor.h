#ifndef RFID_H
#define RFID_H 
#include "ACS712.h"

/*
  This example shows how to measure the power consumption
  of devices in 230V electrical system
  or any other system with alternative current
*/
float I;
// We have 30 amps version sensor connected to A0 pin of arduino
// Replace with your version if necessary
ACS712 sensor(ACS712_20A, A1);

void ac_sensor() {
  // We use 230V because it is the common standard in European countries
  // Change to your local, if necessary
  float U = 230;

  // To measure current we need to know the frequency of current
  // By default 50Hz is used, but you can specify desired frequency
  // as first argument to getCurrentAC() method, if necessary
  I = sensor.getCurrentAC();

  // To calculate the power we need voltage multiplied by current
  //float P = U * I;

  Serial.println(String("I = ") + I + " A");
  //Serial.println(String("P = ") + P + " Watts");


  delay(1000);
}
#endif
