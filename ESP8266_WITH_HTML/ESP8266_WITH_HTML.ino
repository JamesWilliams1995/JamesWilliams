#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define WLAN_SSID       "JOKER"
#define WLAN_PASS       "12345678"
#define TOUCH_PIN       D2  // GPIO pin connected to the touch sensor

ESP8266WebServer server(80);

String touchStatus = "Not Touched";  // Variable to store touch sensor status

void handleRoot() {
  // Update touch status
  if (digitalRead(TOUCH_PIN) == HIGH) {  // Assuming LOW means "Touched"
    touchStatus = "Touched";
  } else {
    touchStatus = "Not Touched";
  }

  // HTML page to display touch status
  String html = "<html>\
    <head>\
      <title>ESP8266 Web Server</title>\
      <style>body { font-family: Arial; text-align: center; }</style>\
    </head>\
    <body>\
      <h1>ESP8266 Web Server</h1>\
      <p>Touch Sensor Status: " + touchStatus + "</p>\
    </body>\
  </html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  // Configure the touch sensor pin
  pinMode(TOUCH_PIN, INPUT);
 
  // Connect to WiFi
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Set up web server routes
  server.on("/", handleRoot);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();  // Handle incoming client requests
}
