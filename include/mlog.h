#ifndef MLOG_H
#define MLOG_H

#include <HardwareSerial.h>
#include <IPAddress.h>

void LOG();

void LOG(const char *value);
void LOG(const char *label, const char *value);
void LOG(const char *label, IPAddress value);

void LOG(int value);
void LOG(const char *label, int value);
void LOG(const char *label, size_t value);

void LOG(double value);
void LOG(const char *label, double value);

#endif  // MLOG_H