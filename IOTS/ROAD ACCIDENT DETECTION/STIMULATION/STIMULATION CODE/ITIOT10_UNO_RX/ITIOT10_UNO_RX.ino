#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
void IOT(String s);
String tdata;
int count = 0;
//char tdata1[50];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  //lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("HELLO !");
  Serial.println("HELLO..!");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

  char tdata1[20];
  count = 0;
  tdata = "";
  while (Serial.available() > 0)
  {
    //lcd.clear();

    char c = Serial.read();
    // Serial.print(c);
    if (c == '*')
    {
      while (Serial.available() > 0)
      { //lcd.clear();
        //IOT("*ACCIDENT#");
//        lcd.setCursor(1, 1);
//        lcd.print("ACCIDENT OCCUR");
        char t = Serial.read();
        if (count == 50)
        {
          break;
        }
        if (t == '#') {
          break;
        }
        tdata += t;
        count++;
      }
    }
    //    delay(1000);
    //lcd.clear();
  }
  if ( tdata.length() > 0 )
  {
    for (int i = 0; i < 20; i++) {
      tdata1[i] = tdata[i];
    }
    tdata = "";
    delay(2000);
  }
  tdata = "";
  count = 0;
  Serial.println(tdata1);
  lcd.clear();
  lcd.setCursor(3, 1);
  lcd.print(tdata1);
  delay(200);
  //  if (tdata1 > 0) {
  //
  //  }
  //IOT("*" + String(tdata1) + "#");
  for (int i = 0; i <= 20; i++) {
    tdata1[i] = '\0';
  }
  //Serial.println(tdata1);
}
//void IOT(String s) {
//  for (int i = 0; i < s.length(); i++) {
//    Serial.write(s[i]);
//  }
//  delay(3000);
//}
