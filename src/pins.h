// PINS CONFIGURATION

#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

// TODO Don't forget to modify in case pin modifications
#define RELAY_0 D0
#define RELAY_1 D1
#define RELAY_2 D2
#define RELAY_3 D3
#define RELAY_4 D4
#define RELAY_5 D5
#define RELAY_6 D6
#define RELAY_7 D7
#define RELAY_8 D8
#define SIGNAL A0

// TODO Don't forget to modify in case pin modifications
int ROM_PINS[9] = {100, 101, 102, 103, 104, 105, 106, 107, 108};

// TODO Don't forget to modify in case pin modifications
void setupPins()
{
    pinMode(RELAY_0, OUTPUT);
    pinMode(RELAY_1, OUTPUT);
    pinMode(RELAY_2, OUTPUT);
    pinMode(RELAY_3, OUTPUT);
    pinMode(RELAY_4, OUTPUT);
    pinMode(RELAY_5, OUTPUT);
    pinMode(RELAY_6, OUTPUT);
    pinMode(RELAY_7, OUTPUT);
    pinMode(RELAY_8, OUTPUT);
    pinMode(SIGNAL, INPUT);

    digitalWrite(RELAY_0, HIGH);
    digitalWrite(RELAY_1, HIGH);
    digitalWrite(RELAY_2, HIGH);
    digitalWrite(RELAY_3, HIGH);
    digitalWrite(RELAY_4, HIGH);
    digitalWrite(RELAY_5, HIGH);
    digitalWrite(RELAY_6, HIGH);
    digitalWrite(RELAY_7, HIGH);
    digitalWrite(RELAY_8, HIGH);
};

#endif