#include<LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#include<SoftwareSerial.h>
SoftwareSerial zigbee(2, 3); //RX TX

void iot_send(String text);

char inchar;

# define D_buzzer 7

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  lcd.begin(16, 2);
  zigbee.begin(9600);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("CORPORATION");
  lcd.setCursor(5, 1);
  lcd.print("SECTION");
  digitalWrite(D_buzzer, LOW);
  pinMode(D_buzzer, OUTPUT);
}

void loop() {

  while (Serial.available() > 0)
  {
    inchar = (char)Serial.read();
    Serial.println(inchar);
    switch (inchar)
    {
      case'A':
        digitalWrite(D_buzzer, HIGH);
        delay(2000);
        digitalWrite(D_buzzer, LOW);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("HIGH TEMPERATURE");
        iot_send("*HIGH TEMPERATURE#");
        break;

      case'B':
        digitalWrite(D_buzzer, HIGH);
         delay(2000);
        digitalWrite(D_buzzer, LOW);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("METHANE DETECTED");
        iot_send("*METHANE DETECTED#");
        break;

      case'C':
        digitalWrite(D_buzzer, HIGH);
        lcd.clear();
         delay(2000);
        digitalWrite(D_buzzer, LOW);
        lcd.setCursor(0, 1);
        lcd.print("DRAINAGE FULL");
        iot_send("*DRAINAGE FULL#");
        break;

      case'D':
        digitalWrite(D_buzzer, HIGH);
         delay(2000);
        digitalWrite(D_buzzer, LOW);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("DRAINAGE OPEN");
        iot_send("*DRAINAGE OPEN#");
        break;

      case'E':
        digitalWrite(D_buzzer, HIGH);
         delay(2000);
        digitalWrite(D_buzzer, LOW);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("DRAINAGE BLOCKED");
        iot_send("*DRAINAGE BLOCKED#");
        break;
    }
  }
  delay(1000);
}

void iot_send(String text)
{
  for (int i = 0; i < text.length(); i++)
  {
    Serial.write(text[i]);
  }
  delay(3000);
}
