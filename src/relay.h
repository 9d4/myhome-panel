#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include <Wire.h>

struct Relay {
    byte num;               // pyshical number
    byte state;             // state of the relay
    byte actuator_pin;      // pin in the actuator
    byte actuator_addr;     // i2c address of the actuator
    byte virtual_pin;       // virtual pin in the blynk cloud
    int eeprom_addr;        // eeprom address of the relay state
};

// send state to the actuator
void relay_toggle(Relay *relay) {
    if (relay->state == 0) {
        relay->state = 1;
    } 
    
    if (relay->state > 0) {
        relay->state = 0;
    }

    Wire.beginTransmission(relay->actuator_addr);
    Wire.write(relay->actuator_pin);
    Wire.write(relay->state);
    Wire.endTransmission();
}


#endif
