#ifndef RTC_H
#define RTC_H
#include"Arduino.h"
#include <DS3231.h>
#include <Wire.h>
DS3231  rtc(SDA, SCL);
Time  t;
//const int onhour=09;
//const int onmin1=01;
//const int onmin2=02;
//const int onmin3=03;
int Hor;
int Min;
int Sec;
//
//extern int Min_inc;
//extern int unit_count;

void rtc_init(void)
{
  
  Wire.begin();
  rtc.begin();
//  rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  rtc.setTime(9, 00, 00);    // Set the time to 12:00:00 (24hr format)
//  rtc.setDate(12, 31, 2021);   // Set the date to January 1st, 2014
  delay(1000);
}
void rtc_check()
{
  t = rtc.getTime();
  Hor = t.hour;
  Min = t.min;
  Sec = t.sec; 

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(Hor);
  lcd.setCursor(2, 1);
  lcd.print(':');
  lcd.setCursor(3, 1);
  lcd.print(Min);
  lcd.setCursor(5, 1);
  lcd.print(':');
  lcd.setCursor(6, 1);
  lcd.print(Sec);
  Serial.print(Hor);
  Serial.print(Min);
  Serial.print(Sec);
  
}
#endif
