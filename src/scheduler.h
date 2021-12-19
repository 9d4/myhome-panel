#ifndef SCHEDULER_h
#define SCHEDULER_h

#include <BlynkSimpleEsp8266.h>

typedef void (*time_callback)(void);

class Scheduler
{
private:
    char *_name;
    u_int16_t _startTime[2]; // 0: h; 1: m
    u_int16_t _stopTime[2];  // 0: h; 1: m
    u_int64_t _lastUpdate;
    u_int16_t _currentTime[3];              // 0: h; 1:m; 2:s;
    unsigned long _updateInterval = 3000UL; // ms
    NTPClient *_ntp;

    time_callback startF;
    time_callback stopF;
    time_callback betweenF;

    void internalUpdate();
    void updateTime();
    void printHeaderLog();
    bool inBetween();

public:
    Scheduler(const char *name, NTPClient *ntpClient, u_int16_t startH, u_int16_t startM, u_int16_t stopH, u_int16_t stopM);
    void onStopCallback(time_callback);
    void onStartCallback(time_callback);
    void onBetweenCallback(time_callback);
    void setUpdateInterval(unsigned long); // 3000 ms by default
    void update();
};

Scheduler::Scheduler(const char *name, NTPClient *ntpClient, u_int16_t startH, u_int16_t startM, u_int16_t stopH, u_int16_t stopM)
{
    _name = (char *)name;
    _ntp = ntpClient;
    _startTime[0] = startH;
    _startTime[1] = startM;
    _stopTime[0] = stopH;
    _stopTime[1] = stopM;
    internalUpdate();
}

// Executes when current time is matched with stopTime
void Scheduler::onStopCallback(time_callback f)
{
    stopF = f;
}

// Executes when current time is matched with startTime
void Scheduler::onStartCallback(time_callback f)
{
    startF = f;
}

// Executes when current time is in between startTime and stopTime
void Scheduler::onBetweenCallback(time_callback f)
{
    betweenF = f;
}

// by default 3000ms
void Scheduler::setUpdateInterval(unsigned long ms)
{
    _updateInterval = ms;
}

bool Scheduler::inBetween()
{
    bool gtStart = false;
    bool ltStop = false;

    // currentHour >= startHour and currentMinute gt startMinute
    if (_currentTime[0] >= _startTime[0] && _currentTime[1] > _startTime[1])
    {
        gtStart = true;
    }
    // currentHour gt startHour
    else if (_currentTime[0] > _startTime[0])
    {
        gtStart = true;
    }

    // currentHour lt stopHour
    if (_currentTime[0] < _stopTime[0])
    {
        ltStop = true;
    }
    // currentHour <= stopHour and currentMinute lt stopMinute
    else if (_currentTime[0] <= _stopTime[0] && _currentTime[1] < _stopTime[1])
    {
        ltStop = true;
    }

    printHeaderLog();
    Serial.print(gtStart);
    Serial.print(" && ");
    Serial.println(ltStop);
    return gtStart && ltStop;
}

// update _currentTime
void Scheduler::updateTime()
{
    _currentTime[0] = _ntp->getHours();
    _currentTime[1] = _ntp->getMinutes();
    _currentTime[2] = _ntp->getSeconds();
}

void Scheduler::internalUpdate()
{
    updateTime();

    // start time match
    if (_startTime[0] == _currentTime[0] &&
        _startTime[1] == _currentTime[1])
    {
        startF();
    }

    // stop time match
    if (_stopTime[0] == _currentTime[0] &&
        _stopTime[1] == _currentTime[1])
    {
        stopF();
    }

    if (inBetween())
    {
        betweenF();
    }

    _lastUpdate = millis();
}

// Update the engine
void Scheduler::update()
{
    unsigned long now = millis();
    unsigned long gap = now - _lastUpdate;

    if (gap >= _updateInterval)
    {
        internalUpdate();
    }
}

void Scheduler::printHeaderLog()
{
    Serial.print("[Scheduler:");
    Serial.print(_name);
    Serial.print("]: ");
}
#endif
