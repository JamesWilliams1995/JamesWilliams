
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#define green1 2
#define green2 3
#define green3 4
#define green4 5
#define yellow1 6
#define yellow2 7
#define yellow3 A0
#define yellow4 A1

void iott(String data);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(green1, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(green3, OUTPUT);
  pinMode(green4, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(yellow3, OUTPUT);
  pinMode(yellow4, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("TROFFIC");
  lcd.setCursor(2, 1);
  lcd.print("MONITARING");
  delay(2000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:

  //  Serial.print("lineA");
  //
  //  digitalWrite(green1, HIGH);
  //  digitalWrite(yellow1, LOW);
  //  digitalWrite(green2, HIGH);
  //  digitalWrite(yellow2, LOW);
  //  delay(10000);
  //  digitalWrite(green3, LOW);
  //  digitalWrite(yellow3, HIGH);
  //  digitalWrite(green4, LOW);
  //  digitalWrite(yellow4, HIGH);
  while (Serial.available() > 0) {
    char inchar = Serial.read();
    switch (inchar) {

      case 'A':
        Serial.print("line A");
        lcd.setCursor(2, 0);
        lcd.print("LINEA");
        digitalWrite(green1, HIGH);
        lcd.print("Green1-ON");
        digitalWrite(yellow1, LOW);
        digitalWrite(green2, LOW);
        lcd.print("Green2-OFF");
        digitalWrite(yellow2, HIGH);
        digitalWrite(green3, HIGH);
        lcd.print("Green3-ON");
        digitalWrite(yellow3, LOW);
        digitalWrite(green4, LOW);
        digitalWrite(yellow4, HIGH);
        lcd.print("yellow-ON");
        lcd.setCursor(0, 1);
        lcd.print("lane1&lane3open");
        iott("*LANE ONE OPEN\n#");
        iott("*LANE THREE OPEN#");
        break;
      case 'B':
        Serial.print("line B");
        lcd.setCursor(2, 0);
        lcd.print("LINE B");
        digitalWrite(green1, LOW);
        digitalWrite(yellow1, HIGH);
        digitalWrite(green2, HIGH);
        digitalWrite(yellow2, LOW);
        digitalWrite(green3, LOW);
        digitalWrite(yellow3, HIGH);
        digitalWrite(green4, HIGH);
        digitalWrite(yellow4, LOW);
        lcd.setCursor(0, 1);
        lcd.print("lane2&lane4open");
        iott("*LANE TWO OPEN \n#");
        iott("*LANE FOUR OPEN#");
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
  
