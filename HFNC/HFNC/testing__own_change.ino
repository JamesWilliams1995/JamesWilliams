 #include <Wire.h>
#include"fio2.h"
#include"xgzp6847d.h"
#include "XGZP6897D.h"
#include "HoneywellZephyrI2C.h"
ZephyrFlowRateSensor sensor(0x49, 200, ZephyrFlowRateSensor::SLPM);
#include <Adafruit_GFX.h>   // Core graphics library

#include "global.h"
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
MCUFRIEND_kbv tft;

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <FreeDefaultFonts.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define ORANGE  0xFD20
#define DARKORANGE  0xFB60
#define MAROON  0x7800
#define BLACKM  0x18E3
#define pwm_pin 44
#define o2_pwm_pin 46
#define Buzzer 22

int send_o2_pwm, pwmvalue = 0, o2_pwm = 0, temperature_value = 27, humidity_value = 0,
                 size_of_array = 0, last_value = 0, last_value2 = 0, humidity_last_value = 0,
                 temp_last_value = 0, lastMenuItem_3 = 0, send_pwm = 0, send_pwm2 = 0, i = 1, z = 0,
                 menuitem = 1, FIO2_VALUE = 0, FLOW_VALUE = 0, FLOW_VALUE2 = 10, page = 1, lastMenuItem = 0,
                 x = 0, y = 0, menuitem_2 = 1, menuitem_3 = 1, menuitem_4 = 1, lastMenuItem_2 = 1;

const int pwm_full_range = 255, total_percentage = 100, flowRange = 200;
float total_o2_in_percentage = 0.0, total_air_in_percentage = 0.0, subtract_o3 = 0.0,
      balance_purity_by_air3 = 0.0, o2_per_litre = 0.0, o2_in_air = 0.0, required_o2 = 0.0,
      o2_alone = 0.0, balance_purity_by_air = 0.0, total_purity = 0.0, total_purity2 = 0.0;

float balance_purity_by_air2 = 0.0, total_purity3 = 0.0, subtract_o2 = 0.0, required_air = 0.0, f_loop1 = 0.0;

String menuItem1 = "MENU";
String menuItem2 = "SETFLOW";
String menuItem3 = "SETFIO2";
String menuItem4 = "START";
//String menuItem5 = "STANDBY";
String menuItem6 = "  ADULT ";  //HIGH FLOW FOR ADULT
String menuItem7 = "PEDIATRIC";  //  LOW FLOW REPLACE pediatric PEDIATRIC
String menuItem8 = "BACK";
String menuItem9 = "TEMP";
String menuItem10 = "RH";
String menuItem11 = "ALARM";
String menuItem12 = "x";
String menuItem13 = "ON";
String menuItem14 = "OFF";
String lastMenuItem_4;
boolean up = false;
boolean down = false;
boolean middle = false;
boolean encoder_boolean = false;
boolean default_boolean = false;
byte msb, lsb, address = 0x28;
ClickEncoder *encoder;
int16_t last, value;
void menu();
enum {
  O2_FLOW_HIGH = 0,
  AIR_FLOW_HIGH = 1
} FLOW;

