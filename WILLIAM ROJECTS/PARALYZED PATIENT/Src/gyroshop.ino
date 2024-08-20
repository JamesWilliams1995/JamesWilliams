#include <Wire.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#include"dht11.h"
#include"gsm.h"
#define Heart 5

const int MPU1 = 0x68;           //address for SENSOR 1  (sensor that is placed on the shank)
float GX, GY, GZ, AcX, AcY, AcZ;             //global variables for SENSOR 1 raw data  (sensor that is placed on the shank)
float GYX, GYY, GYZ, AYX, AYY, AYZ;

int minVal = 265;                //control the sensor angular velocity
int maxVal = 402;


int heart_rate = 0;
DHT dht;
int fahrenheit;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(2, INPUT);
  pinMode(Heart,  INPUT_PULLUP);
  lcd.setCursor(0, 0);
  lcd.print("PARALYSED PATIENT");
  lcd.setCursor(4, 1);
  lcd.print("MONITORING");
  lcd.clear();

  Wire.begin();                      //SENSOR 1  (sensor that is placed on the shank)
  Wire.beginTransmission(MPU1);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);


  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  TCCR1B |= 0X07;
  interrupts();
  

  delay(1000);
}




void loop() {

  dht.dht_read(2);
  fahrenheit = (dht.temperature * 1.8) + 32;
  TCNT1 = 0;
  delay(5000);
  heart_rate = (TCNT1 * 12);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:" + String(fahrenheit) + "f");
  Serial.println(fahrenheit);
  
  if (fahrenheit > 100)
  {
    lcd.setCursor(13, 0);
    lcd.print("T_AN");
    send_sms("9074126766", "TEMPERATURE ABNORMAL");
  }

  else
  {
    lcd.setCursor(12,0);
    lcd.print("T_N");
  }
  /*************heart beat *******************/

  lcd.setCursor(6, 0);
  lcd.print("H:" + String(heart_rate) + " h");
  // Serial.println(heart_rate);


  if ((heart_rate > 20 && heart_rate < 60) || (heart_rate > 100))

  {
    lcd.setCursor(11, 1);
    lcd.print("H_AB");
    send_sms("9074126766", "HB NORMAL");
  }

  else
  {
    lcd.setCursor(11, 1);
    lcd.print("H_NL");
  }
  /*******************************gyro********************/
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
  //  Serial.println(GYY);
  //  Serial.print("@");
  //  Serial.println(GYZ);

  if (GYX >= 35  && GYX <= 55 && GYY <= 337 && GYZ <= 130)
  {
    lcd.setCursor(1, 1);
    lcd.print("FOOD NEED");
    send_sms("9074126766", "FOOD NEED");
  }
  else if (GYX > 330 && GYY > 330)
  {
    lcd.setCursor(1, 1);
    lcd.print("WATER");
    send_sms("9074126766", "WATER");
  }
  else if (GYX <= 15 && GYY >= 340 || GYY <= 10)
  {
    lcd.setCursor(1, 1);
    lcd.print("REST ROOM");
    send_sms("9074126766", "REST ROOM");
  }

  delay(1000);
}
