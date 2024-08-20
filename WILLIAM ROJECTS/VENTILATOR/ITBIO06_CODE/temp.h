#ifndef TEMP_H
#define TEMP_H
#include"global.h"
#include <Adafruit_MLX90614.h>
#include<Wire.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


void Temp_state(void)
{
  Serial.println(mlx.readObjectTempC());
  TempF = (mlx.readObjectTempC() * 1.8) + 32;
}
#endif
