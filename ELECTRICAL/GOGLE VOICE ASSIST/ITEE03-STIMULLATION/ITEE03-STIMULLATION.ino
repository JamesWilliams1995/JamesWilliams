#include<LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#include "ss.h"
#define Bulb
#define Dc_fan
#define plug_ponit
int relay1 = 2;
int relay2 = 4;
int relay3 = 5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CONTROL ROBOT");


}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    char inchar = Serial.read();

    switch (inchar) {
      case 'A':
        Serial.print("LIGHT ON");
        digitalWrite(relay1, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("light ON");
        iott("*LIGHT ON \n#");
        break;
      case 'B':
        Serial.print("LIGHT OFF");
        digitalWrite(relay1, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LIGHT OFF");
        iott("@LIGHT OFF \n#");
        break;
      case '1':
        Serial.print("FAN ON");
        digitalWrite(relay2, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FAN ON");
        iott("$FAN ON \n#");
        break;
      case '0':
        Serial.print("FAN OFF");
        digitalWrite(relay2, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FAN OFF");
        iott("^FAN OFF \n#");
      case 'E':
        Serial.print("PLUG BOX ON");
        digitalWrite(relay3, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PLUG BOX ON");
        iott("*FAN ON \n#");
        iott("&PLUG BOX ON \n#");
      case 'F':
        Serial.print("PLUG BOX OFF");
        digitalWrite(relay3, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PLUG BOXN OFF");
        iott("*FAN ON \n#");
        iott("%PLUG BOX OFF \n#");


    }


  }

}
void iott(String data)
{
  for (int i = 0; i < data.length(); i++)
  {
    Serial.write(data[i]);
  }
  delay(3000);
}
