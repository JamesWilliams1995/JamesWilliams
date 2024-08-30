#ifndef RTC_H
#define RTC_H
#include"Arduino.h"
#include <DS3231.h>
#include <Wire.h>
DS3231  rtc(SDA, SCL);
Time  t;
int Hor;
int Min;
int Sec;

extern int Min_inc;
extern int unit_count;

void rtc_begin()
{
  Wire.begin();
  rtc.begin();
  rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  rtc.setTime(9, 00, 00);    // Set the time to 12:00:00 (24hr format)
  rtc.setDate(12, 31, 2021);   // Set the date to January 1st, 2014
  delay(2000);
}
int rtc_check()
{
  t = rtc.getTime();
  Hor = t.hour;
  Min = t.min;
  Sec = t.sec;  
}
#endif
