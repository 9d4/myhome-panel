#include "properties.h"
#include "pins.h"
#include "definitions.h"
#include "events.h"
#include "timing.h"
#include <ESP8266WiFi.h>
#include "lib/EEPROM.h"
#include <string>
#include "scheduler.h"
#include "relay.h"
#include <Wire.h>

// connect wifi at first time
void wifiInit()
{
    WiFi.begin(ssid, pass); // non-blocking
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
}

void printWiFiInfo()
{
    Serial.println("-----------WIFI INFO-----------");
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("Netmask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("DNS IP : ");
    Serial.println(WiFi.dnsIP());
    Serial.print("Signal : ");
    Serial.println(WiFi.RSSI());
    Serial.println("-------------------------------");
    Serial.println();
}

bool wifiDisconnected = true;

void testStart()
{
    Serial.println("Scheduler triggered the startF");
}
void testStop()
{
    Serial.println("Scheduler triggered the stopF");
}
void testBetween()
{
    Serial.println("Scheduler triggered the Between");
}


void setup()
{
    // Debug console
    Serial.begin(115200);

    Wire.begin(D1, D2);

    // EEPROM things
    EEPROM.begin(1024);

    // setup pins mode
    setupPins();

    // sync Last Data from EEPROM
    syncPinEEPROM();

    // init the wifi
    wifiInit();

    // init time things
    timeInit();

    Blynk.config(auth);
    Blynk.connect();

    // Send uptime every 5 seconds
    timer.setInterval(5000L, sendTimeInfo);    
}

void loop()
{
    timer.run();

    if (WiFi.isConnected())
    {
        if (wifiDisconnected)
        {
            printWiFiInfo();
            Blynk.logEvent(MESSAGE_EVENT, "Connected Successfully!");
        }

        wifiDisconnected = false;
        Blynk.run();
    }
    else
    {
        wifiDisconnected = true;

        // swap justBooted to true, so in case wifi disconnected then connected again,
        // device can execute BLYNK_CONNECTED event. see events.h
        // if the value not swapped to true then the Server Based function won't work
        // till device restarts.
        justBooted = true;
    }

    // You can inject your own code or combine it with other sketches.
    // Check other examples on how to communicate with Blynk. Remember
    // to avoid delay() function!
}

// Send uptime and local time to the server
void sendTimeInfo()
{
    timeUpdate();

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
    Serial.print(*days);
    Serial.print("d ");
    Serial.print(*hours);
    Serial.print("h ");
    Serial.print(*minutes);
    Serial.print("m ");
    Serial.print(seconds);
    Serial.println("s ");

    // v123 for day
    // v122 for hour
    // v121 for minute
    // v120 for second
    Blynk.virtualWrite(V123, ntpClient.getDay());
    Blynk.virtualWrite(V122, ntpClient.getHours());
    Blynk.virtualWrite(V121, ntpClient.getMinutes());
    Blynk.virtualWrite(V120, ntpClient.getSeconds());

    printTime();
    Serial.println();
}

// callback that should be called when pin changed
// see events.h
void onPinChangeLog(int pin, int val)
{
    // convert val to byte
    byte valByte = val;
    actuate_relays(pin, valByte);
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
}

// Request server to send virtualPin value
void doSync()
{
    // TODO Don't forget to modify in case pin modifications
    Blynk.syncVirtual(V0, V1, V2, V3, V4, V5, V6, V7, V8);
}

// equivalent doSync();
void doVirtualSync() { return doSync(); };

// Save data to EEPROM
bool saveData(int addr, byte val)
{
    EEPROM.write(addr, val);

    return EEPROM.commit();
}

// Read data from EEPROM
byte getData(int addr)
{
    return EEPROM.read(addr);
}

// Flip between 0 and 1
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

// Sync the pin with value from the EEPROM
void syncPinEEPROM()
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
        Serial.println("Last Pin Configuration Synced");
    }
}

// actuate the relays
void actuate_relays(int virtual_pin, byte state) {
    Relay *target = NULL;

    // iterate array named *relays
    for (int i = 0; i < relays_length; i++) {
        if (relays[i].virtual_pin == virtual_pin) {
            target = &relays[i];
        }
    }

    if (target != NULL) { 
        target->state = state;
        relay_actuate(target);
    }
}
