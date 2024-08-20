#ifndef EEPROM_H
#define EEPROM_H
#include <EEPROM.h>
#include "lcd.h"

void eeprom_clear()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RESETING...");
  for (int i = 0; i <= EEPROM.length(); i++)
    EEPROM.write(i, 0);
}

#endif
