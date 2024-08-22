/**************************************************************/
//CODE : ITIOT02


/********************HEADER FILES*******************************/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include "global.h"
#include "heart.h"
#include "gsm.h"
#include "iot.h"

/***************************************************************/

/**********************FUNCTION DECLRATION***********************/

void F_buzzer_state(void);
void gsm(String number, String data);
void heart(void);
void E_BUTTON(void);
void HEART(void);
void Send(String c);
void iott(String s);

/***************************************************************/

void setup() {
  Serial.begin(9600); //zigbee
  Serial1.begin(9600); //iot
  Serial2.begin(9600); //gps
  Serial3.begin(9600); //gsm
  lcd.init();
  lcd.setBacklight( HIGH );
  pinMode(HEART_SENSOR, INPUT_PULLUP);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("WOMEN SAFETY");
  delay(1000);

}

void loop()
{

  int tog_switch = digitalRead(SWITCH_PIN);
  //  Serial.print(tog_switch);
  if (tog_switch == 0)
  {
    //    Serial.print("Button Mode");
    E_BUTTON();
  }
  else
  {
    //    Serial.print("Heart Rate Mode");
    HEART();
  }
}

void E_BUTTON(void)
{
  int button = digitalRead(BUTTON_PIN);
  if (button == LOW)
  {
    Serial.print('A');
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("EMERGENCY");
    iott("*EMERGENCY#");
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
    
    gsm("8189988347", "EMERGENCY");

  }
  else
  {
    //    Serial.println("Fine");
    Serial.println("B");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Fine");
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
  }
  delay(500);
}

void HEART(void)
{
  heart();
    Serial.println(G_i);
  
  if (G_i > 100)
  {
    Serial.print('C');
    //    Serial.println("Heart rate High");
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("EMERGENCY");
    iott("*EMERGENCY#");
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
    gsm("8189988347", "EMERGENCY");
  }
  else if ((G_i < 100) && (G_i > 60))
  {
    Serial.print('D');
    //    Serial.println("Heart rate Normal");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heart Rate Normal");
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, HIGH);


  }
  else if ((G_i < 60) && (G_i > 0))
  {
    //    Serial.println("Heart Rate Low");
    Serial.print('E');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heart Rate Low");
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, HIGH);

  }
  else if (G_i == 0)
  {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("PLACE FINGER");
    Serial.print('F');
    //    Serial.println("Place Finger");
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, HIGH);
  }
  delay(300);
}

void Send(String c)
{
  for (int i = 0; i < c.length(); i++)
  {
    Serial.write(c[i]);
  }
}