void setup() {
  encoder = new ClickEncoder(A6, A7, A8);
  encoder->setAccelerationEnabled(false);
  Wire.begin();
  Wire.setClock(400000L);
 // sensor.begin();
//   if(!mysensor.readRawSensor(mysensor.rawTemperature,mysensor.rawPressure))
//   {
//    Serial.print(String("check************"));
//    while(1);
//   }
   
 // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  //ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  //ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  //ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV



  //ads.begin();
 // mysensor.begin();
  Serial.begin(9600);
  Serial.println("ADS1115 Initialized");
  pinMode(pwm_pin, OUTPUT);
  pinMode(o2_pwm_pin, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  Serial.println(ID, HEX);
  tft.setRotation(1);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  last = encoder->getValue();
  tft.fillScreen(0xFFFF);
  set_up();                                           //To  define display user interface stably so declared here
}
void set_up()                                         //To  define display user interface function
{
  tft.drawFastHLine(0, 30, 480, BLACK);  // main menu top horizontal line
  tft.drawFastHLine(0, 31, 480, BLACK);  // main menu top horizontal darkness line to line
  tft.fillRect(0, 0, 480, 31, BLACK);    // horizontal black
  tft.fillRect(0, 0, 480, 30, tft.color565(192, 192, 192));  // setting & monitoring top horizontal
  tft.setCursor(120, 5);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print(String ("SETTING & MITORING"));
  tft.drawFastVLine(84, 32, 290, BLACK);  // mainmenu vertical darkness line
  tft.drawFastVLine(85, 32, 290, BLACK);  // mainmenu vertical darkness line to line
  tft.drawFastHLine(86, 284, 480, BLACK);  // mainmenu bottom horizontal  line
  tft.drawFastHLine(86, 285, 480, BLACK);  // mainmenu bottom horizontal darkness line to line
  tft.fillRoundRect(90, 35, 190, 120, 5, tft.color565(87, 146, 255));        // flow lpm box
  tft.fillRoundRect(285, 35, 190, 120, 5, tft.color565(87, 146, 255));       // o2 show
  tft.fillRoundRect(90, 160, 190, 120, 5, tft.color565(87, 146, 255));       // pressure show
  tft.fillRoundRect(285, 160, 190, 120, 5, tft.color565(87, 146, 255));      // temperature show

  tft.drawFastHLine(0, 109, 85, BLACK);  // mainmenu menu between setflow horizontal line
  tft.drawFastHLine(0, 110, 85, BLACK);  // mainmenu menu between setflow  horizontal darkness line o line
  tft.fillRect(0, 33, 84, 76, tft.color565(137, 146, 153));  // mainmenu menu box 1
  tft.drawFastHLine(0, 183, 85, BLACK);  // mainmenu setflow between setfio2 horizontal line
  tft.drawFastHLine(0, 184, 85, BLACK);  // mainmenu setflow between setfio2 horizontal line to line
  tft.fillRect(0, 112, 84, 71, tft.color565(137, 146, 153)); // mainmenu setflow box 2
  tft.drawFastHLine(0, 253, 85, BLACK);  // mainmenu setfio2 between start horizontal line
  tft.drawFastHLine(0, 254, 85, BLACK);  // mainmenu setfio2 between start horizontal line to line
  tft.fillRect(0, 186, 84, 67, tft.color565(137, 146, 153)); // mainmenu setfio2 box 3
  tft.fillRect(0, 256, 84, 81, tft.color565(137, 146, 153)); // mainmenu start &standby box 4
  tft.fillRect(86, 286, 400, 67, tft.color565(137, 146, 153)); // erase high flow low flow blank space fillcolor
  tft.fillRoundRect(205, 105, 70, 40, 5, tft.color565(159, 171, 180)); // flow setting inital emty box count clear rectangle
  tft.fillRoundRect(400, 105, 70, 40, 5, tft.color565(159, 171, 180)); // o2 setting inital emty box count clear rectangle

  /******************** flow text***************************/
  tft.setTextSize(2);
  tft.setCursor(220, 50);
  tft.setTextColor(BLACK);
  tft.print(String ("FLOW"));
  /***************************lpm text********************/
  tft.setTextSize(3);
  //  tft.setCursor(110, 70);
  //  tft.setTextColor(WHITE);
  //  tft.print(String ("--"));
  tft.setCursor(105, 110);
  tft.setTextColor(WHITE);
  tft.print(String ("LPM"));
  /**********************************02 text & %************/
  tft.setTextSize(2);
  tft.setCursor(440, 50);
  tft.setTextColor(BLACK);
  tft.print(String ("O"));
  tft.setCursor(453, 54);
  tft.setTextColor(BLACK);
  tft.print(String ("2"));


  tft.setTextSize(4);
  tft.setCursor(303, 108);
  tft.setTextColor(WHITE);
  tft.print(String ("%"));
  /**************************temperature & Celsius unit C text****************************/
  tft.setTextSize(2);
  tft.setCursor(135, 177);
  tft.setTextColor(BLACK);
  tft.print(String ("TEMPERATURE"));
  //  tft.setTextSize(3);
  //  tft.setCursor(110, 220);
  //  tft.setTextColor(WHITE);
  //  tft.print(String ("--"));
  tft.setTextSize(3);
  tft.setCursor(250, 230);
  tft.setTextColor(WHITE);
  tft.print(String ("C"));

  tft.setTextSize(2);
  tft.setCursor(237, 226);
  tft.setTextColor(WHITE);
  tft.print(String ("o"));
  /************************************pressure text & cmh2o************************/
  tft.setTextSize(2);
  tft.setCursor(370, 177);
  tft.setTextColor(BLACK);
  tft.print(String ("PRESSURE"));


  tft.setTextSize(3);
  tft.setCursor(380, 230);
  tft.setTextColor(WHITE);
  tft.print(String ("cmH2O"));
  tft.setTextSize(3);
  page = 1;
}
void pwm_function()
{
  tft.setTextSize(3);
  send_pwm = pwm_flowrate(required_air);
  analogWrite(pwm_pin, send_pwm);

  send_pwm2 = o2_pwm_flowrate(o2_alone);
  analogWrite(o2_pwm_pin, send_pwm2);
  Serial.println(String("send_o2_pwm ******************** ") + o2_alone);
  Serial.println(String("send_pwm2 ******************** ") + send_pwm2);

  Serial.println(String("required_air <<<<<<<<<<<<<<<<<<<< ") + required_air);
  Serial.println(String("send_pwm <<<<<<<<<<<<<<<<<<<< ") + send_pwm);
  //  Serial.println(String("required_air") + required_air);
  //printSensorData();
  printSensorData();
}
//void pwm_function2()
//{
//  tft.setTextSize(3);
//  send_pwm2 = o2_pwm_flowrate(o2_alone);
//  analogWrite(o2_pwm_pin, send_pwm2);
//  Serial.println(String("send_o2_pwm ******************** ") + o2_alone);
//  Serial.println(String("send_pwm2 ******************** ") + send_pwm2);
//  printSensorData();
//}

int pwm_flowrate(float desiredflowrate)                      // pwm & flow match  calibiration code
{
  float flowrate[23] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0};
  int pwmValues[23] = {12, 16, 20, 23, 26, 33, 35, 37, 40, 41, 43, 45, 47, 53, 55, 57, 59, 60, 62, 66, 70, 75};
  int index = 0;
  size_of_array = sizeof(flowrate) / sizeof(float);
  while (index < size_of_array - 1 && desiredflowrate > flowrate[index + 1])
  {
    index++;
  }
  float flowRateDiff = flowrate[index + 1] - flowrate[index];
  int pwmValueDiff = pwmValues[index + 1] - pwmValues[index];
  float flowRateOffset = desiredflowrate - flowrate[index];
  int pwmValue = pwmValues[index] + (pwmValueDiff * flowRateOffset / flowRateDiff);
  // Constrain the PWM value between 0 and 255 (Arduino PWM range)
  return constrain(pwmValue, 12, 75);
}

