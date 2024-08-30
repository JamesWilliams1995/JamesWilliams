#ifndef RFID_H
#define RFID_H

volatile String inputString = "";
volatile bool stringComplete = false;

const char rfid1[12] = {"87007F2FF720"};//1
const char rfid2[12] = {"4200D970AF44"};//2

const char rfid3[12] = {"3A001A8AD278"};
const char rfid4[12] = {"3A0018782E74"};
const char rfid5[12] = {"3A0018D86D97"};

volatile char rfidmatch[12] = {};
volatile int rfidno = 6;
volatile int rfidno_1 = 0;
volatile int count1, count2, count3, count4, count5, count = 0;
volatile byte data = false;

int rfid()
{
  while (Serial.available()) {
    char inChar = (char)Serial.read();
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
    for (int i = 0; i < 12; i++)
    {
      if (rfid3[i] == rfidmatch[i])
      {
        count3++;
      }
    }
    for (int i = 0; i < 12; i++)
    {
      if (rfid4[i] == rfidmatch[i])
      {
        count4++;
      }
    }
    for (int i = 0; i < 12; i++)
    {
      if (rfid5[i] == rfidmatch[i])
      {
        count5++;
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
    else if (count3 == 12)
    {
      rfidno = 3;
    }
    else if (count4 == 12)
    {
      rfidno = 4;
    }
    else if (count5 == 12)
    {
      rfidno = 5;
    }
    else
    {
      rfidno = 0;
    }
    stringComplete = false;
  }
  count1 = 0;
  count2 = 0;
  count3 = 0;
  count4 = 0;
  count5 = 0;

  return rfidno;
}
#endif
