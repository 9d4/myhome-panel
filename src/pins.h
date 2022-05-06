// PINS CONFIGURATION

#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

// TODO Don't forget to modify in case pin modifications
#define SIGNAL A0

// TODO Don't forget to modify in case pin modifications
int ROM_PINS[9] = {100, 101, 102, 103, 104, 105, 106, 107, 108};

// TODO Don't forget to modify in case pin modifications
void setupPins()
{
    pinMode(SIGNAL, INPUT);
};

#endif