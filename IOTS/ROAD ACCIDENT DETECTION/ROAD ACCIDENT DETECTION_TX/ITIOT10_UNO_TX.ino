#include "initial.h"
#include "rpm.h"
#include "gps.h"

void speed_count(void);
void setup() {
  Serial.begin(9600);
  dht.dht_read(DHTPIN);
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("ROAD  ACCIDENT");
  lcd.setCursor(3, 1);
  lcd.print("DETECTION");
  Serial.println("WELCOME");
  //  pinMode(VIBRATION, INPUT);
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  pinMode(IRSENSOR, INPUT);
  pinMode(MOTOR_PLUSE, OUTPUT);
  pinMode(MOTOR_MINUS, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);
  analogWrite(MOTOR_PLUSE, 100);
  digitalWrite(MOTOR_MINUS, LOW);
  dht.dht_read(DHTPIN);

  attachInterrupt(digitalPinToInterrupt(2), VIB_ISR, LOW);
  //gps();

  delay(2000);
}

void loop() {
   dht.dht_read(DHTPIN);
  //Serial.println(dht.temperature);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEM:");
  lcd.print(dht.temperature);
  lcd.setCursor(0, 0);
  lcd.print("TEM:");

  if (dht.temperature >= 38)
  {
    lcd.setCursor(9, 0);
    lcd.print("T>HIGH");
  }
  else
  {
    lcd.setCursor(9, 0);
    lcd.print("T.NRML");
  }

  if (flag1 == true) {
    flag1 = false;
    analogWrite(MOTOR_PLUSE, 0);
    digitalWrite(MOTOR_MINUS, LOW);
    digitalWrite(A0, HIGH);
    GPS_SEND();
    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.print("ACCIDENT OCCUR");
    Serial.println("ACCIDENT OCCUR");
    delay(1000);
  }
  
  if (digitalRead(SWITCH) ==  HIGH) {

    analogWrite(MOTOR_PLUSE, 255);
    digitalWrite(MOTOR_MINUS, LOW);
    speed_count();
    lcd.setCursor(3, 1);
    lcd.print("HIGH SPEED");
    delay(2000);
  }
  else if (digitalRead(SWITCH) ==  LOW) {
    analogWrite(MOTOR_PLUSE, 100);
    digitalWrite(MOTOR_MINUS, LOW);
  }
  

}

void VIB_ISR() {
  flag1 = true;
}
