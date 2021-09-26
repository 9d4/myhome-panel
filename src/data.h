#ifndef DATA_h
#define DATA_h

#include <ArduinoJson.h>
// #include "lib/EEPROM.h"

bool saveData(int addr, byte val);
byte getData(int addr);
void syncPinRom();

#endif