#ifndef TIMING_h
#define TIMING_h

#include <definitions.h>

void timeInit()
{
    ntpClient.begin();
    ntpClient.setUpdateInterval(2 * 60 * 1000); // 2 mins
}

#endif