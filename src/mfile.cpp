#include "mfile.h"

long getActualSize(const char* dataSize);
bool initLittleFS() { return LittleFS.begin(); }
void readRandomFromFile(const char* filename, const char* dataSize,
                        char* returnedData) {
  File file = LittleFS.open(filename, "r");
  if (!file) {
    LOG("Failed to open file for reading");
    return;
  }
  LOG("File size: ", file.size());
  LOG("Data size: ", dataSize);

  long actualDataSize = getActualSize(dataSize);
  int randomIndex = random(0, file.size() - actualDataSize);
  LOG("Random index: ", randomIndex);
  file.seek(randomIndex);
  file.readBytes(returnedData, actualDataSize);
  file.close();
}

long getActualSize(const char* dataSize) {
  long actualSize = 0;
  if (strstr(dataSize, "k")) {
    actualSize = atoi(dataSize) * DATA_MULTIPLIER;
  } else if (strstr(dataSize, "m")) {
    actualSize = atoi(dataSize) * DATA_MULTIPLIER * DATA_MULTIPLIER;
  } else if (strstr(dataSize, "g")) {
    actualSize =
        atoi(dataSize) * DATA_MULTIPLIER * DATA_MULTIPLIER * DATA_MULTIPLIER;
  } else {
    actualSize = atoi(dataSize);
  }
  return actualSize;
}