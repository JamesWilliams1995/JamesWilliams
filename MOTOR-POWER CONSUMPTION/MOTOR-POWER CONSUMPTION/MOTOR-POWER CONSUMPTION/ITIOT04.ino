#include<LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#include "IOT.h"
void iot_send(String data);
#define pump 4
/*** Dont change this value --value from datasheet**********************/
int sensorInterrupt = 0;  // interrupt 0
int sensorPin       = 3; //Digital Pin 2
unsigned int SetPoint = 400; //400 milileter
/*The hall-effect flow sensor outputs pulses per second per litre/minute of flow.*/
float calibrationFactor = 90; //You can change according to your datasheet
volatile byte pulseCounter = 0;
float flowRate = 0.0;
unsigned int flowMilliLitres = 0;
unsigned long totalMilliLitres = 0;
unsigned long oldTime = 0;
void pulseCount();
/****************************************************************************/
float analogval = 0;
float output = 0;
float R1 = 30000.0;
float R2 = 7500.0;
int ref_voltage = 5.0;
#define VOLTAGE_SENSOR A1
#define PH_SENSOR A2
/**************************************************************************/
float ph_f=0;
//void ph_dta(void);
bool flag = true;
void setup() {
  Serial.begin(9600);
  pinMode(VOLTAGE_SENSOR, INPUT);
  pinMode(PH_SENSOR, INPUT);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  MOTOR-POWER  ");

  lcd.setCursor(0, 1);
  lcd.print("   CONSUMPTION");
  delay(3000);
  lcd.clear();
  attachInterrupt(sensorPin, pulseCount, RISING); //you can use Rising or Falling

}

void loop() {

  if ((millis() - oldTime) > 1000)   // Only process counters once per second
  {

    lcd.setCursor(0, 0);
    lcd.print("pH:");
    lcd.setCursor(6, 1);
    lcd.print("M:");
    lcd.setCursor(0, 1);
    lcd.print("FS:");
    lcd.setCursor(9, 0);
    lcd.print("V:");
    //    lcd.setCursor(12, 0);
    //    lcd.print("ml/s");
    // Disable the interrupt while calculating flow rate and sending the value to the host
    detachInterrupt(sensorInterrupt);
    // Because this loop may not complete in exactly 1 second intervals we calculate the number of milliseconds that have passed since the last execution and use that to scale the output. We also apply the calibrationFactor to scale the output based on the number of pulses per second per units of measure (litres/minute in this case) coming from the sensor.
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCounter) / calibrationFactor;
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

    //     Print the flow rate for this second in litres / minute
    //        Serial.print("Flow rate: ");
    //        Serial.print(flowMilliLitres, DEC);  // Print the integer part of the variable
    //        Serial.print("mL/Second");
    //        Serial.print("\t");
    //
    //        // Print the cumulative total of litres flowed since starting
    //        Serial.print("Output Liquid Quantity: ");
    //        Serial.print(totalMilliLitres, DEC);
    //        Serial.println("mL");
    //        Serial.print("\t");
    analogval = analogRead(VOLTAGE_SENSOR);
    analogval = (analogval * ref_voltage) / 1024;
    output = analogval / (R2 / (R1 + R2));
    lcd.setCursor(3, 1);
    //int totalflow = flowMilliLitres ;
    lcd.print(flowMilliLitres);
    iot_send("%" + String(flowMilliLitres) + "#");

    //    Serial.println(flowMilliLitres);
    lcd.setCursor(11, 0);
    lcd.print(output, DEC);
    //    Serial.print(output);
    iot_send("^" + String(output) + "#");
    ph_f=analogRead(PH_SENSOR);
    lcd.setCursor(3, 0);
    lcd.print(ph_f);
    iot_send("@" + String(ph_f) + "#");
    if ((flowMilliLitres > 15) || (ph_f > 57) || (ph_f < 55) || (output < 10) || ((output > 12)))
    {
      Serial.print("ph");
      lcd.setCursor(8, 1);
      lcd.print("OFF ");
      if ((flowMilliLitres > 15))
      {
        //        lcd.setCursor(6, 1);
        //        lcd.print("HIGH WF");

        iot_send("*WaterFlow Detected#");
      }
      if (output < 10)
      {
        //        lcd.setCursor(6, 1);
        //        lcd.print("LOW VOLT");

        iot_send("*LOW VOLTAGE#");
      }
      if (output > 12)
      {
        //        lcd.setCursor(6, 1);
        //        lcd.print("HIGH VOLT");
        iot_send("*HIGH VOLTAGE#");
      }
      if (ph_f > 57) {
        //        lcd.setCursor(6, 1);
        //        lcd.print("HIGH PH");
        iot_send("*PH VALUE IS HIGH#");
      }
      if (ph_f < 55)
      {
        //        lcd.setCursor(6, 1);
        //        lcd.print("LOW WF");
        iot_send("*PH VALUE IS LOW#");
      }


      digitalWrite(pump, LOW);
    }
    else
    {
      lcd.setCursor(8, 1);
      lcd.print("ON ");
      //      lcd.setCursor(6, 1);
      //      lcd.print("NO-WF      ");
      digitalWrite(pump, HIGH);
    }



    pulseCounter = 0;

    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }
}


void pulseCount()
{
  // Increment the pulse counter
  pulseCounter++;
}
