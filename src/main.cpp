#include "properties.h"
#include "pins.h"
#include "definitions.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "events.h"
#include "lib/EEPROM.h"
#include <ArduinoJson.h>
#include <string>

// connect wifi at first time
void wifiInit()
{
    WiFi.begin(ssid, pass); // non-blocking
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);

    Blynk.config(auth);
    Blynk.connect();
}

void setup()
{
    // Debug console
    Serial.begin(115200);

    // EEPROM things
    EEPROM.begin(1024);

    // setup pins mode
    setupPins();

    // sync Last Data from EEPROM
    syncPinRom();

    // init the wifi
    wifiInit();

    // connect to the ntp server
    ntpClient.begin();

    // Send uptime every 5 seconds
    timer.setInterval(5000L, sendUptime);
}

void loop()
{
    timer.run();

    if (WiFi.isConnected())
    {
        Blynk.run();
    }
    else
    {
        // swap justBooted to true, so in case wifi disconnected then connected again, 
        // device can execute BLYNK_CONNECTED event. see events.h
        // if the value not swapped to true then the Served Based function won't work
        // till device restarts.
        justBooted = true;
    }

    // You can inject your own code or combine it with other sketches.
    // Check other examples on how to communicate with Blynk. Remember
    // to avoid delay() function!
}


// Send uptime and local time
void sendUptime()
{
    Serial.println(ntpClient.getDay());

    unsigned long total = millis();

    *days = total / DAY;
    total -= (*days * DAY);

    *hours = total / HOUR;
    total -= (*hours * HOUR);

    *minutes = total / MINUTE;
    total -= (*minutes * MINUTE);

    unsigned long seconds = total / SECOND;

    // v127 for days
    // v126 for hours
    // v125 for minutes
    // v124 for seconds
    Blynk.virtualWrite(V127, *days);
    Blynk.virtualWrite(V126, *hours);
    Blynk.virtualWrite(V125, *minutes);
    Blynk.virtualWrite(V124, seconds);

    Serial.print("[uptime]: ");
    Serial.print(*days); Serial.print("d ");
    Serial.print(*hours); Serial.print("h ");
    Serial.print(*minutes); Serial.print("m ");
    Serial.print(seconds); Serial.println("s ");

    // v123 for day
    // v122 for hour
    // v121 for minute
    Blynk.virtualWrite(V127, *days);
    Blynk.virtualWrite(V126, *hours);
    Blynk.virtualWrite(V125, *minutes);
    Blynk.virtualWrite(V124, seconds);
}

void onChangeLog(int pin, int val)
{
    Serial.print('V');
    Serial.print(pin);
    Serial.print(": ");
    Serial.println(val);

    // push to EEPROM
    saveData(ROM_PINS[pin], val);

    Serial.println("Value saved to EEPROM");
    Serial.print("addr:");
    Serial.print(pin);
    Serial.print("  value:");
    Serial.println(val);

    Serial.println("");

    // // notify
    // char cond[3] = "";

    // if (val == 1)
    // {
    //     cond[0] = 'O';
    //     cond[1] = 'N';
    // }
    // else
    // {
    //     cond[0] = 'O';
    //     cond[1] = 'F';
    //     cond[2] = 'F';
    // }

    // char desc[32] = "";
    // char changedVPin[8];
    // sprintf(changedVPin, "%d", virtualPin);

    // strcat(desc, "Relay ");
    // strcat(desc, changedVPin);
    // strcat(desc, " :");
    // strcat(desc, cond);

    // Blynk.logEvent("PINCHG", desc);
}

void doSync()
{
    // TODO Don't forget to modify in case pin modifications
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
    Serial.println();
    // this number is fancy number
    int mark = 98;

    // if the fancy number exists, then its not a new device
    if (EEPROM.read(1023) != mark)
    {
        // this is new board
        newDevice = true;
        Serial.println("NEW BOARD!");

        // make mark, show we know that board is not new anymore
        // by adding a number on sector 512
        // TODO Don't forget to modify in case pin modifications
        EEPROM.write(1023, mark);
        EEPROM.write(ROM_PINS[0], 1);
        EEPROM.write(ROM_PINS[1], 1);
        EEPROM.write(ROM_PINS[2], 1);
        EEPROM.write(ROM_PINS[3], 1);
        EEPROM.write(ROM_PINS[4], 1);
        EEPROM.write(ROM_PINS[5], 1);
        EEPROM.write(ROM_PINS[6], 1);
        EEPROM.write(ROM_PINS[7], 1);
        EEPROM.write(ROM_PINS[8], 1);

        if (EEPROM.commit())
        {
            Serial.println("written");
        }

        doSync();
    }
    else
    {
        // TODO Don't forget to modify in case pin modifications
        digitalWrite(RELAY_0, reverseByte(getData(ROM_PINS[0])));
        digitalWrite(RELAY_1, reverseByte(getData(ROM_PINS[1])));
        digitalWrite(RELAY_2, reverseByte(getData(ROM_PINS[2])));
        digitalWrite(RELAY_3, reverseByte(getData(ROM_PINS[3])));
        digitalWrite(RELAY_4, reverseByte(getData(ROM_PINS[4])));
        digitalWrite(RELAY_5, reverseByte(getData(ROM_PINS[5])));
        digitalWrite(RELAY_6, reverseByte(getData(ROM_PINS[6])));
        digitalWrite(RELAY_7, reverseByte(getData(ROM_PINS[7])));
        digitalWrite(RELAY_8, reverseByte(getData(ROM_PINS[8])));
        Serial.println("Last Pin Configuration Synced");
    }
}