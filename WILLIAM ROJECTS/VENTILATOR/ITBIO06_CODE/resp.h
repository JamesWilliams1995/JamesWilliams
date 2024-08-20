#ifndef RESP_H
#define RESP_H
#include"global.h"
#include"lcd.h"

void resp_state(void)
{
  resp = 0;
  for (int i = 0; i < 20; i++)
  {
    //    lcd.setCursor(13, 0);
    //    lcd.print(digitalRead(A0));
    //    lcd.setCursor(15, 0);
    //    lcd.print('R');
    if (r_flag == true)
    {
      r_flag = false;
      resp++;
    }
    lcd.setCursor(13, 1);
    lcd.print(resp);
    delay(1000);
  }
  resp = resp * 3; //20*3= 60 sec
  //  lcd.setCursor(0, 15);
  //  lcd.print(' ');
//  if ((resp < 12) || (resp > 16) )  // avg human respiration 12-16 breath per minute
//  {
    //    lcd.clear();
    //    lcd.setCursor(0, 0);
    //    lcd.print("BREATH");
    //    lcd.setCursor(0, 1);
    //    lcd.print("ABNORMAL");
    //    lifi.print('R');
   // iot_send("*RESPIRATION ABNORMAL#");
    iott("^" + String(resp) + "#");

    delay(2000); resp = 0;
  //}
}
#endif
