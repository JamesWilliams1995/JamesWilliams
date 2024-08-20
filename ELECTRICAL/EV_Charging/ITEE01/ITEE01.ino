

#include "global.h"
#include "lcd.h"
#include "iotkeypad.h"
#include "ss.h"
#include "rfid.h"
#include "eeprom.h"
#include "ui.h"
#include "iot.h"

/**********function declaration******/


void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(D_irsensor_1, INPUT);
  pinMode(D_irsensor_2, INPUT);
  pinMode(D_switch, INPUT_PULLUP);
  digitalWrite(D_relay_1, HIGH);
  digitalWrite(D_relay_2, HIGH);
  digitalWrite(D_buzzer, LOW);
  pinMode(D_relay_1, OUTPUT);
  pinMode(D_relay_2, OUTPUT);
  pinMode(D_buzzer, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("WIRELESS CHRGING");
  lcd.setCursor(4, 1);
  lcd.print("STATION");
  delay(1000);
  lcd.clear();
}
void loop()
{
  ev_charging();
  delay(1000);
}
