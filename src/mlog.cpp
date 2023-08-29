#include "mlog.h"

void LOG() { Serial.println(); }

void LOG(const char *value) { Serial.println(value); }
void LOG(const char *label, const char *value) {
  Serial.printf("[%s]: '%s'\n", label, value);
}
void LOG(const char *label, IPAddress value) {
  Serial.print("[");
  Serial.print(label);
  Serial.print("]: '");
  Serial.print(value);
  Serial.println("'");
}

void LOG(int value) { Serial.println(value); }
void LOG(const char *label, int value) {
  Serial.printf("[%s]: %d\n", label, value);
}
void LOG(const char *label, size_t value) {
  Serial.printf("[%s]: %d\n", label, value);
}

void LOG(double value) { Serial.println(value, 6); }
void LOG(const char *label, double value) {
  Serial.printf("[%s]: %.6lf\n", label, value);
}