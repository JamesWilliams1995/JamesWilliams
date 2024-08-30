/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-mesh-esp32-esp8266-painlessmesh/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include"function.h"

#include "painlessMesh.h"
#include <Arduino_JSON.h>


// MESH Details
#define   MESH_PREFIX     "saravanan" //name for your MESH
#define   MESH_PASSWORD   "12345678" //password for your MESH
#define   MESH_PORT       5555 //default port


//Number for this node
int nodeNumber = 3;



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
  FUNTION_STATE();
  //Serial.println(dht.temperature);

  JSONVar jsonReadings;
  jsonReadings["node"] = nodeNumber;
  jsonReadings["soil_value"] = soil_value;
  jsonReadings["water_value"] = water_value;
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
  int ir_value = myObject["soil_value"];
  int gas_value = myObject["water_value"];
  //  int motor = myObject["motor"];


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
  //U1.begin(6, 7);
  pinMode(D0, INPUT);
  pinMode(A0, INPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

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
