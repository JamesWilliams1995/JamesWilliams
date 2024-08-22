#ifndef TEMPERATURE_H
#define TEMPERATURE_H

//#include "DHT.h"
//#define DHTTYPE DHT11
//DHT dht(DHTPIN,DHTTYPE);
//void TEMP();
void TEMP() {

  dht.dht_read(DHTPIN);
  int t = dht.temperature;
  lcd.setCursor(4, 0);
  lcd.print("T:");
  lcd.print(t);
  Serial.println("T:");
  Serial.print(t);
  
  //Serial.print(t);

}
#endif
