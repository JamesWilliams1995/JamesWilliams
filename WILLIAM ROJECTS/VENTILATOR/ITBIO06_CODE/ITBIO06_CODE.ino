/***************************************************************
  TITLE :M000287-2
  DATE  :03.02.2022
  AUTHOR:R.SARAVANAN
  LOG   :v.0.1
****************************************************************/

/********************HEADER FILES*******************************/
#include"global.h"
#include"lcd.h"
#include"spo2.h"
#include"keypad.h"
#include"temp.h"
#include"resp.h"
#include"iot.h"
#include <avr/wdt.h>
/***************************************************************/

/**********************FUNCTION DECLRATION***********************/
void motor(void);
void F_lcd_update(void);
void o2(void);
void Temp_state(void);
void resp_state(void);
void iott(String s);
/****************************************************************/

void setup()
{
  wdt_disable();
  key_def();
  digitalWrite(D_buzzer, LOW);
  digitalWrite(D_relay1, LOW);
  digitalWrite(D_relay2, LOW);
  Serial.begin(9600);//BAUD RATE
  Serial1.begin(9600); //IOT
  mlx.begin();
  digitalWrite(D_buzzer, LOW);
  pinMode(D_motor_p, OUTPUT);
  pinMode(D_motor_n, OUTPUT);
  pinMode(D_buzzer, OUTPUT);
  pinMode(D_relay1, OUTPUT);
  pinMode(D_relay2, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, F_resp, RISING);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("PORTABALE");
  lcd.setCursor(3, 1);
  lcd.print("VENTILATOR");
  Temp_state();
  delay(2000);
  iott("@" + String(TempF) + "#");
  delay(2000);
  iott("$0#");
  lcd.clear();
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = value;              // preload timer
  TCCR1B |= (1 << CS10) | (1 << CS12);  // 1024 prescaler
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt I
  interrupts();
}
void loop()
{
  motor();
  F_o2();
  Temp_state();
  resp_state();

  if ((spo2 < 95) && (spo2 > 10))
    digitalWrite(D_buzzer, HIGH);

  //  if (TempF >= 90)
  //    digitalWrite(D_buzzer, !digitalRead(D_buzzer));
  //

}
void F_lcd_update(void)
{
  lcd.setCursor(0, 0);
  lcd.print("O2:");
  lcd.setCursor(6, 0);
  lcd.print("%");
  lcd.setCursor(9, 0);
  lcd.print("RES:");
  lcd.setCursor(13, 0);
  lcd.print(resp);
  lcd.setCursor(0, 1);
  lcd.print("LVL:");
  lcd.setCursor(4, 1);
  lcd.print(LVL);
  lcd.setCursor(9, 1);
  lcd.print("T:");
  lcd.setCursor(11, 1);
  lcd.print(TempF);
  lcd.setCursor(14, 1);
  lcd.print("'F");

}
ISR(TIMER1_OVF_vect)
{
  TCNT1 = value;
  F_keypad();
  F_lcd_update();

}
void F_keypad(void)
{
  //Serial.println(Key_value);
  Key_press();
  if (Key_value == '5')
  {

    G_O2_flag = true;
    digitalWrite(D_motor_p, LOW);
    digitalWrite(D_motor_n, LOW);
    Key_value = 'x';
  }
  if (Key_value == '8')
  {
    Serial.println("reset");
    wdt_enable(WDTO_15MS);
    //wdt_enable(WDTO_4S);
    while (1);
  }
  if (Key_value == '1')
  {
    motor_p = 1;
    d_value_f = 600;
    d_value_r = 610;
    LVL = "1";
    a = "68";
    iott("*LVL1#"); Key_value = 'x';
    iott("@" + String(TempF) + "#");
  }
  if (Key_value == '2')
  {
    motor_p = 1;
    d_value_f = 1200;
    d_value_r = 1210;
    a = "65";
    LVL = "2";
    iott("*LVL2#"); Key_value = 'x'; iott("@" + String(TempF) + "#");
  }
  if (Key_value == '3')
  {
    motor_p = 1;
    d_value_f = 1800;
    d_value_r = 1810;
    a = "62";
    LVL = "3";
    iott("*LVL3#");
    Key_value = 'x';
    iott("@" + String(TempF) + "#");
  }
  if (Key_value == '0')
  {
    motor_p = 0;
    a = "00";
    LVL = "0"; Key_value = 'x';
    iott("*OFF#");
  }

}

void F_for(void)
{
  digitalWrite(D_motor_p, motor_p);
  digitalWrite(D_motor_n, LOW);
}
void F_delay_f(void)
{
  delay(d_value_f);
}
void F_rev(void)
{
  digitalWrite(D_motor_p, LOW);
  digitalWrite(D_motor_n, motor_p);
}
void F_delay_r(void)
{
  delay(d_value_r);
}

void F_stop(void)
{
  digitalWrite(D_motor_p, LOW);
  digitalWrite(D_motor_n, LOW);
  delay(1000);
}

void F_o2(void)
{
  if (G_O2_flag == true)
  {
    o2();
    G_O2_flag = false;
    delay(2000);
    Serial.println(G_O2_flag);
    delay(2000);
    Key_value = '8';
  }
}

void motor(void)
{
  F_for();
  F_delay_f();
  F_stop();
  F_rev();
  F_delay_r();
  F_stop();
}

void serialEvent1(void)
{
  while (Serial1.available() > 0)
  {
    char d = (char)Serial1.read();
    switch (d)
    {
      case'0':
        {
          Serial.println("iot 1");
          Key_value = '0';
          break;
        }

      case'1':
        {
          Serial.println("iot 1");
          Key_value = '1';
          break;
        }
      case'2':
        {
          Key_value = '2';
          break;
        }
      case'3':
        {
          Key_value = '3';
          break;
        }
      case'5':
        {
          Serial.println("iot 1");
          Key_value = '5';
          break;
        }
      case'8':
        {
          Serial.println("iot 1");
          Key_value = '8';
          break;
        }
    }
  }
}
void F_resp()
{
  r_flag = true;
}
