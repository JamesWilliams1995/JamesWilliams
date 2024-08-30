#ifndef PYTHON_H
#define PYTHON_H
char face();
char inchar;
char face()
{
   while (  Serial1.available() > 0)
      {
//        lcd.setCursor(0, 0);
//        lcd.print("please view cam");
        inchar =   Serial1.read();
        Serial.print(inchar);
      }
      return inchar;
}
#endif
