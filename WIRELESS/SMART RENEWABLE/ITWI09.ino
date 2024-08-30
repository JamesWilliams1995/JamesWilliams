
#include"rtc.h"
#include"lcd.h"
#include"global.h"
#include <avr/wdt.h>


void setup() {
  wdt_disable();
  Serial.begin(9600);
  pinMode(iot_on_off, INPUT_PULLUP);
  pinMode(iot_mode, INPUT_PULLUP);
  pinMode(RELAY_PIN1, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(RELAY_PIN1, HIGH);
  digitalWrite(RELAY_PIN2, HIGH);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("SMART RENEWABLE");
  lcd.setCursor(7, 1);
  lcd.print("ENERGY");
  delay(2000);
  lcd.clear();

  rtc_begin();

}

void loop()
{
  lcd.clear();
  rtc_check();
  //  lcd.setCursor(11, 1);
  //  lcd.print(Hor);
  // lcd.setCursor(13, 1);
  // lcd.print(":");
  lcd.setCursor(11, 1);
  lcd.print(Min);
  lcd.setCursor(13, 1);
  lcd.print(":");
  lcd.setCursor(14, 1);
  lcd.print(Sec);

  float current = 0;
  for (int i = 0; i < 20; i++)           //Averaging the 20 values to get better result.
  {
    measure.all(V, I, P, pf);
    current = current + I * current_transfer_ratio; //Calculating Actual Current and Summing
  }
  current = current / 20.0;
  lcd.setCursor(0, 0);
  lcd.print("CT:");
  lcd.setCursor(3, 0);
  lcd.print(current);


  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  lcd.setCursor(9, 0);
  lcd.print("D:");
  lcd.setCursor(11, 0);
  lcd.print(distance);


  adc_value = analogRead(A0);
  adc_voltage  = (adc_value * ref_voltage) / 1024.0;
  in_voltage = adc_voltage / (R2 / (R1 + R2));


  lcd.setCursor(0, 1);
  lcd.print(in_voltage);



  adc_value = analogRead(A1);
  adc_voltage1  = (adc_value * ref_voltage) / 1024.0;
  in_voltage1 = adc_voltage1 / (R2 / (R1 + R2));

  lcd.setCursor(5, 1);
  lcd.print(in_voltage1);
  /*************** AUTO MODE  ***********************************/

  if (digitalRead(iot_mode) == 1)
  {
    lcd.setCursor(15, 0);
    lcd.print('A');
    if ((distance <= 10) && ((Min >= 0) && (Min < 3)))
    {
      if ((in_voltage > 10) && (in_voltage1 > 10))
      {
        Serial.println("MODE 1");
        digitalWrite(RELAY_PIN1, LOW);
        digitalWrite(RELAY_PIN2, LOW);
      }
      if ((in_voltage1 > 10) && (in_voltage < 10))
      {
        Serial.println("MODE 2");
        digitalWrite(RELAY_PIN1, LOW);
        digitalWrite(RELAY_PIN2, HIGH);
      }
      if ((in_voltage1 < 10) && (in_voltage > 10))
      {
        Serial.println("MODE 3");
        digitalWrite(RELAY_PIN1, LOW);
        digitalWrite(RELAY_PIN2, LOW);
      }
      if ((in_voltage1 < 10) && (in_voltage < 10))
      {
        Serial.println("MODE 4");
        digitalWrite(RELAY_PIN1, HIGH);
        digitalWrite(RELAY_PIN2, HIGH);
      }
    }
    if (Min >= 3)
    {
      digitalWrite(RELAY_PIN1, HIGH);
      digitalWrite(RELAY_PIN2, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CLOSED");
      while (1);
    }
  }

  if (digitalRead(iot_mode) == 0)
  {
    lcd.setCursor(15, 0);
    lcd.print('M');
  }
  delay(1000);
}
void serialEvent(void)
{
  while (Serial.available() > 0)
  {
    char d = (char)Serial.read();
    switch (d)
    {
      case'1':
        {
          Serial.println("iot 1");
          if (digitalRead(iot_mode) == 0) {
            digitalWrite(RELAY_PIN1, LOW);
          }
          break;
        }
      case'2':
        {
          if (digitalRead(iot_mode) == 0) {

            digitalWrite(RELAY_PIN1, HIGH);
          }
          break;
        }
      case'3':
        {
          if (digitalRead(iot_mode) == 0) {

            digitalWrite(RELAY_PIN2, LOW);
          }
          break;
      } case'4':
        {
          if (digitalRead(iot_mode) == 0) {

            digitalWrite(RELAY_PIN2, HIGH);
          }
          break;
        }
    }
  }
}

//void iot_send(String data)
//{
//  for (int i = 0; i < data.length(); i++)
//  {
//    Serial.write(data[i]);
//  }
//  //delay(2000);
//}
