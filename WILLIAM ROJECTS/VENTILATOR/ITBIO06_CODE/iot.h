#ifndef IOT_H
#define IOT_H
void iott(String s)
{
  for (int i = 0; i < s.length(); i++)
  {
    Serial1.write(s[i]);
  }
  //delay(3000);
}
#endif
