#ifndef UI_H
#define UI_H

#include "global.h"
#include "lcd.h"
#include "iotkeypad.h"
#include "ss.h"
#include "rfid.h"
#include "eeprom.h"
#include "iot.h"

/***********FUNTION DECLARATION***************/
void recharge(void);

void home_screen()
{
  switch (present_state)
  {
    case HOME:
      {
        digitalWrite(D_buzzer, LOW);
        card_amount = 0;
        rfidno = 0;
        if (ir_value1 == 0 || ir_value2 == 0)
        {
          key_value = 'x';
          iot_flag = true;
          present_state = CARD_READ;
        }
        break;
      }
    case CARD_READ:
      {
        lcd.clear();
        digitalWrite(D_buzzer, LOW);
        
        if (rfid() != 0)
        {
          card_amount = EEPROM.read(rfid());
          lcd.setCursor(0, 0);
          lcd.print("BAL:");
          lcd.setCursor(4, 0);
          lcd.print(card_amount * 100);
          lcd.setCursor(10, 0);
          lcd.print("EXIT:0");
          lcd.setCursor(0, 1);
          lcd.print("CHRGE:*");
          lcd.setCursor(8, 1);
          lcd.print("RECHRG:#");
          //          if (iot_flag == true)
          //          {
          iot_send("@" + String(card_amount * 100) + "#");
          //            iot_flag = false;
          //          }
        }
        else
        {
          lcd.setCursor(0, 0);
          lcd.print("READING ID.... ");
          rfidno = 0;
        }
//        Serial.print(rfidno);
//        Serial.print(key());
        switch (key())
        {
          case '#':
            key_value = 'x';
            iot_flag = true;
            present_state = MOBILE_RECHARGE;
            previous_state = CARD_READ;
            break;

          case '0':
            key_value = 'x';
            iot_flag = true;
            rfidno = 0;
            card_amount = 0;
            present_state = HOME;
            previous_state = HOME;
            break;

          case '*':
            key_value = 'x';
            iot_flag = true;
            present_state = CHARGING;
            previous_state = PAYMENT;
            break;
        }
        break;
      }
    case MOBILE_RECHARGE:
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PLS PAY AMOUNT");
        lcd.setCursor(10, 1);
        lcd.print("EXIT:#");
        lcd.setCursor(0, 1);
        lcd.print("RESET:*");
        if (iot_flag == true)
        {
          iot_send("*PLS PAY AMOUNT#");
          iot_flag = false;
        }

        switch (key())
        {
          case 'Q':
            key_value = 'x';
            iot_flag = true;
            recharge();
            break;
          case '*':
            key_value = 'x';
            iot_flag = true;
            eeprom_clear();
            card_amount = EEPROM.read(rfid());
            iot_send("@" + String(card_amount * 100) + "#");
            present_state = HOME;
            previous_state = HOME;
            break;
          case '#':
            key_value = 'x';
            iot_flag = true;
            present_state = CARD_READ;
            previous_state = HOME;
            break;
        }
        break;
      }
    case CHARGING:
      {
        switch (previous_state)
        {
          case PAYMENT:
            {
              if (iot_flag == true)
              {
                iot_send("*CHOOSE THE AMOUNT#");
                iot_flag = false;
              }
              switch (key())
              {
                case '1':
                  key_value = 'x';
                  iot_flag = true;
                  user_amount = 1;
                  break;
                case '2':
                  key_value = 'x';
                  iot_flag = true;
                  user_amount = 2;
                  break;
                case '3':
                  key_value = 'x';
                  iot_flag = true;
                  user_amount = 3;
                  break;
              }
              time_period = Min * user_amount;
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("CHS AMT:");
              lcd.setCursor(10, 0);
              lcd.print("1.100");
              lcd.setCursor(0, 1);
              lcd.print("2.200");
              lcd.setCursor(6, 1);
              lcd.print("3.300");
              if (user_amount > card_amount)
              {
                user_amount = 0;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("PLS RECHARGE OR");
                lcd.setCursor(0, 1);
                lcd.print("ENTER VALID AMT");
                //iot_send("*PLS RECHARGE OR ENTER VALID AMT#");
                present_state = CARD_READ;
              }
              else if (user_amount != 0 && user_amount <= card_amount)
              {
                user_amount = 0;
                present_state = CHARGING;
                previous_state = CARD_READ;
              }
              break;
            }

          case CARD_READ:
            {
              if ((time_period == 0) || (key() == '8'))
              {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("THANK YOU...");
                digitalWrite(D_relay_1, HIGH);
                digitalWrite(D_relay_2, HIGH);
                EEPROM.write(rfid(), card_amount);
                time_period = 0;
                slot1 = false;
                slot2 = false;
                for (int i = 0; i < 5; i++)
                {
                  digitalWrite(D_buzzer, HIGH);
                  delay(150);
                  digitalWrite(D_buzzer, LOW);
                  delay(150);
                }
                iot_send("*CHARGING COMPLETED THANKYOU#");
                iot_send("@" + String(card_amount * 100) + "#");
                present_state = HOME;
              }
              else if (time_period != 0 )
              {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("SLOT:");
                lcd.setCursor(15, 0);
                lcd.print("S");
                lcd.setCursor(0, 1);
                lcd.print("AMT:");
                lcd.setCursor(10, 1);
                lcd.print("8-STOP");

                if (ir_value1 == 0 && slot2 == false)
                {
                  slot1 = true;
                  slot2 = false;
                  digitalWrite(D_relay_1, LOW);
                  lcd.setCursor(5, 0);
                  lcd.print("1");
                  lcd.setCursor(7, 0);
                  lcd.print("ON");
                }

                if (ir_value2 == 0 && slot1 == false)
                {
                  slot1 = false;
                  slot2 = true;
                  digitalWrite(D_relay_2, LOW);
                  lcd.setCursor(5, 0);
                  lcd.print("2");
                  lcd.setCursor(7, 0);
                  lcd.print("ON");
                }

                if ((time_period % 60) == 0)
                {
                  card_amount--;
                }
                time_period--;
                lcd.setCursor(11, 0);
                lcd.print(time_period);
                lcd.setCursor(4, 1);
                lcd.print(card_amount * 100);
              }
              break;
            }
        }
        break;
      }
  }
}


void ev_charging()
{
  switch_value = digitalRead(D_switch);
  ir_value1 = digitalRead(D_irsensor_1);
  ir_value2 = digitalRead(D_irsensor_2);
  //Serial.println(switch_value);
  if (switch_value == 0)
  {
    if (ir_value1 == 0 || ir_value2 == 0 )
    {
      home_screen();
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("EXPECT VEHICLE");
      present_state = HOME;
    }
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TURN ON SWITCH");
    present_state = HOME;
  }
}


void recharge(void)
{
  int temp = EEPROM.read(rfid());
  temp = temp + MAX_AMOUNT;
  lcd.clear();
  if (temp <= RC_MAX_AMOUNT)
  {
    EEPROM.write(rfid(), temp);
    lcd.setCursor(0, 0);
    lcd.print("RC SUCCESS..");
    if (iot_flag == true) {
      iot_send("*RC SUCCESS..#");
      iot_flag = false;
    }
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("RC LIMIT REACHED..");
    if (iot_flag = true)
    {
      iot_send("*RC LIMIT REACHED..#");
      iot_flag = false;
    }
  }
  present_state = CARD_READ;
}

#endif
