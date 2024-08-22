#include "initial.h"
#include "ht.h"
#include "rpm.h"
#include "gps.h"


void setup() {
  Serial.begin(9600);
  dht.dht_read(DHTPIN);
  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("welcome");
  Serial.println("welcome");
  pinMode(VIBRATION, INPUT);
  pinMode(IRSENSOR, INPUT);
  pinMode(MOTOR_PLUSE, OUTPUT);
  pinMode(MOTOR_MINUS, OUTPUT);
  digitalWrite(MOTOR_PLUSE, HIGH);
  digitalWrite(MOTOR_MINUS, LOW);
  attachInterrupt(digitalPinToInterrupt(3), VIB_SENSOR, HIGH);
  //gps();
  delay(100);
  lcd.clear();
}

void loop() {


  TEMP();

  RPM();

  //Serial.println(rpm);

  
  if (rpm > 150) {
    analogWrite(MOTOR_PLUSE, 100);
    digitalWrite(MOTOR_MINUS, LOW);
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("OVER SPEED");
    Serial.println("over speed");
//    delay(2000);
    
  }
//  else {
//    lcd.clear();
//    lcd.setCursor(2, 1);
//    lcd.print("NORMAL SPEED");
//    Serial.println("normal speed");
//  }
  if (flag1 == true) {
    flag1 = false;
    GPS_SEND();
    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.print("ACCIDENT OCCUR");
    Serial.println("ACCIDENT OCCUR");
    delay(100);
  }
  else {
    Serial.println("NO ACCIDENT");
  }
}

void VIB_SENSOR() {
  flag1 = true;
}
