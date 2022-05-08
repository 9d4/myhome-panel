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

const byte header_start = 0x37;
const byte header_end = 0x38;

// send state to the actuator
void relay_actuate(Relay *relay) {
    Serial.println("sending data to actuator");
    // print relay struct

    Wire.beginTransmission(relay->actuator_addr);
    Wire.write(header_start);
    Wire.write(relay->actuator_pin);
    Wire.write(relay->state);
    Wire.write(header_end);
    Wire.endTransmission();

    Serial.println("sent!\n");
}


#endif
