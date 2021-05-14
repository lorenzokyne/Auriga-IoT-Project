#ifndef SENSOR_H
    #define SENSOR_H
    #include "Sensor.h"
#endif
#include "Arduino.h"

class Brightness : Sensor
{

public:
    Brightness(int pin) : Sensor("atm/darkness/value", pin){};

    void measureValue()
    {
        // BRIGHTNESS SENSOR
        // 0 = LIGHT - 1000 = DARKNESS
        int brightnessAnalogValue = analogRead(this->pin);
        int StrLen = sprintf((char *)this->value, "%d", brightnessAnalogValue);
        this->value[StrLen] = '\0';
    }

    char *getValue()
    {
        return this->value;
    }

    char *getTopic()
    {
        return this->topic;
    }
};