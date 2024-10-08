#include <ESP8266WiFi.h>
#include<SoftwareSerial.h>
SoftwareSerial ss(D1, D2);
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h" 
String tdata, hdata, bpdata, f1data, f2data;
int count = 0, count1 = 0, count2 = 0, count3 = 0,  count4 = 0, uvc = 0;
#define WLAN_SSID       "M1788M1788"
#define WLAN_PASS       "12345678"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "M1788M1788"
#define AIO_KEY         " "

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish location = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/log");
Adafruit_MQTT_Publish hb1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/heart beat");
Adafruit_MQTT_Publish spo21 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/spo2");
Adafruit_MQTT_Publish temp1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish speed1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/speed");

Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");
Adafruit_MQTT_Subscribe onoffbutton1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/relay1");
Adafruit_MQTT_Subscribe onoffbutton2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/relay2");
//Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();
char tdata1[50];
char hdata1[5];
char bpdata1[10];
char f1data1[5];
char f2data1[5];
void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);
  delay(10);

  Serial.println(F("Adafruit MQTT"));
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  digitalWrite(D4, HIGH);
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  mqtt.subscribe(&onoffbutton);
  mqtt.subscribe(&onoffbutton1);
  mqtt.subscribe(&onoffbutton2);
}

void loop() {

  MQTT_connect();
  count = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
  count4 = 0;
  tdata = "";
  hdata = "";
  bpdata = "";
  f1data = "";
  f2data = "";
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    // Serial.print(c);
    if (c == '*')
    {
      while (Serial.available() > 0)
      {
        char t = Serial.read();
        if (count == 50)
        {
          break;
        }
        if (t == '#') {
          break;
        }
        tdata += t;
        count++;
      }
    }
    if (c == '@')
    {
      while (Serial.available() > 0)
      {
        char h = Serial.read();
        if (count1 == 2)
        {
          break;
        }
        if (h == '#') {
          break;
        }
        hdata += h;
        count1++;
      }
    }
    if (c == '$')
    {
      while (Serial.available() > 0)
      {
        char u = Serial.read();
        if (count2 == 4)
        {
          break;
        }
        if (u == '#') {
          break;
        }
        bpdata += u;
        count2++;
      }
    }
    if (c == '^')
    {
      while (Serial.available() > 0)
      {
        char v = Serial.read();
        if (count3 == 3)
        {
          break;
        }
        if (v == '#') {
          break;
        }
        f1data += v;
        count3++;
      }
    }
    if (c == '&')
    {
      while (Serial.available() > 0)
      {
        char l = Serial.read();
        if (count3 == 3)
        {
          break;
        }
        if (l == '#') {
          break;
        }
        f2data += l;
        count4++;
      }
    }
  }

  if ( tdata.length() > 0 )
  {
    for (int i = 0; i < 50; i++) {
      tdata1[i] = tdata[i];
    }

    Serial.println(tdata1);
    location.publish(tdata1);
    digitalWrite(D4, HIGH);
    delay(1000);
    digitalWrite(D4, LOW);
    tdata = "";

    delay(2000);
  }

  if ( hdata.length() > 0 )
  {
    for (int i = 0; i < 5; i++) {
      hdata1[i] = hdata[i];
    }
    Serial.println(hdata1);
    hb1.publish(hdata1);
    digitalWrite(D4, HIGH);
    delay(1000);
    digitalWrite(D4, LOW);
    hdata = "";
    delay(2000);
  }
  if ( bpdata.length () > 0 )
  {
    for (int i = 0; i < 5; i++) {
      bpdata1[i] = bpdata[i];
    }

    Serial.println(bpdata1);
    spo21.publish(bpdata1);
    digitalWrite(D4, HIGH);
    delay(1000);
    digitalWrite(D4, LOW);
    bpdata = "";
    delay(2000);
  }
  if ( f1data.length () > 0 )
  {
    for (int i = 0; i < 5; i++) {
      f1data1[i] = f1data[i];
    }

    Serial.println(f1data1);
    temp1.publish(f1data1);
    digitalWrite(D4, HIGH);
    delay(1000);
    digitalWrite(D4, LOW);
    f1data = "";
    delay(2000);
  }
  if ( f2data.length () > 0 )
  {
    for (int i = 0; i < 5; i++) {
      f2data1[i] = f2data[i];
    }
    Serial.println(f2data );
    speed1.publish(f2data1);
    digitalWrite(D4, HIGH);
    delay(1000);
    digitalWrite(D4, LOW);
    f1data = "";
    delay(2000);
  }
  tdata = "";
  hdata = "";
  bpdata = "";
  f1data = "";
  f2data = "";
  count = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
  count4 = 0;
  delay(100); // ThingSpeak will only accept updates every 15 seconds.


  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
      if (strcmp((char *)onoffbutton.lastread, "ON") == 0) {
        Serial.println("D0 ON");
        digitalWrite(D0, HIGH);
      }
      if (strcmp((char *)onoffbutton.lastread, "OFF") == 0) {
        Serial.println("D0 OFF");
        digitalWrite(D0, LOW);
      }
    }
    if (subscription == &onoffbutton1) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton1.lastread);
      if (strcmp((char *)onoffbutton1.lastread, "ON") == 0) {
        Serial.println("D1 ON");
        ss.write('1');

      }
      if (strcmp((char *)onoffbutton1.lastread, "OFF") == 0) {
        Serial.println("D1 OFF");
        ss.write('2');

      }
    }
    if (subscription == &onoffbutton2) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton2.lastread);
      if (strcmp((char *)onoffbutton2.lastread, "ON") == 0) {
        ss.write('3');
      }
      if (strcmp((char *)onoffbutton2.lastread, "OFF") == 0) {
        ss.write('4');
      }
    }
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  digitalWrite(D4, HIGH);
}
