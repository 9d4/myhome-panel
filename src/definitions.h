// define functions, vars, or any global things here,
// which will be overriden in another file
#ifndef DEFINITIONS_h
#define DEFINITIONS_h

#include <ArduinoJson.h>
#include <BlynkSimpleEsp8266.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// CONSTANTS
// what is time
const unsigned long DAY = 24UL * 60UL * 60UL * 1000UL;
const unsigned long HOUR = 60UL * 60UL * 1000UL;
const unsigned long MINUTE = 60UL * 1000UL;
const unsigned long SECOND = 1000UL;
const char NTP_SERVER[] = "0.id.pool.ntp.org";

// FUNCTIONS
bool saveData(int addr, byte val);
byte getData(int addr);
void syncPinRom();
void sendUptime();
void onChangeLog(int virtualPin, int val);
void doSync();

// VARS
unsigned long *days = new unsigned long;
unsigned long *hours = new unsigned long;
unsigned long *minutes = new unsigned long;
unsigned long *seconds = new unsigned long;
bool newDevice = false;
bool serverBased = false;
bool justBooted = true;

// INSTANCE
BlynkTimer timer;
WiFiUDP wifiUdp;
NTPClient ntpClient(wifiUdp, NTP_SERVER);

#endif