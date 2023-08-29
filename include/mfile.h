#ifndef MFILE_H
#define MFILE_H

#include <LittleFS.h>
#define DATA_MULTIPLIER 1024
#include "mlog.h"

bool initLittleFS();
void readRandomFromFile(const char* filename, const char* dataSize,
                        char* returnedData);

#endif  // MFILE_H