#include "env.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

#define R_PIN D6
#define G_PIN D7
#define B_PIN D5

#define R_DEFAULT 255
#define G_DEFAULT 255
#define B_DEFAULT 255

ESP8266WebServer server(80);

uint8_t red;
uint8_t green;
uint8_t blue;

void handleColor(){
if (!server.hasArg("red")){
  server.send(400, "text/plain", "Please pass an argument called 'red'");
  return;
}

if(!server.hasArg("green")){
server.send(400, "text/plain", "Please pass an argument called 'green'");
  return;
}

if(!server.hasArg("blue")){
  server.send(400, "text/plain", "Please pass an argument called 'blue'");
  return;
}

  red = (uint8_t) server.arg("red").toInt();
  green = (uint8_t) server.arg("green").toInt();
  blue = (uint8_t) server.arg("blue").toInt();

  String response = "Succefully got red: " + String(red) + " green: " + String(green) + " blue: " + String(blue);
  saveColorToFile();
  printColorState();
  setColor();
  server.send(200, "text/plain", response);
}

void printColorState(){
  String response = "red: " + String(red) + " green: " + String(green) + " blue: " + String(blue);
  Serial.println(response);
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found");
}

void loadColorFromFile(){
  if (LittleFS.exists("/red")){
    File redFile = LittleFS.open("/red", "r");
    red = (uint8_t) redFile.readString().toInt();
    redFile.close();
  }
  else{
    red = R_DEFAULT;
  }

  if (LittleFS.exists("/green")){
    File greenFile = LittleFS.open("/green", "r");
    green = (uint8_t) greenFile.readString().toInt();
    greenFile.close();
  }
  else{
    green = G_DEFAULT;
  }

if (LittleFS.exists("/blue")){
    File blueFile = LittleFS.open("/blue", "r");
    blue = (uint8_t) blueFile.readString().toInt();
    blueFile.close();
  }
  else{
    blue = B_DEFAULT;
  }
}

void saveColorToFile(){
  File redFile = LittleFS.open("/red", "w");
  File greenFile = LittleFS.open("/green", "w");
  File blueFile = LittleFS.open("/blue", "w");
  redFile.print(red);
  greenFile.print(green);
  blueFile.print(blue);
  redFile.close();
  greenFile.close();
  blueFile.close();
}

void setColor(){
  analogWrite(R_PIN, red);
  analogWrite(G_PIN, green);
  analogWrite(B_PIN, blue);
}

void setup(){
  Serial.begin(115200);
  Serial.print("connecting to");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  LittleFS.begin();
  loadColorFromFile();
  printColorState();
  setColor();
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("connected succefully");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/color", HTTP_GET , handleColor);
  server.begin();
}

void loop(){
  server.handleClient();
}
