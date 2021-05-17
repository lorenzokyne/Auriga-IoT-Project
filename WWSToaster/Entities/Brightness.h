#ifndef SENSOR_H
#define SENSOR_H
#include "Sensor.h"
#endif
#include "Arduino.h"

class Brightness : Sensor
{

public:
    Brightness(int pin) : Sensor("atm/darkness/value", pin){};

    void measureValue(char*value)
    {
        // BRIGHTNESS SENSOR
        // 0 = LIGHT - 1000 = DARKNESS
        int brightnessAnalogValue = analogRead(this->pin);
        int StrLen = sprintf(value, "%d", brightnessAnalogValue);
        value[StrLen] = '\0';
    }

    char *getTopic()
    {
        return this->topic;
    }
};