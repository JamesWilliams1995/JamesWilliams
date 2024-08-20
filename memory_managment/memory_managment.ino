#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <FreeDefaultFonts.h>

#include <TimerOne.h>
unsigned long lastButtonPressTime = 0;
unsigned long lastShortPressTime = 0;
unsigned int shortPressCount = 0;
#define LONG_PRESS_DURATION_5S 5000 // 5 seconds
#define LONG_PRESS_DURATION_10S 10000
#define SHORT_PRESS_WINDOW 2000 // 2 seconds
#define FADE_DURATION 3000 // 3 seconds
#define LED_BLINK_COUNT 3
#define MINPRESSURE 10
#define MAXPRESSURE 1000

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

#define ledPin 49    // white warm
#define ledPin_yellow 53    // white warm

const int XP = 8, XM = A2, YP = A3, YM = 9; //ID=0x9486
const int TS_LEFT = 955, TS_RT = 98, TS_TOP = 907, TS_BOT = 133;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

int pixel_x = -1, pixel_y = -1; // Initial invalid values
int menuitem = 0;

String menuItems[] = {"ON", "OFF", "UP", "DOW", "UP", "DOW", "COLD", "WARM"};
boolean menuStates[] = {true, true}; // ON, OFF
boolean ModeSelect[] = {false, false};

bool touchState = false;
bool longPressHandled = false;  // Track if long press action is handled

bool currentState = false;
bool lastState = false;

unsigned long pressTime = 0;
unsigned long releaseTime = 0;

struct DisplayItem {
  int x, y;
  String label;
};
DisplayItem Title[] = {
  {0, 50,  "Intensity  :"},
  {0, 110, "Cold White :"},
  {0, 170, "WARM YELLOW:"},
  {0, 250, "MODE SELECT:"}
};
struct Button {
  int x, y, w, h;
  String label;
};

Button buttons[] = {
  {240, 40, 100, 50, "ON"},
  {350, 40, 100, 50, "OFF"},
  {240, 100, 100, 50, "UP"},
  {350, 100, 100, 50, "DOW"},
  {240, 160, 100, 50, "UP"},
  {350, 160, 100, 50, "DOW"},
  {240, 230, 100, 80, "COLD"},
  {350, 230, 100, 80, "WARM"}
};

boolean Touch_getXY(void) {
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);      // restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);   // because TFT control pins
  digitalWrite(XM, HIGH);
  bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);

  if (pressed) {
    pixel_x = map(p.x, TS_LEFT, TS_RT, 0, 480);
    pixel_y = map(p.y, TS_TOP, TS_BOT, 0, 320);

      Serial.print(String("pixel_x  ") + pixel_x);
      Serial.println(String("pixel_y ") + pixel_y);
  } else {
    pixel_x = -1;
    pixel_y = -1;
  }
  return pressed;
}

void setupDisplay() {
  tft.drawFastHLine(0, 30, 480, BLACK);  // main menu top horizontal line
  tft.drawFastHLine(0, 31, 480, BLACK);  // main menu top horizontal darkness line to line
  tft.fillRect(0, 0, 480, 31, BLACK);    // horizontal black
  tft.fillRect(0, 0, 480, 30, tft.color565(192, 192, 192));  // setting & monitoring top horizontal
  tft.setCursor(90, 5);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("OT LIGHT CONTROLLER");

  for (Button b : buttons) {
    tft.fillRoundRect(b.x, b.y, b.w, b.h, 5, tft.color565(87, 146, 255));
    tft.setCursor(b.x + 30, b.y + 10);
    tft.setTextSize(3);
    tft.setTextColor(BLACK);
    tft.print(b.label);
  }
  for (DisplayItem c : Title) {
    tft.setCursor(c.x + 10, c.y + 10);
    tft.setTextSize(3);
    tft.setTextColor(BLACK);
    tft.print(c.label);
  }
}

void displayMenuItem(String item, int x, int y, boolean selected) {
  tft.setTextSize(3);
  tft.setTextColor(selected ? YELLOW : BLACK);
  tft.setCursor(x, y);
  tft.print(item);
}

void main_select() {
  for (int i = 0; i < 8; i++) {
    displayMenuItem(menuItems[i], buttons[i].x + 30, buttons[i].y + 10, menuitem == i + 1);
  }
}

void handleButtonPress(int i) {
  switch (i) {
    case 1:
      digitalWrite(ledPin, LOW);
      digitalWrite(ledPin_yellow, LOW);
      Serial.println("LED ON");
      break;
    case 2:
      digitalWrite(ledPin, LOW);
      digitalWrite(ledPin_yellow, LOW);
      Serial.println("LAED OFF");
      break;
    case 7:

      tft.fillRoundRect(240, 230, 100, 80, 5, tft.color565(0, 255, 0));      // ONLY COLD
      tft.setCursor(270, 240);
      tft.setTextSize(3);
      tft.setTextColor(BLACK);
      tft.print(String ("COLD"));

      tft.fillRoundRect(350, 230, 100, 80, 5, tft.color565(87, 146, 255));      // ONLY WARM
      tft.setCursor(380, 240);
      tft.setTextSize(3);
      tft.setTextColor(BLACK);
      tft.print(String ("WARM"));
      break;


    case 8:

      tft.fillRoundRect(240, 230, 100, 80, 5, tft.color565(87, 146, 255));      // ONLY COLD
      tft.setCursor(270, 240);
      tft.setTextSize(3);
      tft.setTextColor(BLACK);
      tft.print(String ("COLD"));

      tft.fillRoundRect(350, 230, 100, 80, 5, tft.color565(0, 255, 0));      // ONLY WARM
      tft.setCursor(380, 240);
      tft.setTextSize(3);
      tft.setTextColor(BLACK);
      tft.print(String ("WARM"));

      break;
  }
}

