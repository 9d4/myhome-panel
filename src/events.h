// TODO Don't forget to modify in case pin modifications

// #include "pins.h"
#include "BlynkSimpleEsp8266.h"

BLYNK_CONNECTED()
{
    // When the device is connected to the server, there is two options:
    // 1. Update the pins based on the EEPROM
    // 2. Update the pins based on the blynk server
    // To do that, I set virtual pin (V100). Once device connected to blynk,
    // update that pin, then
    // If that pin state is (1), do option number 1, else number 2.
    // Sometimes power outage happened, to recover this condition, 
    // On-device-boot we'll always sync local pin at first. see main.cpp
    // WE DO THE OPERATION IN BLYNK_WRITE(V100) due to asynchronous syncing

    Serial.println("Checking Server Based value....");
    Blynk.syncVirtual(V100);
}

// determines whether value server based or local based
void setupServerLocalMode() {
    if (serverBased && justBooted)
    {
        justBooted = false;

        Serial.println("Using Server Based Value");
        doSync();
    }
    else
    {
        justBooted = false;

        Serial.println("Using Local Based Value");

        // push local to server
        // reverse the value 0 = 1, 1 = 0
        // TODO Don't forget to modify in case pin modifications
    }
}

BLYNK_WRITE(V100)
{
    int pinVal = param.asInt();

    Serial.print("Got V100 value ");
    Serial.println(pinVal);

    if (pinVal == 1)
    {
        serverBased = true;
    }
    else
    {
        serverBased = false;
    }

    setupServerLocalMode();
}

BLYNK_WRITE(V0)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onPinChangeLog(V0, pinValue);
}

BLYNK_WRITE(V1)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onPinChangeLog(V1, pinValue);
}

BLYNK_WRITE(V2)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onPinChangeLog(V2, pinValue);
}

BLYNK_WRITE(V3)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onPinChangeLog(V3, pinValue);
}

BLYNK_WRITE(V4)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onPinChangeLog(V4, pinValue);
}

BLYNK_WRITE(V5)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onPinChangeLog(V5, pinValue);
}

BLYNK_WRITE(V6)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onPinChangeLog(V6, pinValue);
}

BLYNK_WRITE(V7)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onPinChangeLog(V7, pinValue);
}

BLYNK_WRITE(V8)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onPinChangeLog(V8, pinValue);
}

BLYNK_WRITE(V15) {
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onPinChangeLog(V15, pinValue);
}
