
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#define buzzer 4
char inChar = ' ';

void setup()
{
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("KEY");

  delay(1000);

}


void loop()
{
  while (Serial.available() > 0)

    inChar = Serial.read();
  Serial.print(inChar);
  switch (inChar)
  {
    case 'A':
      lcd.setCursor(0, 0);
      lcd.print("PSW ! MATCHED");
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      break;
  }
}