void longPressButton() {
  switch (menuitem) {
    case 3:
      digitalWrite(ledPin, LOW);
      Serial.println("UP");
      Serial.println("up_");
      break;
    case 4:
      digitalWrite(ledPin, LOW);
      Serial.println("DOWN");
      break;
  }
}

void setup(void) {
  pinMode(ledPin_yellow, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin_yellow, OUTPUT);
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledPin_yellow, HIGH);
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  if (ID == 0xD3D3) ID = 0x9486; // write-only shield
  tft.begin(ID);
  tft.setRotation(1);            // PORTRAIT
  tft.fillScreen(WHITE);
  setupDisplay();
}

void loop(void) {
   Touch_getXY();
  int turns = 0;
  TSPoint T = ts.getPoint();
 
  int longPressed = (T.z > MINPRESSURE && T.z < MAXPRESSURE);
  
  unsigned long currentTime = millis();
  if (longPressed) {

    if (pixel_x != -1 && pixel_y != -1) {
      if (((pixel_x > 94 && pixel_x < 180 && pixel_y > 188 && pixel_y <= 200)) && menuStates[0]) { // ON STATE
        menuitem = 1;
        menuStates[0] = false;
        menuStates[1] = true;

        if (currentTime - lastButtonPressTime >= SHORT_PRESS_WINDOW) {
          handleButtonPress(menuitem);
          Serial.print("Button ");
          Serial.print(buttons[0].label);
          Serial.println(" pressed");
        }
        lastButtonPressTime = currentTime;
      } else if (((pixel_x > 100 && pixel_x < 180 && pixel_y > 200 && pixel_y < 300)) && menuStates[1]) { // OFF STATE
        menuitem = 2;
        menuStates[0] = true;
        menuStates[1] = false;
        if (currentTime - lastButtonPressTime >= SHORT_PRESS_WINDOW) {
          handleButtonPress(menuitem);
          Serial.print("Button ");
          Serial.print(buttons[1].label);
          Serial.println(" pressed");
        }
        lastButtonPressTime = currentTime;
      }


      else if ((pixel_x > 300 && pixel_x < 409) && (pixel_y > 100 && pixel_y < 250 ) && !ModeSelect[0])
      {
        menuitem = 7;
        Serial.print("modeselect_cold");
        ModeSelect[0] = true;
        ModeSelect[1] = false;
        handleButtonPress(menuitem);

      }


      else if ((pixel_x > 320 && pixel_x < 480) && (pixel_y > 200 && pixel_y < 300 ) &&  !ModeSelect[1])
      {
        menuitem = 8;
        Serial.print("welcome_modeselect_warm");
        ModeSelect[0] = false;
        ModeSelect[1] = true;
        handleButtonPress(menuitem);

      }


      main_select();
    }

  }


  if (ModeSelect[0])
  {
    //Serial.print("welcom");
    while (turns < 65) {
      bool  ColdWhiteUp = Touch_getXY();
      if ((ColdWhiteUp == true && pixel_x > 190 && pixel_x < 230 && pixel_y > 190 && pixel_y < 250) && ModeSelect[0]) {
        menuitem = 3;
        currentState = true;
        break;
      }
      else if (ColdWhiteUp == true && (pixel_x > 195 && pixel_x < 230 && pixel_y > 250 && pixel_y < 300) && ModeSelect[0]) {
        menuitem = 4;
        currentState = true;
        break;
      }
      currentState = false;
      turns = turns + 1;
    }

    //measure when it is pressed and released
    if (lastState == false && currentState == true) {
      pressTime = millis();
      digitalWrite(ledPin, LOW);
      Serial.println("Touch Pressed");
      main_select();
    } else if (lastState == true && currentState == false) {
      releaseTime = millis();
      digitalWrite(ledPin, HIGH);
      Serial.println("Touch Released");

    }
    lastState = currentState;
  }


  else if (ModeSelect[1])
  {
    //Serial.print("welcom");
    while (turns < 65) {
      bool  ColdWhiteUp = Touch_getXY();
      if ((ColdWhiteUp == true && pixel_x > 270 && pixel_x < 300 && pixel_y > 170 && pixel_y < 250 ) && ModeSelect[1]) {
        menuitem = 5;
        currentState = true;
        break;
      }
      else if ((ColdWhiteUp == true && pixel_x > 270 && pixel_x < 300 && pixel_y > 200 && pixel_y < 300 ) && ModeSelect[1]) {
        menuitem = 6;
        currentState = true;
        break;
      }
      currentState = false;
      turns = turns + 1;
    }


    //measure when it is pressed and released
    if (lastState == false && currentState == true) {
      pressTime = millis();
      digitalWrite(ledPin_yellow, LOW);
      Serial.println("Touch Pressed_warm");
      main_select();
    } else if (lastState == true && currentState == false) {
      releaseTime = millis();
      digitalWrite(ledPin_yellow, HIGH);
      Serial.println("Touch Released_warm");

    }
    lastState = currentState;
  }











  else {
    digitalWrite(ledPin_yellow, HIGH);
    digitalWrite(ledPin, HIGH);
    //Serial.println(longPressed);
    longPressHandled = false;  // Reset the long press handled state when button is released
  }
  delay(500);
}
