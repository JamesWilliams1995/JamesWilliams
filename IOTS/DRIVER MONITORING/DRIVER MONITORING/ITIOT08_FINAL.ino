#include "lcd.h"
#include "gsm.h"
#include "ss.h"
#include "iot.h"
#include <ultrasonic.h>
ULTRASONIC U1;
//#include<LiquidCrystal.h>
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

#define D_vib 2
#define D_triger A0
#define D_echo A1
#define D_eyeblink 3
#define D_gas 5
#define D_irsensor 4

 0.
             
#define motor_positive 6  //motor
#define motor_negative 7
#define D_buzzer A2

bool crash_flag = false;

int value = 60000;
int eye_count = 0;
bool eye_flag = false;

int gas_value, cm;

int rpm_read = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(9600);
  lcd.begin(16, 2);  //lcd initializing
  U1.begin(D_triger, D_echo);  //trig echo
  attachInterrupt(digitalPinToInterrupt(D_vib), crash_ISR, RISING); // attaching the interrupt for vibration
  attachInterrupt(digitalPinToInterrupt(D_eyeblink), eye_ISR, RISING); // attaching the interrupt for vibration
  pinMode(D_eyeblink, INPUT);
  pinMode(D_gas, INPUT);
  pinMode(D_irsensor, INPUT);

  digitalWrite(motor_positive, HIGH);
  digitalWrite(motor_negative, LOW);
  pinMode(motor_positive, OUTPUT);
  pinMode(motor_negative, OUTPUT);
  digitalWrite(D_buzzer, LOW);
  pinMode(D_buzzer, OUTPUT);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DRIVER");
  lcd.setCursor(0, 1);
  lcd.print("MONITORING");
  delay(1000);
  lcd.clear();
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = value;              // preload timer
  TCCR1B |= (1 << CS10) | (1 << CS12);  // 1024 prescaler
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt I
  interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  cm = U1.ultra();
  gas_value = digitalRead(D_gas);
  Serial.println(cm);
  Serial.print(gas_value);
  lcd.setCursor(0, 1);
  lcd.print("D:");
  lcd.setCursor(2, 1);
  lcd.print(cm);
  if (crash_flag == true)
  {
    crash_flag = false;
    digitalWrite(motor_positive, LOW);
    digitalWrite(motor_negative, LOW);
    gsm("8189988347", "ACCIDENT");
    Serial.println("accident");
    lcd.setCursor(0, 0);
    lcd.print("ACCIDENT");
    iot_send("*ACCIDENT#");
  }
  else
  {
    Serial.println("NORMAL");
    lcd.setCursor(0, 0);
    lcd.print("NORMAL");
  }
  if (cm < 40)
  {
    Serial.println("object detected");
    analogWrite(motor_positive, 100);
    digitalWrite(motor_negative, LOW);
    gsm("8189988347", "ACCIDENT");
  }
  if (eye_flag == true)
  {
    eye_flag = false;
    digitalWrite(motor_positive, LOW);
    digitalWrite(motor_negative, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("EYE CLOSE");
    digitalWrite(D_buzzer, HIGH);
    iot_send("*Eye closed#");
    gsm("818998347", "drowsiness detected..");
  }
  else
  {
    digitalWrite(D_buzzer, LOW);
  }

  if (gas_value == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ALCHOHOL CONSUMED");
    digitalWrite(D_buzzer, HIGH);
    iot_send("*ALCHOHOL CONSUMED#");
    Serial.print("*ALCHOHOL CONSUMED#");
    gsm("818998347", "alchol detected..");
  }
  else
  {
    digitalWrite(D_buzzer, LOW);
  }
  speed_count();
  delay(1000);
}

void crash_ISR(void)
{
  crash_flag = true;
}

void eye_ISR(void)
{
  if (digitalRead(D_eyeblink) == 0)
  {
    Serial.println("eye:" + String(eye_count));
    if (eye_count > 3)
    {
      eye_flag = true;
    }

    eye_count++;
  }
  else
  {
    eye_flag = false;
    eye_count = 0;
  }
}

ISR(TIMER1_OVF_vect)
{
  TCNT1 = value;
  eye_ISR();
}

void speed_count(void)
{
  while (digitalRead(D_irsensor) == 1);
  unsigned long temp = millis();
  while (millis() < (temp + 5000))
  {
    if (digitalRead(D_irsensor) == 0)
    {
      rpm_read = rpm_read + 1;
      while (digitalRead(D_irsensor) == 0);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("RPM:");
      lcd.setCursor(14, 0);
      lcd.print(rpm_read);
    }
  }
  rpm_read = rpm_read * 12;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RPM:");
  lcd.setCursor(4, 0);
  lcd.print(rpm_read);
  iot_send("@" + String(rpm_read) + "#");
  rpm_read = 0;
}
