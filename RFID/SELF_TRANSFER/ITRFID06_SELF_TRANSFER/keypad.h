#ifndef KEYPAD_H
#define KEYPAD_H
#define TOTAL_ROW 4
#define TOTAL_COL 4
#define r0 A3
#define r1 A2
#define r2 A1
#if(TOTAL_ROW==4)
#define r3 A0
#endif

#define c0 A4
#define c1 A5
#define c2 A6
#if(TOTAL_COL==4)
#define c3 A7
#endif

volatile char key_value = 'x';

void keypad_init()
{
  pinMode(r0, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
#if(TOTAL_ROW==4)
  pinMode(r3, OUTPUT);
#endif
  pinMode(c0, INPUT_PULLUP);
  pinMode(c1, INPUT_PULLUP);
  pinMode(c2, INPUT_PULLUP);
#if(TOTAL_COL==4)
  pinMode(c3, INPUT_PULLUP);
#endif
}

char key()
{
  digitalWrite(r0, LOW);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
#if(TOTAL_ROW==4)
  digitalWrite(r3, HIGH);
#endif
  if (digitalRead(c0) == LOW)
    key_value = '*';
  while (digitalRead(c0) == LOW);
  if (digitalRead(c1) == LOW)
    key_value = '0';
  while (digitalRead(c1) == LOW);
  if (digitalRead(c2) == LOW)
    key_value = '#';
  while (digitalRead(c2) == LOW);
#if(TOTAL_COL==4)
  if (digitalRead(c3) == LOW)
    key_value = 'D';
  while (digitalRead(c3) == LOW);
#endif


  digitalWrite(r0, HIGH);
  digitalWrite(r1, LOW);
  digitalWrite(r2, HIGH);
#if(TOTAL_ROW==4)
  digitalWrite(r3, HIGH);
#endif
  if (digitalRead(c0) == LOW)
    key_value = '7';
  while (digitalRead(c0) == LOW);
  if (digitalRead(c1) == LOW)
    key_value = '8';
  while (digitalRead(c1) == LOW);
  if (digitalRead(c2) == LOW)
    key_value = '9';
  while (digitalRead(c2) == LOW);
#if(TOTAL_COL==4)
  if (digitalRead(c3) == LOW)
    key_value = 'C';
  while (digitalRead(c3) == LOW);
#endif
  digitalWrite(r0, HIGH);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, LOW);
#if(TOTAL_ROW==4)  
    digitalWrite(r3, HIGH);  
#endif

  if (digitalRead(c0) == LOW)
    key_value = '4';
  while (digitalRead(c0) == LOW);
  if (digitalRead(c1) == LOW)
    key_value = '5';
  while (digitalRead(c1) == LOW);
  if (digitalRead(c2) == LOW)
    key_value = '6';
  while (digitalRead(c2) == LOW);
#if(TOTAL_COL==4)
  if (digitalRead(c3) == LOW)
    key_value = 'B';
  while (digitalRead(c3) == LOW);
#endif
digitalWrite(r0, HIGH);
digitalWrite(r1, HIGH);
digitalWrite(r2, HIGH);
#if(TOTAL_ROW==4)
digitalWrite(r3, LOW);
#endif

if (digitalRead(c0) == LOW)
  key_value = '1';
while (digitalRead(c0) == LOW);
if (digitalRead(c1) == LOW)
  key_value = '2';
while (digitalRead(c1) == LOW);
if (digitalRead(c2) == LOW)
  key_value = '3';
while (digitalRead(c2) == LOW);
#if(TOTAL_COL==4)
if (digitalRead(c3) == LOW)
  key_value = 'A';
while (digitalRead(c3) == LOW);
#endif
return key_value;
}
#endif
