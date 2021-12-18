#ifndef TIMING_h
#define TIMING_h

#include <definitions.h>

void sendTimeInfo();

void timeInit()
{
    ntpClient.begin();
    ntpClient.setUpdateInterval(2 * 60 * 1000); // 1 mins
}

void printTime()
{
    Serial.print("[time]: ");
    Serial.print(ntpClient.getHours());
    Serial.print(":");
    Serial.print(ntpClient.getMinutes());
    Serial.print(":");
    Serial.println(ntpClient.getSeconds());
}

#endif