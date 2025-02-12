
#include<Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#include"dht11.h"
#include "heart.h"
//#include "sd.h"
#include "Respiration.h"
#include "Rfid.h"
#include "iot.h"
#include "gsm.h"
#include "ss.h"
#include "global.h"
DHT dht;
void heart(void);
void Resp(void);
void setup () {
  // put your setup code here, to run once:

  Serial.begin(9600);
  ss.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(HEART_SENSOR, INPUT_PULLUP);
  pinMode(res, INPUT);
  Serial.print("HEALTH CONTROL");
  lcd.setCursor(2, 0);
  lcd.print("HEALTH CONTROL");


  pinMode(buz, OUTPUT);//buz
  digitalWrite(buz, LOW);//buz


}

void loop() {
  // put your main code here, to run repeatedly:
  //  sd();
  //rfid();

  dht.dht_read(A0);
  t = dht.temperature;
  t = (t * 1.8) + 32;
  Serial.println(t);
  Serial.print("temp:");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BT:");
  lcd.setCursor(3, 0);
  lcd.print(t);
  lcd.setCursor(10, 0);
  lcd.print("HB:");
  lcd.setCursor(13, 0);
  lcd.print( G_i);

  if (t < 95)
  {
    //rfid();
    Serial.println(F("NORMAL:"));
    Serial.print(t);
    lcd.setCursor(0, 1);
    lcd.print("Normal");
    iot_send("*" + String(t) + "#");

  }
  else
  {
    //    sd();
    //rfid();
    Serial.println(F("T-HIGH:"));
    Serial.println(t);
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("HIGH");
    digitalWrite(buz, HIGH);
    delay(1000);
    digitalWrite(buz, LOW);
   
    gsm("8189988347", "TEMP HIGH");
    iot_send("@" + String(t) + "#");

  }

  heart();

  if (G_i > 100)
  {
    Serial.print("HEART RATE:");
    Serial.print(G_i);
    iot_send("$" + String(G_i) + "#");

  }
  else
  {

    Serial.print("Heart beat is high");
    digitalWrite(buz, HIGH);
    //    gsm("8189988347", "HEART BEAT HIGH");
    iot_send("@" + String(G_i) + "#");

  }

  if (rfid() == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("https://io.adafru/");
    lcd.setCursor(0, 1);
    lcd.print("it.com/ITIOT13");
    gsm("8189988347", "https://https://io.adafruit.com/ITIOT13/dashboards/iot/");
    while (1);
  }

}
