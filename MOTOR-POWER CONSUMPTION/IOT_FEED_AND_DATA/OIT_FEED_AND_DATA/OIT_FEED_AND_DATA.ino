#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include<SoftwareSerial.h>
SoftwareSerial ss(D1, D2);//rx tx
/************************* WiFi Access Point *********************************/
String tdata, hdata, smdata, rsdata;
int count = 0, count1 = 0, count2 = 0, count3 = 0;
#define WLAN_SSID       "E1236"
#define WLAN_PASS       "12345678"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "dumy"
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
Adafruit_MQTT_Publish FEED = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/info");
Adafruit_MQTT_Publish ph = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/ph");
Adafruit_MQTT_Publish waterflow = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/water");
Adafruit_MQTT_Publish Voltage = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/volt");

Adafruit_MQTT_Subscribe mode0 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/mode0");


//Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();
char tdata1[5];
char hdata1[5];
char smdata1[5];
char rsdata1[5];
void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  pinMode(D1, OUTPUT);
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

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  mqtt.subscribe(&mode0);
}

void loop() {

  MQTT_connect();
  count = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
  tdata = "";
  hdata = "";
  smdata = "";
  rsdata = "";
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    // Serial.print(c);
    if (c == '@')
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
        tdata = tdata + t;
        count++;
      }
    }
    if (c == '%')
    {
      while (Serial.available() > 0)
      {
        char h = Serial.read();
        if (count1 == 3)
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
    if (c == '*')
    {
      while (Serial.available() > 0)
      {
        char  sm= Serial.read();
        if (count2 == 50)
        {
          break;
        }
        if (sm == '#') {
          break;
        }
        smdata += sm;
        count2++;
      }
    }
    if (c == '^')
    {
      while (Serial.available() > 0)
      {
        char rs = Serial.read();
        if (count3 == 3)
        {
          break;
        }
        if (rs == '#') {
          break;
        }
        rsdata += rs;
        count3++;
      }
    }
  }

  if ( tdata.length() > 0 )
  {
    for (int i = 0; i <3; i++) {
      tdata1[i] = tdata[i];
    }

    Serial.println(tdata1);
    ph.publish(tdata1);
    digitalWrite(D4, HIGH);
    delay(1000);
    digitalWrite(D4, LOW);
    tdata = "";

    delay(2000);
  }

  if ( hdata.length() > 0 )
  {
    for (int i = 0; i < 3; i++) {
      hdata1[i] = hdata[i];
    }
    Serial.println(hdata1);
    waterflow.publish(hdata1);
    digitalWrite(D4, HIGH);
    delay(1000);
    digitalWrite(D4, LOW);
    hdata = "";
    delay(2000);
  }
  if ( smdata.length () > 0 )
  {
    for (int i = 0; i < 50; i++) {
      smdata1[i] = smdata[i];
    }

    Serial.println(smdata1);
    FEED.publish(smdata1);
    digitalWrite(D4, HIGH);
    delay(1000);
    digitalWrite(D4, LOW);
    smdata = "";
    delay(2000);
  }
  if ( rsdata.length () > 0 )
  {
    for (int i = 0; i < 2; i++) {
      rsdata1[i] = rsdata[i];
    }

    Serial.println(rsdata1);
    Voltage.publish(rsdata1);
    digitalWrite(D4, HIGH);
    delay(1000);
    digitalWrite(D4, LOW);
    rsdata = "";
    delay(2000);
  }
  tdata = "";
  hdata = "";
  smdata = "";
  rsdata = "";
  count  = 0;
  count1 = 0;
  count2 = 0;
  count3 = 0;
  delay(100); // ThingSpeak will only accept updates every 15 seconds.


  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &mode0) {
      Serial.print(F("Got: "));
    }
    if (strcmp((char *)mode0.lastread, "1") == 0) {
      Serial.println("mode1");
      ss.write('1');
    }

    if (strcmp((char *)mode0.lastread, "2") == 0) {
      Serial.println("mode2");
      ss.write('2');
    }
    if (strcmp((char *)mode0.lastread, "4") == 0) {
      Serial.println("mode4");
      ss.write('4');
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
}
