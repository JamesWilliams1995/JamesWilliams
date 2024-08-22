/**************************************************************/
//CODE : ITIOT14


/********************HEADER FILES*******************************/
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 16, 2);
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
  lcd.init(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WATER LEVEL");
  delay(1000);
  pinMode(MQ4_PIN, INPUT);
  pinMode(MQ135_PIN, INPUT);
  //  pinMode(PH_PIN, INPUT);
  pinMode(led, OUTPUT);
  pinMode(TURBIDITY_PIN, INPUT);
  pinMode(P_MOTOR1_PIN, OUTPUT);
  pinMode(P_MOTOR2_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(P_MOTOR1_PIN, HIGH);
  digitalWrite(P_MOTOR2_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  U1.begin(A2, A3); //trig , echo
  U2.begin(A5, A4);
  U3.begin(A6, A7);

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

  if ((cm1 > 20) || (cm2 >= 30) || (cm3 > 20) || (phValue > 12.00) || (phValue < 6.00) || (mq4_value == LOW))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MOTOR OFF");
    Serial.print("MOTOR OFF");
    digitalWrite(P_MOTOR1_PIN, LOW);
    digitalWrite(led, LOW);
    if (((phValue > 12.00) || (cm1 > 20) ))
    {
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.println("alkline/tank1 empty/Methen detected");
    }
    else {
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
  if (((cm1 < 20) && (phValue > 6.00) && (phValue < 12.00) && (cm2 > 30) && (cm3 > 20)) && (mq4_value == LOW))
  {
    lcd.setCursor(2, 0);
    lcd.print("ON ");
    count = 0;
    Serial.println("tank1 full/ph normal/tank2 empty/tank3 empty/Methen not detected");
    //Serial.println("sump_full\tph_normal\ttank_empty");
    digitalWrite(P_MOTOR1_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(led, HIGH);
  }
  if ((cm2 <= 5 ) && (cm3 > 20 ) && (ntu >= 10 && ntu < 30)) {
    digitalWrite(P_MOTOR2_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
  }
  if ((cm2 < 5) && (cm3 > 20 ) && (ntu >= 30))
  {
    digitalWrite(P_MOTOR2_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
  }
  if ((cm3 < 5 ) && (mq135_value == 1))
  {
    Serial.print("CLEAR WATER");
  }
  delay(500);
}
