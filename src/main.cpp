#include <Arduino.h>
#include <Wire.h>
#include <LittleFS.h>
#include <ESP8266WebServer.h>
#include <ESP_WiFiManager.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#define ARDUINO_ADDRESS 0x09

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

ESP8266WebServer server(80);
const char *WF_MANAGER_SSID = "SaganaTR";
const char *WF_ACCESS_POINT_NAME = "Bench";
const char *WF_PASSWORD = "1234567890";

volatile int receivedDataFromArduino = 0;
volatile bool newDataFromArduino = false;
// hash parameters
String hashType;
String dataSize;
int startingNonce, difficulty, resultsCount, iterationsPerResult;

void onRequestFromArduino();
void handleDownload();
void setup()
{
  Serial.begin(115200);
  LittleFS.begin();
  Wire.begin(ARDUINO_ADDRESS); // slave

  // WiFi provisioning
  ESP_WiFiManager wifiManager;
  wifiManager.autoConnect(WF_MANAGER_SSID, WF_PASSWORD);

  IPAddress myIP(192, 168, 100, 100);
  WiFi.softAPConfig(myIP, myIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(WF_ACCESS_POINT_NAME, WF_PASSWORD);

  attachInterrupt(digitalPinToInterrupt(5), onRequestFromArduino, FALLING);
  // create the web server

  server.serveStatic("/", LittleFS, "/index.html");
  server.on("/rehash", handleDownload);

  server.begin();
  timeClient.begin();
}

void loop()
{
  server.handleClient();
  if (newDataFromArduino)
  {
    noInterrupts();
    int dataFromArduino = receivedDataFromArduino;
    newDataFromArduino = false;
    interrupts();
    // process the data
  }
}

void onRequestFromArduino()
{
  Wire.write(receivedDataFromArduino);
}

void handleDownload()
{
  const char *recDataSize = server.arg("dataSizes").c_str();
  int recDifficulty = server.arg("difficulty").toInt();
  int recStartingNonce = server.arg("startingNonce").toInt();
  int recNLoop = server.arg("nLoop").toInt();
  int recResultsCount = server.arg("resultsCount").toInt();
  const char *whichHash = server.arg("benchmark").c_str();
  const char *recFileType = server.arg("dataFormat").c_str();
  // TODO: Sed these parameters to the arduino
}
