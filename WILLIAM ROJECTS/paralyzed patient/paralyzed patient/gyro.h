#ifndef GYRO_H
#define GYRO_H
#include<Wire.h>

const int MPU1 = 0x68;           //address for SENSOR 1  (sensor that is placed on the shank)

float GX, GY, GZ;             //global variables for SENSOR 1 raw data  (sensor that is placed on the shank)
float GYX, GYY, GYZ;

int minVal = 265;                //control the sensor angular velocity
int maxVal = 402;

void Gsetup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();                      //SENSOR 1  (sensor that is placed on the shank)
  Wire.beginTransmission(MPU1);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  delay(500);
}

void Gloop() {
  // put your main code here, to run repeatedly:
//  lcd.setCursor(15, 1);
//  lcd.print("G");
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

//  Serial.println(GYX);
//  Serial.print(":");
//  Serial.print(GYY);
//  Serial.print(":");
//  Serial.println(GYZ);
  //delay(500);
}

#endif
