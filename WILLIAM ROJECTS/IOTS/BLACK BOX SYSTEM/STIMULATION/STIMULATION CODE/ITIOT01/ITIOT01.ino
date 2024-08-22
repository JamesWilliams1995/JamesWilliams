
#include "initial.h"
#include "lcd.h"
#include "gsm.h"
#include "ss.h"
#include "gps.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("BLACK BOX");
  lcd.setCursor(5, 1);
  lcd.print("SYSTEM");
  dht.dht_read(DHTPIN);


  //gps();

  attachInterrupt(digitalPinToInterrupt(CRASH_SENSOR), crash_ISR, HIGH);
  pinMode(GAS_SENSOR, INPUT);


  //delay(100);

  //  while (!Serial) {
  //     //h/ wait for serial port to connect. Needed for native USB port only
  //   ;
  //  }
  //  Serial.print("Initializing SD card...");
  //  if (!SD.begin(10)) {
  //    Serial.println("initialization failed!");
  //    while (1);
  //  }
  //  Serial.println("initialization done.");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (CRASH_FLAG == true) {
    CRASH_FLAG = false;
    Serial.println("ACCIDENT");
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("ACCIDENT");
    GSM_SEND();
    //IOT("*ACCIDENT#");
    lcd.setCursor(4, 1);
    lcd.print("GSM SEND");
    Serial.println("GSM SEND");
    delay(300);
  }


  lcd.clear();
  dht.dht_read(DHTPIN);
  t = dht.temperature;
  Serial.println(t);
  lcd.setCursor(4, 0);
  lcd.print("T:");
  lcd.print(t);

  GAS_DATA = digitalRead(GAS_SENSOR);
  Serial.println(GAS_DATA);
  lcd.setCursor(10, 0);
  lcd.print("G:");
  lcd.print(GAS_DATA);


  if (GAS_DATA == 0) {
    lcd.setCursor(3, 1);
    lcd.print("Gas detected");
  }
  else {
    lcd.setCursor(1, 1);
    lcd.print("No Gas detected");
  }

  delay(50);
  SD_CARD_WRITE(String(GAS_DATA), String(t));
  //IOT("@" + String(t) + "#" + "$" + String(GAS_DATA) + "#");
}


void crash_ISR() {
  CRASH_FLAG = true;
}

//void IOT(String s) {
//  for (int i = 0; i < s.length(); i++) {
//    Serial.write(s[i]);
//  }
//  delay(3000);
//}

void SD_CARD_WRITE(String s1, String s2) {

  myFile = SD.open("data.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to data.txt...");
    myFile.println();
    myFile.print("Gas: ");
    myFile.print(s1);
    myFile.print("\t");
    myFile.print("temp: ");
    myFile.print(s2);
    myFile.close();
    Serial.println("done.");
  }
  else {
    // if the file didn't open, print an error:
    //Serial.println("error opening test.txt");
    Serial.println("Writing to data.txt...done.");
  }
}
