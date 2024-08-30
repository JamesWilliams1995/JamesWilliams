#include "lcd.h"
#include "gps.h"
#include "gsm.h"
#include <ultrasonic.h>
#include"dht11.h"
DHT dht;

bool leakage_flag = false;
/*** Dont change this value --value from datasheet**********************/
int sensorInterrupt = 0;  // interrupt 0
int sensorPin       = 2; //Digital Pin 2

unsigned int SetPoint = 400; //400 milileter
/*The hall-effect flow sensor outputs pulses per second per litre/minute of flow.*/
float calibrationFactor = 90; //You can change according to your datasheet
volatile byte pulseCount = 0;
float flowRate = 0.0;
unsigned int flowMilliLitres = 0;
unsigned long totalMilliLitres = 0;
unsigned long oldTime = 0;
/*************************************************************************/
ULTRASONIC U1;
#define D_temp A0
#define ir_pin 3
#define gas_pin 4
bool refill_flag = false;
bool gas_flag = false;

void ultrasonic(void);

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  lcd.begin(16, 2);
  U1.begin(A1, A2);
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
  pinMode(ir_pin, INPUT);
  dht.dht_read(D_temp);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("DRAINAGE_BLOCK");
  lcd.setCursor(3, 1);
  lcd.print("MONITORING");
  delay(100);
  lcd.clear();
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING); //you can use Rising or Falling
  //gps();
}

void loop()
{
  if ((millis() - oldTime) > 1000)   // Only process counters once per second
  {
    temperature();
    lcd_update();
    ultrasonic();
    lcd.setCursor(9, 0);
    lcd.print("D:");
    lcd.setCursor(11, 0);
    int pin = digitalRead(ir_pin);
    lcd.print(pin);
    if (pin == 0)
    {
      Serial.print('D');
      gsm("8189988347", "DRAINAGE OPEN");
    }
    lcd.setCursor(13, 0);
    lcd.print("G:");
    lcd.setCursor(15, 0);
    lcd.print(digitalRead(gas_pin));
    lcd.setCursor(0, 1);
    if (digitalRead(gas_pin) == 0)
    {
      Serial.print('B');
      gsm("8189988347", "METHANE DETECTED");
    }
    lcd.print("F:");
    // Disable the interrupt while calculating flow rate and sending the value to the host
    detachInterrupt(sensorInterrupt);
    // Because this loop may not complete in exactly 1 second intervals we calculate the number of milliseconds that have passed since the last execution and use that to scale the output. We also apply the calibrationFactor to scale the output based on the number of pulses per second per units of measure (litres/minute in this case) coming from the sensor.
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime = millis();
    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres = (flowRate / 60) * 1000;
    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;
    unsigned int frac;

    lcd.setCursor(2, 1);
    lcd.print(flowMilliLitres, DEC);

    if (flowMilliLitres > 5)
    {
      Serial.print('E');
      lcd.setCursor(4, 1);
      lcd.print("flow blocked");
      gsm("8189988347", "FLOW BLOCKED ");
    }
  }
  // Reset the pulse counter so we can start incrementing again
  pulseCount = 0;

  // Enable the interrupt again now that we've finished sending output
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}
//Insterrupt Service Routine

void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
void temperature(void)
{
  dht.dht_read(D_temp);
  if (dht.temperature > 33)
  {
    Serial.print('A');
    gsm("8189988347", "HIGH TEMPERATURE");
  }
}

void lcd_update(void)
{
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.setCursor(2, 0);
  lcd.print(dht.temperature);
  delay(1Ś00);
}

void ultrasonic(void)
{
  lcd.setCursor(5, 0);
  lcd.print("U:");
  int cm = U1.ultra();
  if (cm < 10)
  {
    Serial.print('C');
    lcd.print("F");
    gsm("8189988347", "DRAINAGE FULL");
  }
  else if (cm > 10 && cm < 30)
  {
    lcd.print("M");
  }
  else if (cm > 30)
  {
    lcd.print("E");
  }
}
