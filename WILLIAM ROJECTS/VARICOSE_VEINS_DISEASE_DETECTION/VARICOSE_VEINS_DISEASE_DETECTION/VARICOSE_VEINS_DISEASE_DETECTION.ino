#include <OneWire.h>
#include <DallasTemperature.h>
#include<Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define ONE_WIRE_BUS 2
#define touch 3



#define motorPin 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float temp1;
int temp2,count=0;
String data;


void setup() {
  Serial.begin(19200);
  Serial.println("Dallas Temperature IC Control Library Demo");
  sensors.begin();
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  
  delay(1000);
  pinMode(touch, INPUT_PULLUP);
  pinMode(motorPin, OUTPUT);
  




}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Hello");
count=0;
data=" ";

Serial.print(" Requesting temperatures...");
sensors.requestTemperatures(); // Send the command to get temperature readings
Serial.println("DONE");
Serial.print("Temperature 1: ");

temp1 = sensors.getTempCByIndex(0);
temp2 = sensors.getTempFByIndex(0);
//Serial.println(temp1);
Serial.println(temp2);
lcd.setCursor(0,0);
lcd.print("Temp");
lcd.setCursor(0,1);
lcd.print(temp2);





while (Serial.available() > 0)
  {
    char c = Serial.read();
    // Serial.print(c);
    if (c == '*')
    {
      while (Serial.available() > 0)
      {
        char t = Serial.read();
        if (count == 3)
        {
          break;
        }
        if (t == '#') {
          break;
        }
        data += t;
        count++;
      }
    }
  }
  Serial.println(data);
 
  const char* tempD = data.c_str();
  int Rtemp=atoi(tempD);
 int data1= temp2-Rtemp;
  

int touch_value = digitalRead(touch);
Serial.print(touch_value);


  if (data1>2)
  {
    digitalWrite(motorPin, HIGH); //vibrate
    lcd.setCursor(7,0);
    lcd.print("status");
    lcd.setCursor(7,1);
    lcd.print("No");
    delay(1000);
  }
  else
  {
  digitalWrite(motorPin, LOW); //vibrate
  lcd.setCursor(4,0);
  lcd.clear();
    lcd.print("status");
    lcd.setCursor(4,1);
    lcd.print("Yes");
    delay(1000);
  }

  

  delay(1000);
}
