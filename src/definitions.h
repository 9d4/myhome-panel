// define functions, vars, or any global things here,
// which will be overriden in another file
#ifndef DEFINITIONS_h
#define DEFINITIONS_h

#include <ArduinoJson.h>
#include <BlynkSimpleEsp8266.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "relay.h"

// CONSTANTS
// what is time
const unsigned long DAY = 24UL * 60UL * 60UL * 1000UL;
const unsigned long HOUR = 60UL * 60UL * 1000UL;
const unsigned long MINUTE = 60UL * 1000UL;
const unsigned long SECOND = 1000UL;
char daysOfWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char NTP_SERVER[] = "0.id.pool.ntp.org";
const int UTC_OFFSET = 7 * 3600; // in seconds
const char MESSAGE_EVENT[] = "message";

// FUNCTIONS
bool saveData(int addr, byte val);
byte getData(int addr);
void syncPinEEPROM();
void onPinChangeLog(int virtualPin, int val);
void doSync();
void printWiFiInfo(WiFiEventStationModeGotIP event);
void actuate_relays(int virtual_pin, byte state);

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
NTPClient ntpClient(wifiUdp, NTP_SERVER, UTC_OFFSET);
Relay r0 = {0, 0, 32, 8, V0, 100};
Relay r1 = {1, 0, 1, 8, V1, 101};
Relay r2 = {2, 0, 2, 8, V2, 102};
Relay r3 = {3, 0, 9, 8, V3, 103};
Relay r4 = {4, 0, 10, 8, V4, 104};
Relay r5 = {5, 0, 11, 8, V5, 105};
Relay r6 = {6, 0, 12, 8, V6, 106};
Relay r7 = {7, 0, 26, 8, V7, 107};

// save r1 to r7 to array
Relay *relays[8] = {&r0, &r1, &r2, &r3, &r4, &r5, &r6, &r7};

#endif