int o2_pwm_flowrate(int desired_o2_flow)
{
  float flowrate[25] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 30.0, 40.0, 60.0, 100.0};
  int pwmValues[25] = {12, 16, 20, 23, 26, 33, 35, 37, 40, 41, 43, 45, 47, 53, 55, 57, 59, 60, 62, 66, 80, 100, 140, 200};
  int index = 0;
  size_of_array = sizeof(flowrate) / sizeof(float);
  while (index < size_of_array - 1 && desired_o2_flow > flowrate[index + 1])
  {
    index++;
  }
  float flowRateDiff = flowrate[index + 1] - flowrate[index];
  int pwmValueDiff = pwmValues[index + 1] - pwmValues[index];
  float flowRateOffset = desired_o2_flow - flowrate[index];
  int pwmValue = pwmValues[index] + (pwmValueDiff * flowRateOffset / flowRateDiff);
  Serial.println(String("pwmValue") + pwmValue);
  // Constrain the PWM value between 0 and 255 (Arduino PWM range)
  return constrain(pwmValue, 12, 200);
}
void enum_display(int FLOW)
{
  switch (FLOW)
  {
    case 0:
      tft.fillRect(87, 287, 410, 40, RED);
      tft.setTextColor(BLACK);
      tft.setCursor(100, 295);
      tft.print("O2_FLOW_HIGH");
      break;
    case 1:
      tft.fillRect(87, 287, 410, 40, RED);
      tft.setTextColor(BLACK);
      tft.setCursor(100, 295);
      tft.print("AIR_FLOW_HIGH");
      break;
  }
}
void send_as_input(const int x, const int y)
{
  o2_per_litre = (float)(100 / x);
  o2_in_air = (float)21 / x;
  required_o2 = (float)  y / 100;
  o2_alone = x * required_o2;
  balance_purity_by_air = (x - o2_alone) * o2_in_air;
  total_purity = (int)((o2_per_litre * o2_alone) + balance_purity_by_air);
  if (y == 21)
  {
    o2_alone = 0;
    required_air = x - o2_alone;
    balance_purity_by_air2 = (x - o2_alone) * o2_in_air;
    total_o2_in_percentage = (100 / x) * o2_alone;
    total_air_in_percentage = (100 / x) * required_air;
    total_purity = (int)((o2_per_litre * o2_alone) + balance_purity_by_air2);

    if (((page == 7 || page == 1)) && (menuitem == 1))
    {
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.setCursor(55, 125);
      tft.print(required_air);
      tft.setTextColor(WHITE);
      tft.setCursor(55, 230);
      tft.print(o2_alone);
    }
  }
  if ((y > 21) && (y < 100))
  {
    o2_pwm =   y * x / 100;
    o2_alone = o2_alone - 1;
    required_air = x - o2_alone;
    total_o2_in_percentage = (100 / x) * o2_alone;
    total_air_in_percentage = (100 / x) * required_air;
    balance_purity_by_air2 = (x - o2_alone) * o2_in_air;
    total_purity = (int)((o2_per_litre * o2_alone) + balance_purity_by_air2);
    if (((total_purity != y) && (total_purity > y)) || ((total_purity != y) && (total_purity < y)))
    {
      for (f_loop1 = 0.51; f_loop1 <= 300.50; f_loop1 = f_loop1 + 0.01)
      {
        o2_alone = f_loop1 - o2_alone;
        required_air = x - o2_alone;
        balance_purity_by_air3 = (x - o2_alone) * o2_in_air;
        total_o2_in_percentage = (100 / x) * o2_alone;
        total_air_in_percentage = (100 / x) * required_air;
        total_purity = (int)((o2_per_litre * o2_alone) + balance_purity_by_air3);
        if (total_purity == y)
        {

          if (required_air < 0.80)
          {

            digitalWrite(Buzzer, HIGH);
            tft.setCursor(65, 95);
            FLOW = O2_FLOW_HIGH;
            enum_display(FLOW);
          }
          else
          {
            digitalWrite(Buzzer, LOW);
          }
          if (((page == 7 || page == 1)) && (menuitem == 1))
          {
            tft.setTextSize(3);
            tft.setTextColor(WHITE);
            tft.setCursor(55, 125);
            tft.print(required_air);
            tft.setTextColor(WHITE);
            tft.setCursor(55, 230);
            tft.print(o2_alone);
          }
          break;
        }
      }
    }
  }
  if (y == 100)
  {

    required_air = 0;
    total_o2_in_percentage = (100 / x) * x;
    total_air_in_percentage = (100 / x) * required_air;

    if (((page == 7 || page == 1)) && (menuitem == 1))
    {
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.setCursor(55, 125);
      tft.print(required_air);
      tft.setTextColor(WHITE);
      tft.setCursor(55, 230);
      tft.print(o2_alone);
    }
  }
}

