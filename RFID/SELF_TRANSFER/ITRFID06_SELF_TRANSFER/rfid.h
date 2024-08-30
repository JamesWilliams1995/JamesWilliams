#ifndef RFID_H
#define RFID_H

volatile String inputString = "";
volatile bool stringComplete = false;

const char rfid1[12] = {"870091C672A2"};
const char rfid2[12] = {'0', '2', '3', '4', '5', '6', '7', '8', '9', '0', '8', '5'};
//123456789016,023456789085
volatile char rfidmatch[12] = {};
volatile int rfidno = 0;
volatile int count1, count2, count = 0;
volatile byte data = false;

int rfid()
{
  while (Serial3.available()) {
    char inChar = (char)Serial3.read();
    Serial.print(inChar);
    inputString += inChar;
    if (count == 11) {
      count = 0;
      stringComplete = true;
      break;
    }
    count++;
  }
  if (stringComplete)
  {
    
    for (int i = 0; i < 12; i++)
    {
      rfidmatch[i] = inputString[i];
    }
    inputString = "";
    for (int i = 0; i < 12; i++)
    {
      if (rfid1[i] == rfidmatch[i])
      {
        count1++;
      }
    }
    for (int i = 0; i < 12; i++)
    {
      if (rfid2[i] == rfidmatch[i])
      {
        count2++;
      }
    }
    if (count1 == 12)
    {
      rfidno = 1;
    }
    else if (count2 == 12)
    {
      rfidno = 2;
    }
    else
    {
      rfidno = 0;
    }
    stringComplete = false;
  }
  count1 = 0;
  count2 = 0;

  return rfidno;
}
#endif
