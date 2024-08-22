/**************************************************************/
//CODE : ITIOT14


/********************HEADER FILES*******************************/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include "global.h"
#include "ph.h"
#include "ultra.h"
#include "turbidity.h"

void ULTRA_SONIC1();
void ULTRA_SONIC2();
void ULTRA_SONIC3();
void ph_func();
void turb_read(void);


int i = 0;
int count = 0;

void setup()
{
  Serial.begin(9600);
  Serial.print("WATER LEVEL");
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WATER LEVEL");
  pinMode(MQ4_PIN, INPUT);
  pinMode(MQ135_PIN, INPUT);
  //  pinMode(PH_PIN, INPUT);
  //  pinMode(led, OUTPUT);
  pinMode(TURBIDITY_PIN, INPUT);
  pinMode(P_MOTOR1_PIN, OUTPUT);
  pinMode(P_MOTOR2_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(P_MOTOR1_PIN, LOW);
  digitalWrite(P_MOTOR2_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  U1.begin(A2, A3); //trig , echo
  U2.begin(8, 9);
  U3.begin(10, 11);
  delay(1000);

}

void loop()
{
  Serial.print("Welcome");
  ph_func();
  turb_read();
  ULTRA_SONIC1();
  ULTRA_SONIC2();
  ULTRA_SONIC3();
  int mq4_value = digitalRead(MQ4_PIN);
  int mq135_value = digitalRead(MQ135_PIN);
  Serial.println("MQ4:" + String(mq4_value));
  Serial.println("MQ135:" + String(mq135_value));

  if ((cm1 > 20) || (cm2 >= 30) || (cm3 > 20) || (phValue > 12.00) || (phValue < 6.00) || (mq4_value == 1))
  {
    digitalWrite(P_MOTOR1_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    if (((phValue > 12.00) || (cm1 > 20) ))
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("TANK1 QUALITY");
      lcd.setCursor(0, 1);
      lcd.print("    NOT OK");
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.println("alkline/tank1 empty/Methen detected");
      iot("*TANK 1 QUALITY NOT OK#");
    }
    else {
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
  if (((cm1 < 20) && (phValue > 6.00) && (phValue < 12.00) && (cm2 > 30) && (cm3 > 20)) && (mq4_value == 1))
  {
    count = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TANK1 QUALITY");
    lcd.setCursor(0, 1);
    lcd.print("  OK");
    Serial.println("tank1 full/ph normal/tank2 empty/tank3 empty/Methen not detected");
    //Serial.println("sump_full\tph_normal\ttank_empty");
    digitalWrite(P_MOTOR1_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    //    digitalWrite(led, HIGH);
    iot("*TANK 1 QUALITY OK#");
  }
  if ((cm2 <= 5 ) && (cm3 > 20 ) && (ntu >= 5 && ntu < 30)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TANK2 QUALITY");
    lcd.setCursor(0, 1);
    lcd.print("   OK");
    Serial.print("Tank2 motor on");
    digitalWrite(P_MOTOR2_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    iot("*TANK 2 QUALITY OK#");
  }
  if (cm2 > 30)
  {
    digitalWrite(P_MOTOR2_PIN, LOW);
  }
  if ((cm2 < 5) && (cm3 > 20 ) && (ntu >= 30))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TANK2 QUALITY");
    lcd.setCursor(0, 1);
    lcd.print("  NOT OK");
    Serial.print("tank2 motor off");
    digitalWrite(P_MOTOR2_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
    iot("*TANK 2 QUALITY NOT OK#");
  }
  if ((cm3 < 5 ) && (mq135_value == 1))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TANK3 CLEAR");
    lcd.setCursor(0, 1);
    lcd.print("     WATER");
    Serial.print("CLEAR WATER");
    iot("*TANK 3 QUALITY CLEAR#");
  }
  iot("@" + String(cm1) + "#" + "$" + String(cm2) + "#" + "^" + String(cm3) + "#" + "&" + String(mq4_value) + "#" + "!" + String(mq135_value) + "#");
  delay(500);
}

void iot(String s)
{
  for (int i = 0; i < s.length(); i++)
  {
    Serial.write(s[i]);
  }
}