void timerIsr() {
  encoder->service();
}
void readRotaryEncoder()
{
  value += encoder->getValue();

  if (value / 2 > last) {
    last = value / 2;
    down = true;
    //delay(150);
  } else   if (value / 2 < last) {
    last = value / 2;
    up = true;
    //delay(150);
    Serial.println(last);
  }
}



void displayMenuItem(String item, int position, int position2, boolean selected)
{
  tft.setTextSize(2);
  if (selected)
  {
    if (menuitem == 1)
    {
      //tft.fillRect(0, 232, 135, 90, 0xFFE0);
      tft.setTextColor(YELLOW);
    }
    if (menuitem == 2)
    {
      //tft.fillRect(136, 232, 163, 90, 0xFFE0);
      tft.setTextColor(YELLOW);
    }
    else if (menuitem == 3)
    {
      //tft.fillRect(301, 232, 180, 90, 0xFFE0);
      tft.setTextColor(YELLOW);
    }
    else if (menuitem == 4)
    {
      //tft.fillRect(301, 232, 180, 90, 0xFFE0);
      tft.setTextColor(YELLOW);
    }
    else if (menuitem == 5)
    {
      //tft.fillRect(301, 232, 180, 90, 0xFFE0);
      tft.setTextColor(YELLOW);
    }
  }
  else
  {
    tft.setTextColor(BLACK);
  }
  tft.setCursor(position, position2);
  tft.print(item);
}

int displayIntMenuPage(int value)
{
  tft.setTextSize(2);
  tft.setTextColor(YELLOW,  tft.color565(159, 171, 180));

  tft.setCursor(215, 114);
  tft.print(value);
  last_value = value;
  last_value = value;
  if (value <= 100)
  {
    tft.print(" ");                                                 // emty space 100 to " "  then start 99 below
  }
  return value;
}
void send_temp(int value)
{
  tft.setTextSize(2);
  tft.setTextColor(BLACK, tft.color565(137, 146, 153));

  tft.setCursor(368, 85);
  tft.print(value);
  temp_last_value = value;
}
void send_humidity(int value)
{
  tft.setTextSize(2);
  tft.setTextColor(BLACK, tft.color565(137, 146, 153));
  tft.setCursor(368, 119);
  tft.print(value);
  humidity_last_value = value;
}
void displayMenuItem_2(String item, int position, int position1, boolean selected)
{
  if (selected)
  {
    tft.setTextColor(YELLOW);
  } else
  {
    tft.setTextColor(BLACK);
  }
  tft.setCursor(position, position1);
  tft.print(item);
}
int displayIntMenuPage_2(int value)
{
  tft.setTextSize(2);
  tft.setTextColor(YELLOW, tft.color565(159, 171, 180));
  tft.setCursor(410, 114);
  tft.print(value);
  last_value2 = value;
  if (value <= 100)
  {
    tft.print(" ");                                                 ////////////////////jgygyfyug
  }
  return value;
}
/***************************************************** honeywell flow sensor*********************************/
float getFlowReading() {
  if (sensor.readSensor())
  {
    Serial.println("Failed to initialize honey.");
    tft.setTextSize(3);
    //      tft.fillRect(86, 286, 400, 67, tft.color565(255, 0, 0));                         //FULL RED WITH WITH TEXT
    //    tft.setTextColor(WHITE, tft.color565(255, 0, 0));
    tft.setTextColor(tft.color565(255, 0, 0), tft.color565(137, 146, 153));              //ONLY TEXT IN RED
    tft.setCursor(100, 290);
    tft.print("   FLOW SENSOR OPEN");
    return 0.00;
  }
  else if ( sensor.readSensor() == 0 )
  {
    tft.fillRect(86, 286, 400, 67, tft.color565(137, 146, 153));
    return sensor.flow();
  }
}
/************************************* sensordatas  honewell_flow_sensor_unit_lpm, fio2_sensor_unit_o2,cf_pressure_sensor_unit_cmH2O with temperature_unit C**********************/
void printSensorData() {

  float print_flow = getFlowReading();

  if (print_flow <= 0)
  {
    print_flow = 0;
  }
  tft.setTextSize(3);
  //  dtostrf(print_flow, 3, 2, flow_buff_float);
  //sprintf(flow_buff_string, "%d", print_flow);
  tft.setTextColor(WHITE, tft.color565(87, 146, 255));
  tft.setCursor(102, 75);
  tft.print(print_flow);
  if (print_flow <= 320)
  {
    tft.print(" ");
  }
  //Serial.println(String("flow : ") + print_flow);
  tft.setCursor(303, 75);
  tft.setTextColor(WHITE, tft.color565(87, 146, 255));
  tft.print(readads1115_O2());                               //fio2 sensor
  if (readads1115_O2() <= 411)
  {
    tft.print(" ");
  }
  if (cmh2o_function() < 0)
  {
    pressure = 0;
  }
  tft.setCursor(303, 230);
  tft.setTextColor(WHITE, tft.color565(87, 146, 255));
  tft.print(cmh2o_function());
  if (cmh2o_function() <= 200)
  {
    tft.print(" ");
  }
  tft.setCursor(102, 230);
  tft.setTextColor(WHITE, tft.color565(87, 146, 255));
  tft.print(xgzp6894d_temperature());
}

