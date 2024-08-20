#ifndef GYRO_H
#define GYRO_H
#include "global.h"

const int MPU1 = 0x68;           //address for SENSOR 1  (sensor that is placed on the shank) 
float GX, GY, GZ;                //global variables for SENSOR 1 raw data  (sensor that is placed on the shank) 

float GYX, GYY, GYZ;             //global variables for SENSOR 1  (sensor that is placed on the shank) after 360 degree conversion 
float dummy1, dummy2;            //angle that is respective ground variables

int minVal = 265;                //control the sensor angular velocity      
int maxVal = 402;

void gyro(void)
{
  Wire.beginTransmission(MPU1);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU1, 12, true);
  GX = Wire.read() << 8 | Wire.read();                //raw data reading for the angular velocity for SENSOR 1  (sensor that is placed on the shank)
  GY = Wire.read() << 8 | Wire.read();
  GZ = Wire.read() << 8 | Wire.read();

  int X1ANG = map(GX, minVal, maxVal, -90, 90);       // change the raw data into degrees for SENSOR 1  (sensor that is placed on the shank)
  int Y1ANG = map(GY, minVal, maxVal, -90, 90);
  int Z1ANG = map(GZ, minVal, maxVal, -90, 90);

  GYX = RAD_TO_DEG * (atan2(-Y1ANG, -Z1ANG) + PI);
  GYY = RAD_TO_DEG * (atan2(-X1ANG, -Z1ANG) + PI);
  GYZ = RAD_TO_DEG * (atan2(-Y1ANG, -X1ANG) + PI);

  /************************************************************/
  
  Serial.print("GYRO X = "); Serial.println(GYX); // 40 or 45
  //Serial.print("GYRO Y = "); Serial.println(GYY); //80
  //Serial.print("GYRO Z ="); Serial.println(GYZ);
}
#endif
