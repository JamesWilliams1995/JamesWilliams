#ifndef FIO2_H
#define FIO2_H
//#include "Adafruit_ADS1X15.h"
//Adafruit_ADS1015 ads;
#include "global.h"
int16_t adc0, adc1, adc2, adc3;
float volts0, volts1, volts2, volts3;
float mV_baselineO2 = 9;   // millivolt value for 20.9% Ambient Air
const float ambientAir_O2Percent = 20.9;
//void setup(void)
//{
//  Serial.begin(9600);
//  Serial.println("----------------------- Oxygen Analyzer -----------------------");
//
//  ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit =  0.0078125mV
//  Serial.println("ADC Gain Set to16X (+/- 0.256V, 1-Bit = 0.0078125 mV");
//
//  ads.begin();    // Initializing the ADS1115
//  Serial.println("ADS1115 Initialized");
//
//  Serial.println("For Calibration type <cal> and click send button");
//}


/*
   Read OOM202 Oxygen Sensor connected to A0 of ADS1115
*/
float readads1115_O2()
{



  //  adc0 = ads.readADC_SingleEnded(0);
  //  adc1 = ads.readADC_SingleEnded(1);
  //  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  //  volts0 = ads.computeVolts(adc0);
  //  volts1 = ads.computeVolts(adc1);
  //  volts2 = ads.computeVolts(adc2);
  volts3 = ads.computeVolts(adc3);
  volts3 *= 1000;

  float O2_percentage = ((volts3 / mV_baselineO2) * ambientAir_O2Percent);
  //Serial.println("-----------------------------------------------------------");
  //  Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  "); Serial.print(volts0); Serial.println("V");
  //  Serial.print("AIN1: "); Serial.print(adc1); Serial.print("  "); Serial.print(volts1); Serial.println("V");
  //  Serial.print("AIN2: "); Serial.print(adc2); Serial.print("  "); Serial.print(volts2); Serial.println("V");
  Serial.print("AIN3: "); Serial.print(adc3); Serial.print("  "); Serial.print(volts3); Serial.print("mV"); Serial.print("  "); Serial.print(O2_percentage); Serial.println("%");





  return O2_percentage;
}

#endif
