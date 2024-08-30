#ifndef  KEYPAD_H
#define  KEYPAD_H

#define R0 2
#define R1 11
#define R2 4
#define R3 5
#define C0 6
#define C1 7
#define C2 8
#define C3 9
#define led 10

char KEY(void);
char keyValue = 'x';
int count = 0;
//char keyValue[];
String data = "1234";
String password = "";
void PSW(void)
{
  KEY();
  count = 0;
  //for (int i = 0; i < 4; i++) {
  while (keyValue == 'x') {
    //Serial.println("krish");
    if (KEY() != 'x') {
      password += KEY();
      count++;
//      Serial.println(KEY());
      lcd.setCursor(0, 0);
      lcd.print("ENTER OTP:"+password);
//      for (int i = 5; i < 9; i++)
//      {
//        lcd.setCursor(i, 0);
//        lcd.print(String(password(i)));
//      }
    }
    //delay(100);
    keyValue = 'x';
    if (count == 4) {
      break;
    }
    delay(100);

  }
  // }
//  Serial.println("PW:" + String(password));
//  //  lcd.setCursor(0, 0);
//  //  lcd.print("PASS:" + String(password));
//  if (data == password)
//  {
//    Serial.println("UnLocked");
//
//    lcd.setCursor(0, 1);
//    lcd.print("UNLOCKED DOOR");
//    delay(1000);
//  }
//  else
//  {
//    Serial.println("Locked");
//    lcd.setCursor(0, 1);
//    lcd.print("SENDING SMS    ");
//  }
}

char KEY(void) {

  digitalWrite(R0, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);

  if (digitalRead(C0) == LOW) {
    keyValue = '1';

  }
  if (digitalRead(C1) == LOW) {
    keyValue = '2';

  }
  if (digitalRead(C2) == LOW) {
    keyValue = '3';

  }
  if (digitalRead(C3) == LOW) {
    keyValue = 'A';

  }
  digitalWrite(R0, HIGH);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);

  if (digitalRead(C0) == LOW) {
    keyValue = '4';

  }
  if (digitalRead(C1) == LOW) {
    keyValue = '5';

  }
  if (digitalRead(C2) == LOW) {
    keyValue = '6';

  }
  if (digitalRead(C3) == LOW) {
    keyValue = 'B';

  }
  digitalWrite(R0, HIGH);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(R3, HIGH);

  if (digitalRead(C0) == LOW) {
    keyValue = '7';

  }
  if (digitalRead(C1) == LOW) {
    keyValue = '8';

  }
  if (digitalRead(C2) == LOW) {
    keyValue = '9';

  }
  if (digitalRead(C3) == LOW) {
    keyValue = 'C';

  }
  digitalWrite(R0, HIGH);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, LOW);

  if (digitalRead(C0) == LOW) {
    keyValue = '*';

  }
  if (digitalRead(C1) == LOW) {
    keyValue = '0';

  }
  if (digitalRead(C2) == LOW) {
    keyValue = '#';
  }
  if (digitalRead(C3) == LOW) {
    keyValue = 'D';
  }
  return keyValue;
}
 #endif
  
