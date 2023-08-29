#ifndef MSERVER_H
#define MSERVER_H

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <SoftwareSerial.h>
#include <WiFiUdp.h>

#include "globals.h"
#include "mfile.h"

void initServer(SoftwareSerial *uart);
void handleClients();
void processAndDownload();
void generateFilename(const char *filename, const int difficulty,
                      const char *dataSize, const char *fileType, int hashType,
                      NTPClient timeClient, char *finalName);

#endif  // MSERVER_H