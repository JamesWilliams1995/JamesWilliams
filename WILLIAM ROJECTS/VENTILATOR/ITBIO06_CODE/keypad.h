#ifndef KEYPAD_H
#define KEYPAD_H
#define r0 23
#define r1 25
#define r2 27
#define r3 29
#define c0 31
#define c1 33
#define c2 35
#define c3 37
char Key_value = 'x';

void key_def(void)
{
  pinMode(r0, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(c0, INPUT_PULLUP);
  pinMode(c1, INPUT_PULLUP);
  pinMode(c2, INPUT_PULLUP);
//  pinMode(c3, INPUT_PULLUP);
}

char Key_press(void)
{
  digitalWrite(r0, LOW);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, HIGH);
  if (digitalRead(c0) == 0)
  {
    Key_value = '1';
  }
  if (digitalRead(c1) == 0)
  {
    Key_value = '2';
  }
  if (digitalRead(c2) == 0)
  {
    Key_value = '3';
  }
  digitalWrite(r0, HIGH);
  digitalWrite(r1, LOW);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, HIGH);
  if (digitalRead(c0) == 0)
  {
    Key_value = '4';
  }
  if (digitalRead(c1) == 0)
  {
    Key_value = '5';
  }
  if (digitalRead(c2) == 0)
  {
    Key_value = '6';
  }
  digitalWrite(r0, HIGH);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, LOW);
  digitalWrite(r3, HIGH);
  if (digitalRead(c0) == 0)
  {
    Key_value = '7';
  }
  if (digitalRead(c1) == 0)
  {
    Key_value = '8';
  }
  if (digitalRead(c2) == 0)
  {
    Key_value = '9';
  }
  digitalWrite(r0, HIGH);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, LOW);
  if (digitalRead(c0) == 0)
  {
    Key_value = '*';
  }
  if (digitalRead(c1) == 0)
  {
    Key_value = '0';
  }
  if (digitalRead(c2) == 0)
  {
    Key_value = '#';
  }
  return Key_value;
}
#endif
