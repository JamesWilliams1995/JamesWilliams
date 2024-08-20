#ifndef IOTKEYPAD_H
#define IOTKEYPAD_H
volatile char key_value = 'x';

char key(void) {
  while (Serial.available() > 0) {
    key_value = (char)Serial.read();
    //Serial.print(key_value);
    break;
  }
  return key_value;
}
#endif
