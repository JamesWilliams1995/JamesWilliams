#include"dht11.h"
DHT dht;
void setup()
{
  Serial.begin(9600);
}
void loop() {
  dht.dht_read(2);
  Serial.println(dht.temperature);
  Serial.println(dht.RH);
  delay(500);
}
