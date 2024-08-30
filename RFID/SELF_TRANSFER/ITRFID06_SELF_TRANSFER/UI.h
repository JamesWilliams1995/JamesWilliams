#ifndef UI_H
#define UI_H
#include"lcd.h"
#include"Arduino.h"
#include"String.h"
#include"gsm.h"
#include"keypad.h"
#include"fingerenroll.h"
#include"eeprom.h"
#include"ser.h"
#define buz A9

volatile unsigned long transfer_amount = 0;
int from_bank = 0;
int to_bank = 0;
enum {
  NOT_REGESTERED = 0,
  REGISTRED = 1,

};
void thankyou();

int ph_no = 1;
volatile char hcase, bcase, rcase;
unsigned volatile int bb, rb;
const char bname[6][17] = {"1 SBI", "2 IOB", "3 IB", "4 HDFC", "5 FR", "6 PH"};
const char regbank[3][17] = {"1 ADD", "2 DEL", "* CANCEL"};
volatile int reg_bank[4] = { NOT_REGESTERED,  NOT_REGESTERED, NOT_REGESTERED,  NOT_REGESTERED};
volatile unsigned long int dep_amount = 0;
char d_amount[5] = {'0', '0', '0', '0', '0'};
volatile unsigned long int account[4] = {0, 0, 0, 0};
char barray[50] = {};
char carray[50] = {};
extern volatile char key_value;
extern volatile int rfidno;
extern int mob_number[2][11];
int mob[10] = {};
void mob_reg();

void dep(char hcase, int b);
void reg(char hcase, int b);

void ui(char k)
{
  hcase = k;
  switch (k)
  {
    case '1':
    case '2':
    case '4':
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        sprintf(barray, "%s", bname[0]);
        lcd.print(barray);
        lcd.setCursor(9, 0);
        sprintf(barray, "%s", bname[1]);
        lcd.print(barray);
        lcd.setCursor(0, 1);
        sprintf(barray, "%s", bname[2]);
        lcd.print(barray);
        lcd.setCursor(9, 1);
        sprintf(barray, "%s", bname[3]);
        lcd.print(barray);
        key_value = 'x';
        while (key() == 'x');
        while (key() != 'x')
        {
          bcase = key();
          if ((bcase == '1') && ((reg_bank[0]) == REGISTRED))
            bb = 0;
          else if ((bcase == '2') && ((reg_bank[1]) == REGISTRED))
            bb = 1;
          else if ((bcase == '3') && ((reg_bank[2]) == REGISTRED))
            bb = 2;
          else if ((bcase == '4') && ((reg_bank[3]) == REGISTRED))
            bb = 3;
          else if (bcase == '5')
          {
            finger_enroll();
            break;
          }
          else
          {
            key_value = 'x';
            if (hcase != '3')
            {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("PLS REG BANK");
              delay(1000);
            }
            else
            {
              key_value = 'x';
              while (key() == 'x');
              while (key() != 'x')
              {
                if (key() == '1') {
                  rb = 0;
                  dep(hcase, rb);
                }
                if (key() == '2') {
                  rb = 1;
                  dep(hcase, rb);
                }
                if (key() == '3') {
                  rb = 2;
                  dep(hcase, rb);
                }
                if (key() == '4')
                {
                  rb = 3;
                  dep(hcase, rb);
                }
              }
            }
            break;
          }
          if (hcase == '1')
          {
            dep(hcase, bb);
            break;
          }
          if (hcase == '2')
          {
            dep(hcase, bb);
            break;
          }
          if (hcase == '3')
          {
            dep(hcase, bb);
            break;
          }
          if (hcase == '4')
          {
            dep(hcase, bb);
            break;
          }
          break;
        }
        break;
      }
    case '3':
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        sprintf(barray, "%s", bname[0]);
        lcd.print(barray);
        lcd.setCursor(6, 0);
        sprintf(barray, "%s", bname[1]);
        lcd.print(barray);
        lcd.setCursor(12, 0);
        sprintf(barray, "%s", bname[2]);
        lcd.print(barray);
        lcd.setCursor(0, 1);
        sprintf(barray, "%s", bname[3]);
        lcd.print(barray);
        lcd.setCursor(7, 1);
        sprintf(barray, "%s", bname[4]);
        lcd.print(barray);
        lcd.setCursor(12, 1);
        sprintf(barray, "%s", bname[5]);
        lcd.print(barray);

        key_value = 'x';
        while (key() == 'x');
        while (key() != 'x')
        {
          bcase = key();
          if ((bcase == '1') && ((reg_bank[0]) == 1))
            bb = 0;
          else if ((bcase == '2') && ((reg_bank[1]) == 1))
            bb = 1;
          else if ((bcase == '3') && ((reg_bank[2]) == 1))
            bb = 2;
          else if ((bcase == '4') && ((reg_bank[3]) == 1))
            bb = 3;
          else if (bcase == '5')
          {
            finger_enroll();
            break;
          }
          else if (bcase == '6')
          {
            mob_reg();
            break;
          }
          else if (bcase == '*')
          {
            break;
          }
          else
          {
            key_value = 'x';
            if (hcase != '3')
            {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("PLS REG BANK");
              delay(1000);
            }
            else
            {
              key_value = 'x';
              while (key() == 'x');
              while (key() != 'x')
              {
                if (key() == '1') {
                  rb = 0;
                  dep(hcase, rb);
                }
                if (key() == '2') {
                  rb = 1;
                  dep(hcase, rb);
                }
                if (key() == '3') {
                  rb = 2;
                  dep(hcase, rb);
                }
                if (key() == '4')
                {
                  rb = 3;
                  dep(hcase, rb);
                }
              }
            }
            break;
          }
          if (hcase == '1')
          {
            dep(hcase, bb);
            break;
          }
          if (hcase == '2')
          {
            dep(hcase, bb);
            break;
          }
          if (hcase == '3')
          {
            dep(hcase, bb);
            break;
          }
          if (hcase == '4')
          {
            dep(hcase, bb);
            break;
          }
          break;
        }
        break;
      }
    default: {
        break;
      }

  }

}