void default_values()
{
  required_air = 0.0;
  o2_alone = 0.0;
  send_o2_pwm = 0.0;
  digitalWrite(Buzzer, LOW);
  pwm_function();
  // pwm_function2();
}
void loop() {
  menu();
  readRotaryEncoder();
  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    switch (b) {
      case ClickEncoder::Clicked:
        middle = true;
        break;
    }
  }
  if ((up && page == 1) || (up && page == 7)) {
    up = false;

    lastMenuItem = menuitem;
    menuitem--;
    if (menuitem == 0)
    {
      menuitem = 1;
    }
  }
  else if (up && page == 3 && menuitem == 2 && menuitem_2 == 1) {
    up = false;
    FLOW_VALUE2--;
    if (FLOW_VALUE2 <= 10)
    {
      FLOW_VALUE2 = 10;
    }
  }
  else if (up && page == 3 && menuitem == 2 && menuitem_2 == 2) {
    up = false;
    FLOW_VALUE--;
    if (FLOW_VALUE <= 0)
    {
      FLOW_VALUE = 0;
    }
  }
  else if (up && page == 5 && menuitem == 1 && menuitem_3 == 1) {
    up = false;
    temperature_value--;

    if (temperature_value <= 27)
    {
      temperature_value = 27;
    }
  }
  else if (up && page == 5 && menuitem == 1 && menuitem_3 == 2) {
    up = false;
    humidity_value--;

    if (humidity_value <= 0)
    {
      humidity_value = 0;
    }
  }
  else if (up && page == 5 && menuitem == 1 && menuitem_3 == 3) {
    up = false;

    menuitem_4--;
    Serial.println(String ("menuitem_4     ") + menuitem_4);
    if (menuitem_4 == 0)
    {
      menuitem_4 = 1;
    }
  }
  else if (up && page == 6 && menuitem == 3) {
    up = false;
    FIO2_VALUE--;
    if (FIO2_VALUE <= 21)
    {
      FIO2_VALUE = 21;
    }
  }
  else if ((up && page == 2) || (up && page == 7))  {
    up = false;

    lastMenuItem_2 = menuitem_2;
    menuitem_2--;
    if (menuitem_2 == 0)
    {
      menuitem_2 = 1;
    }
  }
  else if (up && page == 4) {
    up = false;

    lastMenuItem_3 = menuitem_3;
    menuitem_3--;
    if (menuitem_3 == 0)
    {
      menuitem_3 = 1;
    }
  }
  else if ((down && page == 1) || (down && page == 7))  //We have turned the Rotary Encoder Clockwise
  {
    down = false;
    lastMenuItem = menuitem;
    menuitem++;
    if (menuitem == 5)
    {
      menuitem--;
    }
  }
  else if (down && page == 3 && menuitem == 2 && menuitem_2 == 1) {
    down = false;
    FLOW_VALUE2++;
    if (FLOW_VALUE2 > 100)
    {
      FLOW_VALUE2 = 100;
    }
  }
  else if (down && page == 3 && menuitem == 2 && menuitem_2 == 2) {
    down = false;
    FLOW_VALUE++;
    Serial.println(String ("FLOW_VALUE      ") + FLOW_VALUE);
    if (FLOW_VALUE > 20)
    {
      FLOW_VALUE = 20;
    }
  }
  else if (down && page == 5 && menuitem == 1 && menuitem_3 == 1) {
    down = false;
    temperature_value++;

    if (temperature_value >= 37)
    {
      temperature_value = 37;
    }
  }
  else if (down && page == 5 && menuitem == 1 && menuitem_3 == 2) {
    down = false;
    humidity_value++;
    if (humidity_value >= 90)
    {
      humidity_value = 90;
    }
  }
  else if (down && page == 5 && menuitem == 1 && menuitem_3 == 3) {
    down = false;

    menuitem_4++;
    Serial.println(String ("menuitem_4     ") + menuitem_4);
    if (menuitem_4 == 4)
    {
      menuitem_4--;
    }
  }
  else if (down && page == 6 && menuitem == 3) {
    down = false;
    FIO2_VALUE++;
    if (FIO2_VALUE <= 21)
    {
      FIO2_VALUE = 21;
    }
    else if (FIO2_VALUE > 100)
    {
      FIO2_VALUE = 100;
    }
  }
  else if ((down && page == 2) || (down && page == 7)) //We have turned the Rotary Encoder Clockwise
  {
    down = false;
    lastMenuItem_2 = menuitem_2;
    menuitem_2++;
    if (menuitem_2 == 4)
    {
      menuitem_2--;
    }
  }
  else if (down && page == 4) //We have turned the Rotary Encoder Clockwise
  {
    down = false;
    lastMenuItem_3 = menuitem_3;
    menuitem_3++;
    if (menuitem_3 == 5)
    {
      menuitem_3--;
    }
  }
  if (middle) //Middle Button is Pressed
  {
    middle = false;
    if (((page == 1 || page == 7)) && (menuitem > 1 && menuitem < 3)) {
      tft.drawFastVLine(240, 285, 35, BLACK);  // mainmenu vertical darkness
      tft.drawFastVLine(241, 285, 35, BLACK);  // mainmenu vertical darkness
      tft.drawFastVLine(375, 285, 35, BLACK);  // mainmenu vertical darkness
      tft.drawFastVLine(374, 285, 35, BLACK);  // mainmenu vertical darkness
      tft.fillRect(87, 286, 152, 67, tft.color565(137, 146, 153));
      tft.fillRect(242, 286, 131, 67, tft.color565(137, 146, 153));
      tft.fillRect(376, 286, 119, 67, tft.color565(137, 146, 153));
      page = 2;
    }
    else if (page == 2 && menuitem == 1)
    {
      page = 1;
    }
    else if (((page == 2 || page == 7)) && (menuitem == 2 && menuitem_2 == 1))
    {
      page = 3;
    }
    else if (((page == 2 || page == 7)) && (menuitem == 2 && menuitem_2 == 2))
    {
      page = 3;
    }
    else if (((page == 2 || page == 7)) && (menuitem == 2 && menuitem_2 == 3))
    {
      tft.fillRect(86, 286, 400, 67, tft.color565(137, 146, 153));
      tft.fillRect(0, 256, 84, 81, tft.color565(137, 146, 153)); // box 4
      menuItem4 = "START";
      page = 1;
    }
    else if (page == 3 && menuitem == 2 && menuitem_2 == 1)
    {

      page = 2;
    }
    else if (page == 3 && menuitem == 2 && menuitem_2 == 2)
    {

      page = 2;
    }
    else if (((page == 1 || page == 7)) && (menuitem == 3))
    {
      tft.fillRect(86, 286, 400, 67, tft.color565(137, 146, 153));
      page = 6;
    }
    else if (page == 6 && menuitem == 3)
    {
      tft.fillRect(0, 256, 84, 81, tft.color565(137, 146, 153)); // box 4
      menuItem4 = "START";
      page = 1;
    }
    else if (page == 1 && menuitem == 4)
    {
      Serial.println("***********************A*********************");
      tft.fillRect(86, 286, 400, 67, tft.color565(137, 146, 153));
      tft.fillRect(0, 256, 84, 81, tft.color565(137, 146, 153)); // box 4
      menuItem4 = "STANDBY";
      page = 7;
      menu2();
    }
    else if (page == 7 && menuitem == 4)
    {
      Serial.println("start");
      tft.fillRect(86, 286, 400, 67, tft.color565(137, 146, 153)); // erase high flow low flow
      tft.fillRect(0, 256, 84, 81, tft.color565(137, 146, 153)); // box 4
      menuItem4 = "START";
      page = 1;
      menu2();
      tft.fillRoundRect(100, 63, 110, 40, 5, tft.color565(87, 146, 255)); //clear and print flow sensor data
      tft.fillRoundRect(301, 63, 110, 40, 5, tft.color565(87, 146, 255));  // clear and print oxygen sensor data
    }
    else if (((page == 7 || page == 1)) && (menuitem == 1))
    {
      tft.fillRect(40, 33, 399, 250, WHITE);
      tft.fillRect(225, 215, 100, 57, tft.color565(87, 146, 255)); // air pressure sensor blue box
      tft.fillRect(330, 215, 100, 57, tft.color565(87, 146, 255)); // o2 pressure sensor blue box
      tft.fillRect(225, 182, 100, 47, tft.color565(137, 146, 153)); // air pressure black box
      tft.fillRect(330, 182, 100, 47, tft.color565(137, 146, 153)); // o2 pressure black box
      tft.drawFastHLine(225, 230, 100, BLACK); // air pressure black line
      tft.drawFastHLine(225, 229, 100, BLACK); // air pressure black line
      tft.drawFastHLine(330, 230, 100, BLACK); // o2 pressure black line
      tft.drawFastHLine(330, 229, 100, BLACK); // o2 pressure black line
      tft.drawRect(38, 32, 402, 252, BLACK); //outer line
      tft.drawFastVLine(37, 31, 252, BLACK); // outer line
      tft.drawFastVLine(36, 31, 252, BLACK); // outer line
      tft.drawFastVLine(440, 31, 252, BLACK); // outer line
      tft.fillRect(39, 32, 400, 30, tft.color565(137, 146, 153));  //menu box
      tft.drawFastHLine(38, 62, 402, BLACK); // outer line
      tft.drawFastHLine(38, 63, 402, BLACK); // inner line
      tft.fillRect(45, 70, 170, 100, tft.color565(87, 146, 255)); // air required box
      tft.fillRect(45, 177, 170, 100, tft.color565(87, 146, 255)); // o2 required box
      tft.fillRect(45, 70, 170, 30, tft.color565(137, 146, 153)); // air black box
      tft.fillRect(45, 177, 170, 30, tft.color565(137, 146, 153)); // air black box
      tft.drawFastHLine(45, 100, 170, BLACK); // air inner line
      tft.drawFastHLine(45, 101, 170, BLACK); // air inner line
      tft.drawFastHLine(45, 205, 170, BLACK);  // o2 inner line
      tft.drawFastHLine(45, 206, 170, BLACK); // o2 inner line
      tft.setCursor(60, 40);
      tft.print("MENU");
      tft.setCursor(60, 80);
      tft.setTextColor(BLACK);
      tft.print(String ("AIR REQUIRED"));
      tft.setCursor(55, 185);
      tft.setTextColor(BLACK);
      tft.print(String ("FIO2 REQUIRED"));
      tft.setCursor(176, 146);
      tft.setTextColor(WHITE);
      tft.print(String ("LPM"));
      tft.setCursor(176, 254);
      tft.setTextColor(WHITE);
      tft.print(String ("LPM"));
      tft.fillRoundRect(222, 73, 212, 105, 4, tft.color565(137, 146, 153)); // temp , hum fillroundrect
      tft.drawRoundRect(220, 71, 214, 206, 5, BLACK); // temp , hum drawroundrect
      tft.drawRoundRect(221, 72, 212, 204, 4, BLACK);
      tft.drawFastHLine(222, 107, 210, BLACK);  // TEMP inner line
      tft.drawFastHLine(222, 108, 210, BLACK); // TEMP inner line
      tft.drawFastHLine(222, 143, 210, BLACK);  // HUM inner line
      tft.drawFastHLine(222, 144, 210, BLACK); // HUM inner line
      tft.drawFastVLine(393, 32, 30, BLACK); // back inner line
      tft.drawFastVLine(394, 32, 30, BLACK); // back inner line
      tft.setCursor(415, 85);
      tft.setTextColor(BLACK);
      tft.print(String ("C"));
      tft.setCursor(404, 75);
      tft.setTextColor(BLACK);
      tft.print(String ("o"));
      tft.setCursor(256, 187);
      tft.setTextColor(BLACK);
      tft.print(String ("AIR"));
      tft.setCursor(230, 210);
      tft.setTextColor(BLACK);
      tft.print(String ("PRESSURE"));
      tft.setCursor(370, 187);
      tft.setTextColor(BLACK);
      tft.print(String ("O"));
      tft.setCursor(382, 189);
      tft.setTextColor(BLACK);
      tft.print(String ("2"));
      tft.setCursor(335, 210);
      tft.setTextColor(BLACK);
      tft.print(String ("PRESSURE"));
      tft.fillRoundRect(367, 83, 35, 20, 5, tft.color565(137, 146, 153));
      tft.setCursor(368, 85);
      tft.print(temp_last_value);
      tft.fillRoundRect(367, 117, 35, 20, 5, tft.color565(137, 146, 153));
      tft.setCursor(368, 119);
      tft.print(humidity_last_value);
      tft.fillRect(366, 151, 40, 20, tft.color565(137, 146, 153));
      tft.setCursor(368, 153);
      tft.print(lastMenuItem_4);
      send_as_input(x, y);
      page = 4;
    }
    else if (page == 4 && menuitem_3 == 1 && menuitem == 1)
    {
      tft.fillRoundRect(367, 83, 35, 20, 5, tft.color565(137, 146, 153)); // temperature setting count clear rectangle
      page = 5;
    }
    else if (page == 4 && menuitem_3 == 2 && menuitem == 1)
    {
      tft.fillRoundRect(367, 117, 35, 20, 5, tft.color565(137, 146, 153)); // humidity setting count clear rectangle
      page = 5;
    }
    else if (page == 4 && menuitem_3 == 3 && menuitem == 1)
    {
      page = 5;
    }
    else if (page == 5 && menuitem_3 == 1 && menuitem == 1)
    {
      page = 4;
    }
    else if (page == 5 && menuitem_3 == 2 && menuitem == 1)
    {
      page = 4;
    }
    else if (page == 5 && menuitem_3 == 3 && menuitem == 1 && menuitem_4 == 1)
    {
      page = 4;
    }
    else if (page == 5 && menuitem_3 == 3 && menuitem == 1 && menuitem_4 == 2)
    {
      page = 4;
    }
    else if (page == 4 && menuitem_3 == 4 && menuitem == 1)
    {
      tft.fillScreen(0xFFFF);
      set_up();
      menu();
      printSensorData();
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.fillRoundRect(205, 105, 70, 40, 5, tft.color565(159, 171, 180));
      tft.setCursor(215, 114);
      tft.print(last_value);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.fillRoundRect(400, 105, 70, 40, 5, tft.color565(159, 171, 180));
      tft.setCursor(410, 114);
      tft.print(last_value2);
      page = 7;
    }

  }
  Serial.println(String ("page ") + page);
}
void menu()
{
  if (page == 1 ||  page == 7)
  {
    printSensorData();
    mysensor.readSensor(temperature, pressure);
    if (menuitem == 1)
    {
      displayMenuItem(menuItem1, 2, 62, true);
      displayMenuItem(menuItem2, 2, 137, false);
      displayMenuItem(menuItem3, 2, 210, false);
      displayMenuItem(menuItem4, 2, 282, false);
    }
    else if (menuitem == 2)
    {
      displayMenuItem(menuItem1, 2, 62, false);
      displayMenuItem(menuItem2, 2, 137, true);
      displayMenuItem(menuItem3, 2, 210, false);
      displayMenuItem(menuItem4, 2, 282, false);
    }
    else if (menuitem == 3)
    {
      displayMenuItem(menuItem1, 2, 62, false);
      displayMenuItem(menuItem2, 2, 137, false);
      displayMenuItem(menuItem3, 2, 210, true);
      displayMenuItem(menuItem4, 2, 282, false);
    }
    else if (menuitem == 4)
    {
      displayMenuItem(menuItem1, 2, 62, false);
      displayMenuItem(menuItem2, 2, 137, false);
      displayMenuItem(menuItem3, 2, 210, false);

      displayMenuItem(menuItem4, 2, 282, true);
    }
  }
  else if (((page == 2 || page == 7)) && (menuitem == 2))
  {

    if (((page == 2 || page == 7)) && (menuitem == 2 && menuitem_2 == 1))
    {

      tft.setTextSize(2);
      displayMenuItem_2(menuItem6, 110, 295, true);
      displayMenuItem_2(menuItem7, 260, 295, false);
      displayMenuItem_2(menuItem8, 400, 295, false);
    }
    else if (((page == 2 || page == 7)) && (menuitem == 2 && menuitem_2 == 2))
    {

      tft.setTextSize(2);
      displayMenuItem_2(menuItem6, 110, 295, false);
      displayMenuItem_2(menuItem7, 260, 295, true);
      displayMenuItem_2(menuItem8, 400, 295, false);
    }
    else if (((page == 2 || page == 7)) && (menuitem == 2 && menuitem_2 == 3))
    {
      // pwm_function();
      tft.setTextSize(2);
      displayMenuItem_2(menuItem6, 110, 295, false);
      displayMenuItem_2(menuItem7, 260, 295, false);
      displayMenuItem_2(menuItem8, 400, 295, true);
    }
  }
  else if (page == 4 && menuitem == 1)
  {

    if (page == 4 && menuitem == 1 && menuitem_3 == 1)
    {
      tft.setTextSize(2);
      displayMenuItem_2(menuItem9, 225, 85, true);
      displayMenuItem_2(menuItem10, 225, 120, false);
      displayMenuItem_2(menuItem11, 225, 154, false);
      displayMenuItem_2(menuItem12, 410, 38, false);
    }
    else if (page == 4 && menuitem == 1 && menuitem_3 == 2)
    {
      tft.setTextSize(2);
      displayMenuItem_2(menuItem9, 225, 85, false);
      displayMenuItem_2(menuItem10, 225, 120, true);
      displayMenuItem_2(menuItem11, 225, 154, false);
      displayMenuItem_2(menuItem12, 410, 38, false);
    }
    else if (page == 4 && menuitem == 1 && menuitem_3 == 3)
    {
      tft.setTextSize(2);
      displayMenuItem_2(menuItem9, 225, 85, false);
      displayMenuItem_2(menuItem10, 225, 120, false);
      displayMenuItem_2(menuItem11, 225, 154, true);
      displayMenuItem_2(menuItem12, 410, 38, false);
    }
    else if (page == 4 && menuitem == 1 && menuitem_3 == 4)
    {
      tft.setTextSize(2);
      displayMenuItem_2(menuItem9, 225, 85, false);
      displayMenuItem_2(menuItem10, 225, 120, false);
      displayMenuItem_2(menuItem11, 225, 154, false);
      displayMenuItem_2(menuItem12, 410, 38, true);
    }
  }
  else if (page == 6 && menuitem == 3)
  {

    y = displayIntMenuPage_2(FIO2_VALUE);
  }

  else if (page == 3 && menuitem == 2 && menuitem_2 == 1)
  {

    tft.setTextSize(2);
    x = displayIntMenuPage(FLOW_VALUE2);
  }
  else if (page == 3 && menuitem == 2 && menuitem_2 == 2)
  {

    tft.setTextSize(2);
    x = displayIntMenuPage(FLOW_VALUE);
  }
  else if (page == 5 && menuitem == 1 && menuitem_3 == 1)
  {
    send_temp(temperature_value);
  }
  else if (page == 5 && menuitem == 1 && menuitem_3 == 2)
  {
    send_humidity(humidity_value);
  }
  else if (page == 5 && menuitem == 1 && menuitem_3 == 3 && menuitem_4 == 1)
  {
    tft.fillRect(366, 151, 40, 20, tft.color565(137, 146, 153));
    displayMenuItem_2(menuItem13, 368, 153, true);

    lastMenuItem_4 = menuItem13;
  }
  else if (page == 5 && menuitem == 1 && menuitem_3 == 3 && menuitem_4 == 2)
  {
    tft.fillRect(366, 151, 40, 20, tft.color565(137, 146, 153));
    displayMenuItem_2(menuItem14, 368, 153, true);
    lastMenuItem_4 = menuItem14;
  }
}
void menu2()
{
  if (page == 7 && menuitem == 4)
  {


    send_as_input(x, y);
    pwm_function();
    //pwm_function2();
    mysensor.readSensor(temperature, pressure);
    Serial.println(String ("send_o2_pwm  ") + send_o2_pwm);
    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&start&&&&&&&&&&&&&&&&");

  }
  else if (page == 1  && menuitem == 4)
  {

    default_values();
  }
}
