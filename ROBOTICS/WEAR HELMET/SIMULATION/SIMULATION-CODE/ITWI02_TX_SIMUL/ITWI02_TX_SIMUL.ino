#include "mic_sensor.h"
#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
/************PIN CONFIGURATION***************/

#define force_Sensor 7
#define gas_Sensor 6
#define mic_Sensor A0

/*************GLOBAL VARIABLES***************/

int force_value, gas_value;

/************FUNCTION DECLARATION************/

void freq_init();
double freq_read();
void Send(String s);

/********************************************/
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("    WELCOME    ");
  freq_init();
  pinMode(force_Sensor, INPUT_PULLUP);
  pinMode(gas_Sensor, INPUT);
  pinMode(mic_Sensor, INPUT);
  delay(100);
}

void loop()
{
  // put your main code here, to run repeatedly:
  force_value = digitalRead(force_Sensor);
  gas_value = digitalRead(gas_Sensor);
  freq_read();

  if (force_value == 1)
  {
    Serial.print('U');
//    Serial.println("Wear Helmet");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   WEAR HELMET   ");
    lcd.setCursor(0, 1);
    lcd.print("G:");
    lcd.setCursor(3, 1);
    lcd.print(gas_value);
    lcd.setCursor(5, 1);
    lcd.print("F:");
    lcd.print(force_value);
    lcd.setCursor(10, 1);
    lcd.print("M:");
    lcd.print(peak);
  }
  //no phonecall and alchohol consumed
  else if (force_value == 0 && gas_value == 0 && peak < 400)
  {
    Serial.print('W');
//        Serial.println("Alchohol Consumed");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    ALCHOHOL    ");
    lcd.setCursor(0, 1);
    lcd.print("G:");
    lcd.setCursor(3, 1);
    lcd.print(gas_value);
    lcd.setCursor(5, 1);
    lcd.print("F:");
    lcd.print(force_value);
    lcd.setCursor(10, 1);
    lcd.print("M:");
    lcd.print(peak);
  }
  //phonecall and no alchohol
  else if (force_value == 0 && gas_value == 1 && peak >= 400 && peak <= 700)
  {
    Serial.print('X');
//        Serial.println("Don't Speak call");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DON'T SPEAK CALL");
    lcd.setCursor(0, 1);
    lcd.print("G:");
    lcd.setCursor(3, 1);
    lcd.print(gas_value);
    lcd.setCursor(5, 1);
    lcd.print("F:");
    lcd.print(force_value);
    lcd.setCursor(10, 1);
    lcd.print("M:");
    lcd.print(peak);
  }
  //phonecall and alchohol consumed
  else if (force_value == 0 && gas_value == 0 && peak >= 400 && peak <= 700)
  {
    Serial.print('Y');
//        Serial.println("Alchohol consumed and Don't speak call");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" ALCHOHOL & CALL ");
    lcd.setCursor(0, 1);
    lcd.print("G:");
    lcd.setCursor(3, 1);
    lcd.print(gas_value);
    lcd.setCursor(5, 1);
    lcd.print("F:");
    lcd.print(force_value);
    lcd.setCursor(10, 1);
    lcd.print("M:");
    lcd.print(peak);

  }
  //All fine
  else if (force_value == 0 && gas_value == 1 && peak < 400)
  {
    Serial.print('Z');
//        Serial.println("All fine");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" HAPPY JOURNEY ");
    lcd.setCursor(0, 1);
    lcd.print("G:");
    lcd.setCursor(3, 1);
    lcd.print(gas_value);
    lcd.setCursor(5, 1);
    lcd.print("F:");
    lcd.print(force_value);
    lcd.setCursor(10, 1);
    lcd.print("M:");
    lcd.print(peak);
  }
  delay(100);
}

void Send(String s)
{
  for (int i = 0; i < s.length(); i++)
  {
    Serial.write(s[i]);
  }
}
