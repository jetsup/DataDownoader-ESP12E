#include "mserver.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
ESP8266WebServer server(80);
SoftwareSerial *uart;

void initServer(SoftwareSerial *serial) {
  uart = serial;
  server.serveStatic("/", LittleFS, "/index.html");
  server.on("/rehash", processAndDownload);
  server.begin();
  timeClient.begin();
}

void handleClients() { server.handleClient(); }

void processAndDownload() {
  const char *recDataSize = server.arg("dataSizes").c_str();
  int recDifficulty = server.arg("difficulty").toInt();
  int recStartingNonce = server.arg("startingNonce").toInt();
  int recNLoop = server.arg("nLoop").toInt();
  int recResultsCount = server.arg("resultsCount").toInt();
  const char *whichHash = server.arg("benchmark").c_str();
  const char *recFileType = server.arg("dataFormat").c_str();

  String combinedParameters =
      String(recDataSize) + ";" + String(recDifficulty) + ";" +
      String(recStartingNonce) + ";" + String(recNLoop) + ";" +
      String(recResultsCount) + ";" + String(whichHash) + ";" +
      String(recFileType);
  LOG("PARAMETERS", combinedParameters.c_str());
  uart->println(combinedParameters);  // send the parameters to the other board
  // keep waiting for results
  while (true) {
    // TODO: Have another mechanism to detect when the other board crashes or
    // disconnects
    if (uart->available()) {
      String response = uart->readStringUntil(
          '\n');  // change this to '\0' if it doesn't work
      LOG("RESPONSE", response.c_str());

      char filename[60];
      if (String(whichHash).equalsIgnoreCase("bare_hashing")) {
        generateFilename("bare_hashing", recDifficulty, recDataSize,
                         recFileType, BARE, timeClient, filename);
      } else if (String(whichHash).equalsIgnoreCase("hashing_with_nonce")) {
        generateFilename("hashing_with_nonce", recDifficulty, recDataSize,
                         recFileType, NONCE, timeClient, filename);
      } else if (String(whichHash).equalsIgnoreCase("hash_verification")) {
        generateFilename("hash_verification", recDifficulty, recDataSize,
                         recFileType, VERIFY, timeClient, filename);
      }
      LOG("FILENAME", filename);
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
      server.sendHeader("Access-Control-Allow-Headers",
                        "Origin,X-Requested-With,Content-Type,Accept");
      server.sendHeader("Content-Type", "application/json");
      server.sendHeader("Content-Disposition",
                        "attachment; filename=" + String(filename));
      server.send(200, "application/json", response);
      break;
    }
    yield();
  }
}

void generateFilename(const char *filename, const int difficulty,
                      const char *dataSize, const char *fileType, int hashType,
                      NTPClient timeClient, char *finalName) {
  char mFormatted[18 + strlen(filename) + strlen(fileType)];
  // TODO: uncomment this for fetching time from internet
  // // while(!timeClient.forceUpdate()){ // Uncomment this
  //     /*Loop until it get the current time, don't use the `cached`*/
  // // }
  timeClient.setTimeOffset(3 * 3600);  // Nairobi +0300 HRS
  time_t rawTime = timeClient.getEpochTime();
  // time_t rawTime = 1689162303;
  struct tm ts;
  ts = *localtime(&rawTime);
  int year = ts.tm_year + 1900;
  char cYear[5];
  sprintf(cYear, "%04d", year);
  sprintf(cYear, "%c%c", cYear[2], cYear[3]);
  int month = ts.tm_mon + 1;  // Starts from ZERO
  int day = ts.tm_mday;
  int hour = ts.tm_hour;
  int mins = ts.tm_min;
  int sec = ts.tm_sec;
  if (hashType == BARE)  // Bare hashing
  {
    sprintf(mFormatted, "%s_%s_%s%02d%02d_%02d%02d%02d.%s", filename, dataSize,
            cYear, month, day, hour, mins, sec, fileType);
  } else if (hashType == NONCE)  // Hashing with Nonce
  {
    sprintf(mFormatted, "%s_D%02d_%s_%s%02d%02d_%02d%02d%02d.%s", filename,
            difficulty, dataSize, cYear, month, day, hour, mins, sec, fileType);
  } else if (hashType == VERIFY)  // Hash verification
  {
    LOG("Hash Verification Not Implemented");
  }
  sprintf(finalName, "%s", mFormatted);
}