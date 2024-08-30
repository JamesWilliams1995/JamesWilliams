#include<SoftwareSerial.h>
#include "gsm.h"
#define Apr 7
#define Apr 8
int data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (Apr, OUTPUT);
  digitalWrite(Apr, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    char data = (char)Serial.read();
    Serial.print(data);
    if (data == 'A') {
      gsm("8189988347", "sand theft detected");
      digitalWrite(Apr, LOW);
      delay(100);
      digitalWrite(Apr, HIGH);
    }
    if (data == 'B') {
      gsm("8189988347", "BROKEN");
      digitalWrite(Apr, LOW);
      delay(100);
      digitalWrite(Apr, HIGH);
    }

  }
}
