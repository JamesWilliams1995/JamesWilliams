#ifndef CUTTER_H
#define CUTTER_H
#include"global.h"
void F_cutter_state(void)
{
  switch (E_CUTTER_STATE)
  {
    case CUTTER_CW:
      digitalWrite(cutter_positive, HIGH);       //CUTTER FORWARD
      digitalWrite(cutter_negative, LOW);
      break;
    case CUTTER_ACW:
      digitalWrite(cutter_positive, LOW);       //CUTTER REVERSE
      digitalWrite(cutter_negative, HIGH);
      break;
    case CUTTER_OFF:
      digitalWrite(cutter_positive, LOW);       //CUTTER OFF
      digitalWrite(cutter_negative, LOW);
      break;
  }
}
#endif
