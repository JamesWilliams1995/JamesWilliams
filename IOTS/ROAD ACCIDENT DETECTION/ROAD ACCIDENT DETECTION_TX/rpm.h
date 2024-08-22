#ifndef RPM_H
#define RPM_H
#include "initial.h"

int rpm_read = 0;
void speed_count(void)
{
  while (digitalRead(IRSENSOR) == 1);
  unsigned long temp = millis();
  while (millis() < (temp + 5000))
  {
    if (digitalRead(IRSENSOR) == 0)
    {
      rpm_read = rpm_read + 1;
      while (digitalRead(IRSENSOR) == 0);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("RPM:");
      lcd.setCursor(14, 0);
      lcd.print(rpm_read);
    }

  }
  rpm_read = rpm_read * 12;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RPM:");
  lcd.setCursor(4, 0);
  lcd.print(rpm_read);


  if (rpm_read > 120)
  {
    analogWrite(MOTOR_PLUSE, 100);
    digitalWrite(MOTOR_MINUS, LOW);
  }
  delay(3000);
  rpm_read = 0;


}

#endif
