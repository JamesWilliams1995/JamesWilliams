#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

#include "gsm.h"
#define FLAME1_PIN 2
#define FLAME2_PIN 3
#define FLAME3_PIN 4
#define FLAME4_PIN 5
#define GAS1_PIN A0
#define GAS2_PIN A1
#define BUZZER_PIN 6
#define RELAY_PIN 7

void gsm(String number, String data);
void setup()
{
  Serial.begin(9600);
  Serial.print("FIRE EXTINGUISHER");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(" FIRE ");
  lcd.setCursor(0, 1);
  lcd.print("    EXTINGUISHER");
  pinMode(FLAME1_PIN, INPUT);
  pinMode(FLAME2_PIN, INPUT);
  pinMode(FLAME3_PIN, INPUT);
  pinMode(FLAME4_PIN, INPUT);
  pinMode(GAS1_PIN, INPUT);
  pinMode(GAS2_PIN, INPUT);
  pinMode(BUZZER_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  delay(100);
}

void loop()
{
  int FLAME1_DATA = digitalRead(FLAME1_PIN);
  int FLAME2_DATA = digitalRead(FLAME2_PIN);
  int FLAME3_DATA = digitalRead(FLAME3_PIN);
  int FLAME4_DATA = digitalRead(FLAME4_PIN);
  int GAS1_DATA = digitalRead(GAS1_PIN);
  int GAS2_DATA = digitalRead(GAS2_PIN);

  lcd.clear();
  if (GAS1_DATA == 1 || GAS2_DATA == 1)
  {
    Serial.print("--SMOKE DETECTED--");
    lcd.setCursor(0, 0);
    lcd.print("  SMOKE DETECTED  ");
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RELAY_PIN, HIGH);
    gsm("7339011809","SMOKE DETECTED");
  }

  if (GAS1_DATA == 0 || GAS2_DATA == 0)
  {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);
  }

  if (FLAME1_DATA == 1 || FLAME2_DATA == 1 || FLAME3_DATA == 1 || FLAME4_DATA == 1)
  {
    Serial.print("--FIRE DETECTED--");
    lcd.setCursor(0, 0);
    lcd.print("  FIRE DETECTED  ");
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RELAY_PIN, HIGH);
    gsm("7339011809","FIRE DETECTED");
  }

  if (FLAME1_DATA == 0 || FLAME2_DATA == 0 || FLAME3_DATA == 0 || FLAME4_DATA == 0)
  {

    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);
  }
}
