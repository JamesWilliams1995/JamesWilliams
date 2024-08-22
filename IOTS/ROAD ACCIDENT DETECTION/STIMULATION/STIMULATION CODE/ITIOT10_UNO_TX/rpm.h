#ifndef RPM_H
#define RPM_H



void RPM() {

  detachInterrupt(0); //detaches the interrupt
  ttime = millis() - oldtime; //finds the time
  rpm = (rev / ttime) * 600 * 3; //calculates rpm for blades
  oldtime = millis(); //saves the current time
  rev = 0;
  Serial.println(rpm);
  attachInterrupt(0, isr, RISING);
  //lcd.clear();
  lcd.setCursor(10, 0);
  lcd.print("S:");
  lcd.print(rpm);
  delay(100);
  //  if (rpm != 0) {
  //    lcd.setCursor(11, 0);
  //    lcd.print("S:");
  //    lcd.print(rpm);
  //  }
  //  else {
  //    lcd.setCursor(11, 0);
  //    lcd.print("S:");
  //    lcd.print(rpm);
  //  }
}
#endif
