#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#include "global.h"
#include "gps.h"
#include "gsm.h"
#include "rtc.h"
#include "ultra.h"

const int onmin1 = 0;
const int onmin2 = 05;

void gsm(String number, String data);
void rtc_begin();
void rtc_check();
void ULTRA_SONIC1();
void ULTRA_SONIC2();
void ULTRA_SONIC3();
int count1 = 0;
int count2 = 0;
int count3 = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("BRIDGE CRIMINAL ACTIVITY");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("BRIDGE CRIMINAL");
  lcd.setCursor(0, 1);
  lcd.print("     ACTIVITY");
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  U1.begin(A0, A1);
  U2.begin(A2, A3);
  U3.begin(6, 7);
  rtc_begin();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  ULTRA_SONIC1();
  ULTRA_SONIC2();
  ULTRA_SONIC3();
  rtc_check();
  int LDR_DATA = digitalRead(LDR_PIN);
  if (Min == onmin1 && LDR_DATA == HIGH)
  {
    if (cm1 <= 20 )
    {
      digitalWrite(LED1_PIN, HIGH);
      count1++;
      if (count1 == 20)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("   CRIMINAL   ");
        lcd.setCursor(0, 1);
        lcd.print("    ACTIVITY");
        gsm("7339011809", "CRIMINAL ACTIVITY SPOTTED");
//        iot("*CRIMINAL ACTIVITY SPOTTED#");
      }
    }

    if (cm1 > 20)
    {
      digitalWrite(LED1_PIN, LOW);
    }

    if (cm2 <= 20 )
    {
      digitalWrite(LED2_PIN, HIGH);
      count2++;
      if (count2 == 20)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("   CRIMINAL   ");
        lcd.setCursor(0, 1);
        lcd.print("    ACTIVITY");
        gsm("7339011809", "CRIMINAL ACTIVITY SPOTTED");
//        iot("*CRIMINAL ACTIVITY SPOTTED#");
      }
    }

    if (cm2 > 20)
    {
      digitalWrite(LED2_PIN, LOW);
    }

    if (cm3 <= 20 )
    {
      digitalWrite(LED3_PIN, HIGH);
      count3++;
      if (count3 == 20)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("   CRIMINAL   ");
        lcd.setCursor(0, 1);
        lcd.print("    ACTIVITY");
        gsm("7339011809", "CRIMINAL ACTIVITY SPOTTED");
//        iot("*CRIMINAL ACTIVITY SPOTTED#");
      }
    }

    if (cm3 > 20)
    {
      digitalWrite(LED3_PIN, LOW);
    }
  }

  if (Min == onmin2 || LDR_DATA == HIGH )
  {
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, LOW);
  }
}

//void iot(String s)
//{
//  for (int i = 0; i < s.length(); i++)
//  {
//    Serial.write(s[i]);
//  }
//}
