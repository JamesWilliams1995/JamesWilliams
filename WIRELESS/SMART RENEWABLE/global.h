#ifndef GLOBAL_H
#define GLOBAL_H

#define trigPin 2
#define echoPin 3


int counter = 0;
int currentState = 0;
int previousState = 0;



#define ANALOG_IN_PIN A0

float adc_voltage = 0.0;
float in_voltage = 0.0;


float adc_voltage1 = 0.0;
float in_voltage1 = 0.0;


float R1 = 30000.0;
float R2 = 7500.0;


float ref_voltage = 5.0;


int adc_value = 0;


#define RELAY_PIN1 4
#define RELAY_PIN2 5

#define iot_on_off 6
#define iot_mode 7
#include "PowerAnalyzer.h"
#define VOLT_PIN A1                     //Voltage signal is connected with Anaog pin 0
#define CURRENT_PIN A2                 //current Signal ic connected with Analog Pin 1
#define volt_transfer_ratio ((100.0+10.0)/10.0) // Vin/Vadc = R1/(R1+R2),Here R1 = 10k, R2 = 100k
#define current_transfer_ratio (1000.00/200.00) //CT ratio = 1000, Sensing Resistor = 200 Ohm
Measure measure(VOLT_PIN, CURRENT_PIN); //Creating the object
float V, I, P, pf;

#endif
