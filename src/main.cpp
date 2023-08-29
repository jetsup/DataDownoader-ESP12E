#include "main.h"

const int RX_PIN = 2, TX_PIN = 3, BAUDRATE = 115200;
// hash parameters
String hashType;
String dataSize;
int startingNonce, difficulty, resultsCount, iterationsPerResult;

void setup() {
  Serial.begin(115200);
  initUART(RX_PIN, TX_PIN, BAUDRATE);
  // create the web server
  initServer(uart);
  LOG("SETUP", "Initialization Complete");
}

void loop() { handleClients(); }