void mob_reg()
{

re_mob:
  key_value = 'x';
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ENTER MOB NO:");
  lcd.setCursor(0, 1);
  for (int i = 0; i < 10; i++)
  {
    while (key() == 'x');
    if (key() == '#')
    {
      goto re_mob;
    } if (key() == '*')
    {
      break;
    }
    lcd.setCursor(i, 1);
    lcd.print(key());
    mob[i] = (key() - '0');
    key_value = 'x';
    Serial.print(mob[i]);
  }


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SENDING OTP..");
  unsigned int otp = random(10000 - 99999);
  Serial.println("OTP:" + String(otp));
  send_sms(mob, "OTP:", String(otp));
  unsigned int otp_check = 0;
  char otp_array[5] = {'0', '0', '0', '0', '0'};

re_otp:
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ENTER OTP:");

  for (int i = 0; i < 5; i++)
  {
    key_value = 'x';
    while (key() == 'x');

    if (key() == '#')
    {
      goto re_otp;
    } if (key() == '*')
    {
      break;
    }
    lcd.setCursor(i, 1);
    lcd.print(key());
    otp_array[i] = (key());
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("checking..");
  // otp_check = atoi(otp_array);
  sscanf(otp_array, "%d", &otp_check);
  Serial.println("OTP CHECk:" + String(otp_check));
  if (otp == otp_check)
  {
    lcd.setCursor(0, 1);
    lcd.print("UPDATED..");
    for (int i = 0; i < 10; i++)
      EEPROM.write(i + 200, mob[i]);
    delay(2000);
    if (EEPROM.read(1000) == 1) {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("RE LOGIN..");
      wdt_enable(WDTO_2S);
      while (1);
    }
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WRONG OTP");
    lcd.setCursor(0, 1);
    lcd.print("RE LOGIN..");
    wdt_enable(WDTO_2S);
    while (1);
  }
}
void dep(char hcase, int b)
{
  switch (hcase)
  {
    case '1':   // deposit
      {
dep: key_value = 'x';

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DEPOSIT in X 100");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        sprintf(barray, "%s", bname[b]);
        lcd.print(barray);
        lcd.setCursor(8, 0);
        lcd.print("DEPOSIT");
        lcd.setCursor(0, 1);
        lcd.print("AMOUNT:");
        lcd.setCursor(7, 1);
         digitalWrite(A9 , HIGH);
        for (int i = 8, j = 0; i < 13, j < 5; i++, j++)
        {
          lcd.setCursor(i, 1);
          while (key() == 'x');
          lcd.print(key());
          d_amount[j] = key();
          if (key() == '*')
          {
            key_value = 'x';
            break;
          }
          key_value = 'x';
        }

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("BALANCE:");
        lcd.setCursor(0, 1);
        dep_amount = atoi(d_amount);
        if ((dep_amount % 100 == 0) && (dep_amount <= 25000) && ((account[b] + dep_amount) <= 25000))
        {
          account[b] +=  dep_amount;
          lcd.print(account[b]);
          EEPROM.write((b + 10) * 10, (account[b] / 100));
          sprintf(barray, "DEP RS:%d", dep_amount);
          sprintf(carray, "BAL RS:%d", account[b]);
          myservo.write(180);
          send_sms(mob, barray, carray);
          delay(1000);
          myservo.write(0);
        }
        else
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("pls enter crct");
          lcd.setCursor(0, 1);
          lcd.print("Denomination");
          delay(2000);
          goto dep;
        }
        break;
      }
    case '2':  // withdraw
      {
wtd:
        key_value = 'x';
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WDW IN X 100");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        sprintf(barray, "%s", bname[b]);
        lcd.print(barray);
        lcd.setCursor(8, 0);
        lcd.print("WDRW");
        lcd.setCursor(0, 1);
        lcd.print("AMOUNT:");
         digitalWrite(A9 , HIGH);
        for (int i = 8, j = 0; i < 13, j < 5; i++, j++)
        {
          lcd.setCursor(i, 1);
          while (key() == 'x');
          lcd.print(key());
          d_amount[j] = key();
          if (key() == '*')
          {
            key_value = 'x';
            break;
          }
          key_value = 'x';
        }
        dep_amount = (atoi(d_amount));

        if (dep_amount > account[b])
        {
          key_value = 'x';
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("BAL INSUFFICIENT");
          lcd.setCursor(0, 1);
          lcd.print("BAL:");
          lcd.setCursor(4, 1);
          lcd.print(account[b]);
          delay(1000);
          goto wtd;
        }
        if (dep_amount <= account[b]) {
          if ((dep_amount % 100 == 0) && (dep_amount <= 25000))
          {
            key_value = 'x';
            account[b] =  account[b] - dep_amount ;

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("WDRW:");
            lcd.setCursor(6, 0);
            sprintf(barray, "%d", dep_amount);
            lcd.print(barray);
            lcd.setCursor(0, 1);
            lcd.print("BAL:");
            lcd.setCursor(5, 1);
            lcd.print(account[b]);
            EEPROM.write((b + 10) * 10, (account[b] / 100));
            sprintf(carray, "WTD RS:%d", dep_amount);
            sprintf(barray, "BAL RS:%d", account[b]);
            myservo.write(180);
            send_sms(mob, barray, carray);
            myservo.write(0);
             digitalWrite(A9 , HIGH);
          }
          else
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("pls enter crct");
            lcd.setCursor(0, 1);
            lcd.print("Denomination");
            delay(2000);
            goto wtd;
          }
        }
        break;
      }
    case '3':  // reg
      {
        key_value = 'x';
        reg(hcase, b);
      }
      break;

    case '4':  // bal
      {
        key_value = 'x';
        lcd.clear();
        lcd.setCursor(0, 0);
        sprintf(barray, "%s", bname[b]);
        lcd.print(barray);
        lcd.setCursor(8, 0);
        lcd.print("BAL");
        lcd.setCursor(0, 1);
        lcd.print("AMOUNT:");
        lcd.setCursor(7, 1);
        lcd.print(account[b]);
        sprintf(barray, "%d", account[b]);
        from_bank = b;
        send_sms(mob, barray, "THANK YOU");
re:     key_value = 'x';
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("TRANSFER MONEY");
        lcd.setCursor(0, 1);
        lcd.print("1.YES  2.NO");
        do
        {
          key();
        }
        while (key_value == 'x');
        if (key_value == '2')
        {
          key_value = 'x';
          break;
        }
        if (key_value == '1')
        {
          key_value = 'x';
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("PLEASE SELECT");
          lcd.setCursor(0, 1);
          lcd.print("RECEIVE ACCOUNT");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          sprintf(barray, "%s", bname[0]);
          lcd.print(barray);
          lcd.setCursor(9, 0);
          sprintf(barray, "%s", bname[1]);
          lcd.print(barray);
          lcd.setCursor(0, 1);
          sprintf(barray, "%s", bname[2]);
          lcd.print(barray);
          lcd.setCursor(9, 1);
          sprintf(barray, "%s", bname[3]);
          lcd.print(barray);


          key_value = 'x';
          do
          {
            key();
          }
          while (key_value == 'x');
          to_bank = key_value - '0';
          to_bank -= 1;

          if ((to_bank < 4) && (to_bank != from_bank) && ((reg_bank[to_bank]) == 1))
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            sprintf(barray, "%s", bname[to_bank]);
            lcd.print(barray);
            lcd.setCursor(8, 0);
            lcd.print("DEPOSIT");
            lcd.setCursor(0, 1);
            lcd.print("AMOUNT:");
            lcd.setCursor(7, 1);
            key_value = 'x';
            for (int i = 8, j = 0; i < 13, j < 5; i++, j++)
            {
              lcd.setCursor(i, 1);
              while (key() == 'x');
              lcd.print(key());
              d_amount[j] = key();
              if (key() == '*')
              {
                key_value = 'x';
                break;
              }
              key_value = 'x';
            }

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("BALANCE:");
            lcd.setCursor(0, 1);
            dep_amount = atoi(d_amount);
            if (dep_amount <= account[from_bank]) {
              if ((dep_amount % 100 == 0) && (dep_amount <= 25000) && ((account[to_bank] + dep_amount) <= 25000))
              {
                account[from_bank] -= dep_amount;
                EEPROM.write((from_bank + 10) * 10, (account[from_bank] / 100));
                account[to_bank] +=  dep_amount;
                lcd.print(account[to_bank]);
                EEPROM.write(((to_bank) + 10) * 10, (account[to_bank] / 100));
                sprintf(barray, "DEP RS:%d", dep_amount);
                sprintf(carray, "BAL RS:%d", account[to_bank]);
                send_sms(mob, barray, carray);

                myservo.write(180);
                lcd.clear();
                lcd.setCursor(0, 0);
                sprintf(barray, "%s", bname[b]);
                lcd.print(barray);
                lcd.setCursor(8, 0);
                lcd.print("BAL");
                lcd.setCursor(0, 1);
                lcd.print("AMOUNT:");
                lcd.setCursor(7, 1);
                lcd.print(account[from_bank]);
                delay(2000);
                lcd.clear();
                lcd.setCursor(0, 0);
                sprintf(barray, "%s", bname[to_bank]);
                lcd.print(barray);
                lcd.setCursor(8, 0);
                lcd.print("BAL");
                lcd.setCursor(0, 1);
                lcd.print("AMOUNT:");
                lcd.setCursor(7, 1);
                lcd.print(account[to_bank]);
                delay(2000);
                myservo.write(0);
                key_value = 'x';
              }
              else
              {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("pls enter crct");
                lcd.setCursor(0, 1);
                lcd.print("Denomination");
                delay(2000); key_value = 'x';
                goto re;
              }
            }
            else
            {
              lcd.clear();
              key_value = 'x';
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("BAL INSUFFICIENT");
              lcd.setCursor(0, 1);
              lcd.print("BAL:");
              lcd.setCursor(4, 1);
              lcd.print(account[from_bank]);
             
              delay(2000); key_value = 'x';
              goto re;
            }
          }
          else
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("WRONG SELECT"); key_value = 'x';
            delay(2000);
            goto re;
          }

        }
        break;

      }
    default: {
        key_value = 'x';
        break;
      }
  }
}

