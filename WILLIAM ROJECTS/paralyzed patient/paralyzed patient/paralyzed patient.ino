#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);


#include "dht11.h"
#include "heart.h"
#include "gyro.h"
#include "gsm.h"
#include "iot.h"
#include "ss.h"
#define buz 3
bool gsm_flag = false;


DHT dht;
int t;
int r;
//int count6;
//int avg;

//void Resp(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(HEART_SENSOR, INPUT_PULLUP);
  pinMode(buz, OUTPUT);
  digitalWrite(buz, LOW);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("PATIENT");
  lcd.setCursor(0, 1);
  lcd.print("SUPPORT SYSTEM");
  delay(3000);
  Gsetup();
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
  dht.dht_read(5);
  t = dht.temperature;
  t = (t * 1.8) + 32;
  //  Serial.println(t);
  //  Serial.print("temp:");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEM:");
  lcd.print(t);
  lcd.setCursor(7, 0);
  lcd.print("HB:");
  lcd.print(G_i);
  iot_send("@" + String(t) + "#");
  iot_send("$" + String(G_i) + "#");
  if (t < 93)
  {
    //    lcd.setCursor(0, 1);
    //    lcd.print("NORMAL");
    digitalWrite(buz, LOW);

  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("T-HIGH");
    gsm("8099552677", "HEART BEAT HIGH");
    iot_send("*BODY TEMPERATURE HIGH#");
  }
  heart();
  if (G_i == 120)
  {
    G_i = 0;
  }
  if (G_i > 60 && G_i < 80 )
  {
    lcd.setCursor(0, 1);
    lcd.print("HFINE");
    digitalWrite(buz, LOW);
  }
  //  if ( G_i != 0 && G_i < 60 && G_i > 84)
  if (G_i > 0 && G_i < 60 )
  {
    lcd.setCursor(0, 1);
    lcd.print("HLOW");
    digitalWrite(buz, HIGH);
    if (gsm_flag == false) {
      gsm("8099552677", "HEART BEAT HIGH");
      gsm_flag = true;
    }
    iot_send("*HEART RATE ABNORMAL#");


  }
  Gloop();

  if (GYX >= 350 && GYX <= 360 )
  {
    lcd.setCursor(0, 1);
    lcd.print("STABLE");
    Serial.print("STOP");
  }

  if (GYX >= 10 && GYX <= 100)
  {
    Serial.println("NEED FOOD");
    lcd.setCursor(2, 1);
    lcd.print("I WANT FOOD");
    digitalWrite(buz, HIGH);
    gsm("8099552677", "I WANT FOOD");
    iot_send("*I WANT FOOD#");
  }

  if (GYX >= 260 && GYX <= 275)
  {
    Serial.println("NEED WATER");
    lcd.setCursor(2, 1);
    lcd.print("I WANT WATER");
    digitalWrite(buz, HIGH);
    gsm("8099552677", "I WANT WATER");
    iot_send("*I WANT WATER#");
  }
  if (GYX >= 330 && GYX <= 365)
  {
    Serial.println("NEED MDICINE");
    lcd.setCursor(2, 1);
    lcd.print("I NEED MADICINE");
    digitalWrite(buz, HIGH);
    gsm("8099552677", "I NEED MADICINE");
    iot_send("*I WANT MADICINE#");

  }
  if (GYX >= 180 && GYX <= 200)
  {
    Serial.println("WANT GO WASHROOM");
    lcd.setCursor(0, 1);
    lcd.print("WANT GO WASHROOM");
    digitalWrite(buz, HIGH);
    gsm("8099552677", "WANT GO WASHROOM");
    iot_send("*WANT GO WASHROOM#");
  }
}
