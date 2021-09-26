#include "pins.h"
#include "BlynkSimpleEsp8266.h"

void onChangeLog(int virtualPin, int val);

void doSync();

BLYNK_CONNECTED()
{
    // push local to server
    // reverse the value 0 = 1, 1 = 0
    Blynk.virtualWrite(V0, (1 - digitalRead(RELAY_0)));
    Blynk.virtualWrite(V1, (1 - digitalRead(RELAY_1)));
    Blynk.virtualWrite(V2, (1 - digitalRead(RELAY_2)));
    Blynk.virtualWrite(V3, (1 - digitalRead(RELAY_3)));
    Blynk.virtualWrite(V4, (1 - digitalRead(RELAY_4)));
    Blynk.virtualWrite(V5, (1 - digitalRead(RELAY_5)));
    Blynk.virtualWrite(V6, (1 - digitalRead(RELAY_6)));
    Blynk.virtualWrite(V7, (1 - digitalRead(RELAY_7)));
    Blynk.virtualWrite(V8, (1 - digitalRead(RELAY_8)));
}

BLYNK_WRITE(V0)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onChangeLog(V0, pinValue);

    switch (pinValue)
    {
    case 0:
        digitalWrite(RELAY_0, HIGH);
        break;
    default:
        digitalWrite(RELAY_0, LOW);
        break;
    }
}

BLYNK_WRITE(V1)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onChangeLog(V1, pinValue);

    switch (pinValue)
    {
    case 0:
        digitalWrite(RELAY_1, HIGH);
        break;
    default:
        digitalWrite(RELAY_1, LOW);
        break;
    }
}

BLYNK_WRITE(V2)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onChangeLog(V2, pinValue);

    switch (pinValue)
    {
    case 0:
        digitalWrite(RELAY_2, HIGH);
        break;
    default:
        digitalWrite(RELAY_2, LOW);
        break;
    }
}

BLYNK_WRITE(V3)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onChangeLog(V3, pinValue);

    switch (pinValue)
    {
    case 0:
        digitalWrite(RELAY_3, HIGH);
        break;
    default:
        digitalWrite(RELAY_3, LOW);
        break;
    }
}

BLYNK_WRITE(V4)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onChangeLog(V4, pinValue);

    switch (pinValue)
    {
    case 0:
        digitalWrite(RELAY_4, HIGH);
        break;
    default:
        digitalWrite(RELAY_4, LOW);
        break;
    }
}

BLYNK_WRITE(V5)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onChangeLog(V5, pinValue);

    switch (pinValue)
    {
    case 0:
        digitalWrite(RELAY_5, HIGH);
        break;
    default:
        digitalWrite(RELAY_5, LOW);
        break;
    }
}

BLYNK_WRITE(V6)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onChangeLog(V6, pinValue);

    switch (pinValue)
    {
    case 0:
        digitalWrite(RELAY_6, HIGH);
        break;
    default:
        digitalWrite(RELAY_6, LOW);
        break;
    }
}

BLYNK_WRITE(V7)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onChangeLog(V7, pinValue);

    switch (pinValue)
    {
    case 0:
        digitalWrite(RELAY_7, HIGH);
        break;
    default:
        digitalWrite(RELAY_7, LOW);
        break;
    }
}

BLYNK_WRITE(V8)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    onChangeLog(V8, pinValue);

    switch (pinValue)
    {
    case 0:
        digitalWrite(RELAY_8, HIGH);
        break;
    default:
        digitalWrite(RELAY_8, LOW);
        break;
    }
}
