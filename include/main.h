#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <SoftwareSerial.h>

#include "mlog.h"
#include "mserver.h"
SoftwareSerial *uart;
void initUART(int RX_PIN, int TX_PIN, int baudrate){
    uart = new SoftwareSerial(RX_PIN, TX_PIN);
    uart->begin(baudrate); // TODO: delete the pointer
}

#endif // MAIN_H