void reg(char hcase, int b)
{
  switch (b)
  {
    case 0:
    case 1:
    case 2:
    case 3:
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        sprintf(barray, "%s", regbank[0]);
        lcd.print(barray);
        lcd.setCursor(6, 0);
        sprintf(barray, "%s", regbank[1]);
        lcd.print(barray);
        lcd.setCursor(0, 1);
        sprintf(barray, "%s", regbank[2]);
        lcd.print(barray);
        key_value = 'x';
        while (key() == 'x');
        while (key() != 'x')
        {
          rcase = key();
          if (rcase == '1') {
            key_value = 'x';
            reg_bank[b] = 1;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(bname[b]);
            lcd.setCursor(0, 1);
            lcd.print("REG SUCCESS");
            EEPROM.write(b, 1);
            Serial.println(b);
            Serial.println(EEPROM.read(b));
            sprintf(barray, "REG SUCCESSFULLY %s", bname[b]);
            send_sms(mob, barray, "THANK YOU");
            break;
          }
          if (rcase == '2')
          {
            key_value = 'x';
            reg_bank[b] = 0;
            EEPROM.write(b, 0);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(bname[b]);
            lcd.setCursor(0, 1);
            lcd.print("REMOVED");
            sprintf(barray, "REMOVED  %s", bname[b]);
            send_sms(mob, barray, "THANK YOU");
            break;
          }
          if (key() == '*')
          {
            key_value = 'x';
            break;
          }
        }
        break;
      }
    default: {
        break;
      }
  }
}
#endif
