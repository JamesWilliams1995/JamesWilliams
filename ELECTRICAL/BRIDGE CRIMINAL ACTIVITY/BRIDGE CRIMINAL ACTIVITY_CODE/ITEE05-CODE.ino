#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//#include <SoftwareSerial.h>
//SoftwareSerial ss(8,9);//iot
#include "global.h"
#include "gps.h"
#include "gsm.h"
#include "rtc.h"
#include "ultra.h"
//#include "ss.h"

const int onmin1 = 0;
const int onmin2 = 05;

void gsm(String number, String data);
void rtc_begin();
void rtc_check();
void ULTRA_SONIC1();
void ULTRA_SONIC2();
void ULTRA_SONIC3();
int count = 0;
int control = 12;
int count1 = 0;
int count2 = 0;
int count3 = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(9600);
  Serial.println("BRIDGE CRIMINAL ACTIVITY");
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("BRIDGE CRIMINAL");
  lcd.setCursor(0, 1);
  lcd.print("     ACTIVITY");
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  U1.begin(A0, A1);
  U2.begin(A2, A3);
  U3.begin(6, 7);
  //  rtc_begin();
  delay(1000);
}

void loop() {
  int cont = digitalRead(control);
  Serial.println(cont);
  delay(1000);
  if (cont == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("manual mode");
    while (Serial.available() > 0) {
      char data = Serial.read();
      Serial.print(data);
      switch (data) {
        case '2': {
            digitalWrite(LED1_PIN, HIGH);
            break;
          }
        case '3': {
            digitalWrite(LED1_PIN, LOW);
            break;
          }
        case '4': {
            digitalWrite(LED2_PIN, HIGH);
            break;
          }
        case '5': {
            digitalWrite(LED2_PIN, LOW);
            break;
          }
        case '6': {
            digitalWrite(LED3_PIN, HIGH);
            break;
          }
        case '7': {
            digitalWrite(LED3_PIN, LOW);
            break;
          }
          break;
      }
    }
  }
  delay(1000);
  if (cont == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("auto mode");
    ULTRA_SONIC1();
    ULTRA_SONIC2();
    ULTRA_SONIC3();
    //delay(2000);
    //  rtc_check();


    int LDR_DATA = digitalRead(LDR_PIN);
    Serial.print("ldr:");
    Serial.println(LDR_DATA);
    if (count <= 5) {

      if ( count <= 10 && LDR_DATA == HIGH)
      {
        if (cm1 <= 20 )
        { Serial.print('a');
          digitalWrite(LED1_PIN, HIGH);
          count1++;
          //      Serial.print("@");
          Serial.print(count1);
          if (count1 == 2)
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("   CRIMINAL   ");
            lcd.setCursor(0, 1);
            lcd.print("    ACTIVITY");
            gsm("8189988347", "CRIMINAL ACTIVITY SPOTTED");
            iot("*CRIMINAL ACTIVITY SPOTTED#");
          }
        }

        if (cm1 > 20)
        {
          digitalWrite(LED1_PIN, LOW);
        }

        if (cm2 <= 20 )
        { Serial.print('b');
          digitalWrite(LED1_PIN, HIGH);
          digitalWrite(LED2_PIN, HIGH);
          count2++;
          if (count2 == 2)
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("   CRIMINAL   ");
            lcd.setCursor(0, 1);
            lcd.print("    ACTIVITY");
            gsm("8189988347", "CRIMINAL ACTIVITY SPOTTED");
            iot("*CRIMINAL ACTIVITY SPOTTED#");
          }
        }

        if (cm2 > 20)
        {
          digitalWrite(LED1_PIN, LOW);
          digitalWrite(LED2_PIN, LOW);
        }

        if (cm3 <= 20 )
        { Serial.print('c');
          digitalWrite(LED2_PIN, HIGH);
          digitalWrite(LED3_PIN, HIGH);
          count3++;
          if (count3 == 2)
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("   CRIMINAL   ");
            lcd.setCursor(0, 1);
            lcd.print("    ACTIVITY");
            gsm("8189988347", "CRIMINAL ACTIVITY SPOTTED");
            iot("*CRIMINAL ACTIVITY SPOTTED#");
          }
        }

        if (cm3 > 20)
        { digitalWrite(LED2_PIN, LOW);
          digitalWrite(LED3_PIN, LOW);
        }
      }
      if ( LDR_DATA == HIGH )
      {
        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, LOW);
        digitalWrite(LED3_PIN, LOW);
      }
    } count++;
    Serial.println(count);
    //      break;
  }
  delay(1000);
}
void iot(String s)
{
  for (int i = 0; i < s.length(); i++)
  {
    ss.write(s[i]);
  }
}
