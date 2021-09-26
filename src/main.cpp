#include "properties.h"
#include "pins.h"
#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "events.h"
#include "data.h"
#include "lib/EEPROM.h"
#include <ArduinoJson.h>
#include <string>

void setup()
{
    // Debug console
    Serial.begin(115200);

    // EEPROM things
    EEPROM.begin(512);

    // setup pins mode
    setupPins();

    // sync Last Data from EEPROM
    syncPinRom();

    Blynk.begin(auth, ssid, pass);
    // You can also specify server:
    //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
    //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
    Blynk.run();
    Blynk.syncAll();

    // You can inject your own code or combine it with other sketches.
    // Check other examples on how to communicate with Blynk. Remember
    // to avoid delay() function!
}

void onChangeLog(int virtualPin, int val)
{
    Serial.print('V');
    Serial.print(virtualPin);
    Serial.print(": ");
    Serial.println(val);

    // push to EEPROM
    saveData(virtualPin, val);
    Serial.println("Value saved to EEPROM");

    // notify
    char cond[3] = "";

    if (val == 1)
    {
        cond[0] = 'O';
        cond[1] = 'N';
    }
    else
    {
        cond[0] = 'O';
        cond[1] = 'F';
        cond[2] = 'F';
    }

    char desc[32] = "";
    char changedVPin[8];
    sprintf(changedVPin, "%d", virtualPin);

    strcat(desc, "Relay ");
    strcat(desc, changedVPin);
    strcat(desc, " :");
    strcat(desc, cond);

    Blynk.logEvent("PINCHG", desc);
}

void doSync()
{
    Blynk.syncVirtual(V0, V1, V2, V3, V4, V5, V6, V7, V8);
}

bool saveData(int addr, byte val)
{
    EEPROM.write(addr, val);

    return EEPROM.commit();
}

byte getData(int addr)
{
    return EEPROM.read(addr);
}

byte reverseByte(byte b)
{
    if (b == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void syncPinRom()
{
    digitalWrite(RELAY_0, reverseByte(getData(0)));
    digitalWrite(RELAY_1, reverseByte(getData(1)));
    digitalWrite(RELAY_2, reverseByte(getData(2)));
    digitalWrite(RELAY_3, reverseByte(getData(3)));
    digitalWrite(RELAY_4, reverseByte(getData(4)));
    digitalWrite(RELAY_5, reverseByte(getData(5)));
    digitalWrite(RELAY_6, reverseByte(getData(6)));
    digitalWrite(RELAY_7, reverseByte(getData(7)));
    digitalWrite(RELAY_8, reverseByte(getData(8)));
    Serial.println("Last Pin Configuration Synced");
}