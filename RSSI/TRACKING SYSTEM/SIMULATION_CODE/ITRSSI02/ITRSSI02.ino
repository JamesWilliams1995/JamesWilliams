#define motor_p A0
#define motor_n A1
#define vib 4
#define buz A2

char data = 'x';

boolean first_flag = false;
boolean second_flag = false;

#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("TRACKING SYSTEM");
  //Serial.print("TRACKING SYSTEM");
  pinMode (vib, INPUT_PULLUP);
  digitalWrite(motor_p, HIGH);
  digitalWrite(motor_n, LOW);
  digitalWrite(buz, LOW);//buz

  pinMode(motor_p, OUTPUT);
  pinMode(motor_n, OUTPUT);
  pinMode(buz, OUTPUT);//buz


}

void loop() {
  // put your main code here, to run repeatedly:
  int v = digitalRead(vib);
  if (v == 0) {
    digitalWrite (motor_p, LOW);
    digitalWrite (motor_n, LOW);
    Serial.print('B');
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("V:");
    lcd.print("ALARM");
    digitalWrite(buz, HIGH);
    delay(100);
    digitalWrite(buz, LOW);
  }

  if (Serial.available()) {
    data = Serial.read();
    //Serial.println(data);
  }

  //  Serial.println("hi hello");
  Serial.println(data);
  if (data == 'A')
  {
    first_flag = true;
    Serial.println("first time");
     lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WELCOME");
  }
  if  (first_flag == true && data == 'B' || data == 'C') {
    second_flag = true;
    Serial.println("second time");
  }
  if (second_flag == true && data == 'A')
  {
    digitalWrite(motor_p, LOW);
    digitalWrite(motor_n, LOW);
    Serial.write('A');
    Serial.println("sand theft");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SAND THEFT");
  }
  delay(100);
}
