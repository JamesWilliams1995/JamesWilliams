//#include "lcd.h"
#include "rtc.h"
#include "rfid.h"
#include<Wire.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

String Names[3] = {"Deva", "Arun", "Poovarasan"};
boolean slot[3] = {false, false, false};
int IRSensor[3] = {2, 3, 4};
int statusSensor[3];
String person;

int RLed[3] = {5, 7, 8};
int GLed[3] = {9, 10, 11};

//int i=0;
void setup()
{
  rtc_init();

  Serial.begin(9600);
  Serial1.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.clear();



  pinMode (IRSensor[0], INPUT);
  pinMode (IRSensor[1], INPUT);
  pinMode (IRSensor[2], INPUT);

  pinMode (RLed[0], OUTPUT);
  pinMode (RLed[1], OUTPUT);
  pinMode (RLed[2], OUTPUT);

  pinMode(GLed[0], OUTPUT);
  pinMode(GLed[1], OUTPUT);
  pinMode(GLed[2], OUTPUT);
  delay(1000);
}
void loop()
{

  rfid();
  if (rfid() == 1)
  {
    Serial.println(Names[0]);
    person == Names[0];
    lcd.setCursor(0, 0);
    lcd.print("Slot avaiability");
    lcd.setCursor(0, 1);
    lcd.print("0");
    delay(1000);
    lcd.clear();
  }
  else if (rfid() == 2)
  {
    Serial.println(Names[1]);
    person == Names[1];
    lcd.setCursor(0, 0);
    lcd.print("Slot avaiability");
    lcd.setCursor(8, 1);
    lcd.print("0");
    delay(1000);
    lcd.clear();


  }
  else if (rfid() == 3)
  {
    Serial.println(Names[2]);
    person == Names[2];
    lcd.setCursor(0, 0);
    lcd.print("Slot avaiability");
    lcd.setCursor(16, 1);
    lcd.print("0");
    delay(1000);
    lcd.clear();


  }

  if (slot[0] == false)
  {
    Serial.println("Slot1 is available");
    parking("*Slot1 is available#");
    lcd.setCursor(0, 0);
    lcd.print("Slot avaiability");
    lcd.setCursor(0, 1);
    lcd.print("1");


  }

  if (slot[1] == false)
  {
    Serial.println("Slot2 is available");
    parking("*Slot2 is available#");
    lcd.setCursor(0, 0);
    lcd.print("Slot avaiability");
    lcd.setCursor(8, 1);
    lcd.print("1");


  }



  if (slot[2] == false)
  {
    Serial.println("Slot3 is available");
    parking("*Slot3 is available#");
    lcd.setCursor(0, 0);
    lcd.print("Slot avaiability");
    lcd.setCursor(15, 1);
    lcd.print("1");

  }

  if (slot[0] == true && slot[1] == true && slot[2] == true)
    Serial.println("No slots available");

  //    Serial.print(person);
  //    Serial.print(" = RS. 200");



  statusSensor[0] = digitalRead(IRSensor[0]);
  statusSensor[1] = digitalRead(IRSensor[1]);
  statusSensor[2] = digitalRead(IRSensor[2]);

  for (int i = 0; i < 3; i++)
  {
    if (statusSensor[i] == 0)
    {
      Serial.print(i + 1);
      Serial.println(" : ");
      Serial.println(statusSensor[i]);

      digitalWrite(RLed[i], HIGH);
      digitalWrite(GLed[i], LOW);
      slot[i] = true;

    }
    else if (statusSensor[i] == 1)
    {
      Serial.print(i + 1);

      Serial.print(" : ");
      Serial.println(statusSensor[i]);
      digitalWrite(GLed[i], HIGH);
      digitalWrite(RLed[i], LOW);
      slot[i] = false;


    }
    

  }
  for (int i = 0; i < 3; i++)
  {
    if (slot[i] == true)
    {

      Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1000 milli seconds or 1 second
      Serial.println("AT+CMGS=\"+918189988347\"\r"); // Replace x with mobile number
      delay(1000);
      Serial.println(person); // Replace x with mobile number
      Serial.println(slot[i]);
      Serial.println("PARKING CHARGE= RS. 200");// The SMS text you want to send
      delay(1000);
      Serial.println((char)26);// ASCII code of CTRL+Z
      delay(2000);


    }
  }


  rtc_check();



  delay(1000);
}
void parking(String s)
{
  for (int i = 0; i < s.length(); i++)
  {
    Serial1.write(s[i]);

  }
  delay(3000);
}
