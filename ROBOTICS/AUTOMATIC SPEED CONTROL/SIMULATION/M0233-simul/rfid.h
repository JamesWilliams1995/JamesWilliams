#ifndef RFID_H
#define RFID_H
#include"softserial.h"
volatile String inputString = "";
volatile bool stringComplete = false;

const char rfid1[12] = {"8700840F7478"};
const char rfid2[12] = {"8700919DF77C"};
const char rfid3[12] = {"8700808AE06D"};
const char rfid4[12] = {"870091819601"};
const char rfid5[12] = {"3B00F59C0153"};
const char rfid6[12] = {"3B00F5B294E8"};
const char rfid7[12] = {"3B00F5BE4F3F"};
const char rfid8[12] = {"3B00F5C12D22"};
const char rfid9[12] = {"3B00F5BB592C"};
const char rfid10[12] = {"3B00F5B86B1D"};

volatile char rfidmatch[12] = {};
volatile int rfidno = 0;
volatile int rfidno_1 = 0;
volatile int count1, count2, count3, count4, count5, count6, count7, count8, count9, count10, count = 0;
volatile byte data = false;

int rfid()
{
  while (rf.available()) {
    char inChar = (char)rf.read();
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
    for (int i = 0; i < 12; i++)
    {
      if (rfid6[i] == rfidmatch[i])
      {
        count6++;
      }
    }
    for (int i = 0; i < 12; i++)
    {
      if (rfid7[i] == rfidmatch[i])
      {
        count7++;
      }
    }
    for (int i = 0; i < 12; i++)
    {
      if (rfid8[i] == rfidmatch[i])
      {
        count8++;
      }
    }
    for (int i = 0; i < 12; i++)
    {
      if (rfid9[i] == rfidmatch[i])
      {
        count9++;
      }
    }
    for (int i = 0; i < 12; i++)
    {
      if (rfid10[i] == rfidmatch[i])
      {
        count10++;
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
    else if (count6 == 12)
    {
      rfidno = 6;
    }
    else if (count7 == 12)
    {
      rfidno = 7;
    }
    else if (count8 == 12)
    {
      rfidno = 8;
    }
    else if (count9 == 12)
    {
      rfidno = 9;
    }
    else if (count10 == 12)
    {
      rfidno = 10;
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
  count6 = 0;
  count7 = 0;
  count8 = 0;
  count9 = 0;
  count10 = 0;
 
  return rfidno;
}
#endif
