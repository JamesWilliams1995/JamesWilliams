#ifndef EEPROM_H
#define EEPROM_H

#include<EEPROM.h>
#include"UI.h"
#include"fingerenroll.h"
extern volatile int reg_bank[4];
extern int mob[10];
extern int card, fno;

void thankyou();
void thankyou()
{
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("THANK YOU!!!");
wdt_enable(WDTO_2S);
key_value = 'x';
wdt_enable(WDTO_2S);
while (1);
}
void eeprom_clear()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RESETING...");
  fclr();
  for (int i = 0; i < EEPROM.length(); i++)
  {
    EEPROM.write(i, 0);
    Serial.println(EEPROM.read(i));
  }
  
}
void validate()
{
  Serial.println();
  for (int i = 0; i < 4; i++)
  {
    reg_bank[i] = EEPROM.read(i);

    Serial.println(reg_bank[i]);
  }
  Serial.println();
  for (int i = 0; i < 4; i++)
  {
    account[i] = EEPROM.read((i + 10) * 10);
    Serial.println(account[i]);
    account[i] = account[i] * (100);
  }
  for (int i = 0; i < 10; i++)
  {
    mob[i] = EEPROM.read(i + 200);
    Serial.print(mob[i]);
  }
  Serial.println();
  Serial.println();
  card = EEPROM.read(1000);
  fno = EEPROM.read(1001);
  for (int i = 1000; i < 1002; i++)
  {
    Serial.println(EEPROM.read(i));
  }
  Serial.println();
  Serial.println();
}





#endif
