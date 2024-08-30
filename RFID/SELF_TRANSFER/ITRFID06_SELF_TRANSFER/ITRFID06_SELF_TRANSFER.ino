#include <avr/wdt.h>
#include"eeprom.h"
#include"rfid.h"
#include"lcd.h"
#include"keypad.h"
#include"UI.h"
#include"gsm.h"
#include"fingerenroll.h"
#include"fingermatch.h"
#include"ser.h"
extern volatile char key_value;
extern volatile int rfidno;
char harray[LCD_MAX_LENGTH + 1] = {};
const char hname[5][LCD_MAX_LENGTH + 1] = {"1 DEP", "2 WID", "3 REG", "4 BAL"};
void rfid_check();
int f_id = 0;
bool finger_ok = false;
int card, fno = 0;
void ff();

void setup() {
  Serial.begin(9600);
  wdt_disable();
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  pinMode(A9, OUTPUT);
  digitalWrite(A9 , LOW);
  myservo.attach(3);
  myservo.write(90);
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.print("WELCOME TO");
  lcd.setCursor(3, 1);
  lcd.print("SMART ATM");
  pinMode(A8, INPUT_PULLUP);
  pinMode(A9, OUTPUT);
  digitalWrite(A9, LOW);
  delay(2000);
  myservo.write(0);
  lcd.clear();
  if (digitalRead(A8) == 0)
    eeprom_clear();
  validate();
  keypad_init();
  finger_init();
  delay(1000);
  rfid_check();
  delay(2000);
}
void loop() {

  //  Serial.println(key());
  //  delay(1000);
  if (key() == 'x') {
    home_screen();
  }
  if (key() == '#') {
    thankyou();
  }
  ui(key_value);
  delay(100);

}
void home_screen()
{
  do {
    key_value = 'x';
    lcd.clear();
    lcd.setCursor(0, 0);
    sprintf(harray, "%s", hname[0]);
    lcd.print(harray);
    lcd.setCursor(9, 0);
    sprintf(harray, "%s", hname[1]);
    lcd.print(harray);
    lcd.setCursor(0, 1);
    sprintf(harray, "%s", hname[2]);
    lcd.print(harray);
    lcd.setCursor(9, 1);
    sprintf(harray, "%s", hname[3]);
    lcd.print(harray);
    delay(10);

  }
  while (key() != 'x');
}

void rfid_check()
{
  lcd.setCursor(0, 0);
  lcd.print(" PLACE ATM CARD");
  do {
    rfid();
  }
  while (rfid() == 0);
  if (rfid() == 1)
  {
    if (EEPROM.read(1000) == NOT_REGESTERED)
    {
      mob_reg();
      ff();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("REG SUCESSFULL..");
      lcd.setCursor(0, 1);
      lcd.print("RE LOGIN..");
      wdt_enable(WDTO_2S);
      while (1);
    }
    if (EEPROM.read(1000) == REGISTRED)
    {
      Serial.println("f_id");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("place finger");
      do {
        getFingerprintID();
      }
      while (f_id == 0);
      if (f_id == fno)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FINGER MATCHED");
        lcd.setCursor(0, 1);
        lcd.print("WELCOME");
        delay(2000);
        key_value = 'x';
      }
      else if (f_id != fno)
      {
        digitalWrite(buz, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("UN AUTHORIZED");
        send_sms(mob, "UN AUTHORIZED ACCESS", "THANK YOU");
        key_value = 'x';
        wdt_enable(WDTO_2S);
        while (1);
      }
    }
  }
}
