#ifndef PH_H
#define PH_H
#include "global.h"

void ph_func(void);

/******************************************************************************************/
void ph_func()
{
  for (int i = 1; i <= 2; i++) {
    String phdata = Serial.readStringUntil(':');
//    Serial.println(phdata);
    if (phdata != "") {
      String ph = Serial.readStringUntil('$');

//      Serial.println(ph);
      phValue = ph.toFloat();
//      Serial.println();
      Serial.println("PH Value");
      Serial.println(phValue);
    }
  }
  //  Serial.print(phValue);
  //  sprintf(L_array,"%-16d",phValue);
  //  lcd.setCursor(7, 0);
  //  lcd.print("PH:");
  //  lcd.setCursor(10, 0);
  //  lcd.print(L_array);
  //  if (phValue < 7.00)
  //  {
  //    Serial.println("acidic");
  //    return ph_acidic;
  //  }
  //  if ((phValue > 7.00) && (phValue < 12.00))
  //  {
  //    // Serial.println("normal");
  //    return ph_normal;
  //  }
  //  if (phValue > 12.00)
  //  {
  //    // Serial.println("alkaline");
  //    return ph_alkaline;
  //  }
}
/*************************************************************************************************/
#endif
