#include <ESPAsyncTCP.h>
#include "global.h"
#include"sensor.h"
#include "iot.h"
#include "lcd.h"
#include"dht11.h"
//DHT dht;

#include "painlessMesh.h"
#include <Arduino_JSON.h>


// MESH Details
#define   MESH_PREFIX     "Saro" //name for your MESH
#define   MESH_PASSWORD   "12345678" //password for your MESH
#define   MESH_PORT       5555 //default port


//Number for this node
int nodeNumber = 1;

//String to send to other nodes with sensor readings
String readings;

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain
String getReadings(); // Prototype for sending sensor readings


//Create tasks: to send messages and get readings;
Task taskSendMessage(TASK_SECOND * 5 , TASK_FOREVER, &sendMessage);


String getReadings ()
{
  F_sensor_data();   //see the sensor.h file

  JSONVar jsonReadings;
  jsonReadings["node"] = nodeNumber;
  jsonReadings["dht_value"] = dht_value;
  jsonReadings["gas_value"] = gas_value;

  readings = JSON.stringify(jsonReadings);
  return readings;
}

void sendMessage () {
  String msg = getReadings();
  mesh.sendBroadcast(msg);
}

// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("Received from %u msg=%s\n", from , msg.c_str());
  JSONVar myObject = JSON.parse(msg.c_str());
  int node = myObject["node"];
  int dht_value = myObject["dht_value"];
  int gas_value = myObject["gas_value"];
  //  int motor = myObject["motor"];

  if (node == 2)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    NODE 2    ");
    lcd.setCursor(0, 1);
    lcd.print("TEM:");
    lcd.print(dht_value);
    lcd.print(8, 1);
    lcd.print("GAS:");
    lcd.print(gas_value);
    delay(1000);
    iot_send("@node" + String(node) + " dht_value" + String(dht_value) + " gas_level" + String(gas_value) + "#");
  }
  if (node == 3)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    NODE 3    ");
    lcd.setCursor(0, 1);
    lcd.print("TEM:");
    lcd.print(dht_value);
    lcd.print(8, 1);
    lcd.print("GAS:");
    lcd.print(gas_value);
    delay(1000);
    iot_send("$node" + String(node) + " dht" + String(dht_value) + " gas_level" + String(gas_value) + "#");
  }
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.println("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void setup() {
  Serial.begin(9600);
  lcd.begin();
  //  lcd.backlight();
  pinMode(D0, INPUT);
  pinMode(A0, INPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);

  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
}

void loop() {
  // it will run the user scheduler as well
  mesh.update();
}