#ifndef SENSOR_H
#define SENSOR_H
#include "Sensor.h"
#endif
#include "Arduino.h"

class Brightness : Sensor
{

public:
    Brightness(int pin) : Sensor(pin){};
    void measureValue(char *value)
    {
        value[0]='\0';
        // BRIGHTNESS SENSOR
        // 0 = LIGHT - 1000 = DARKNESS
        int brightnessAnalogValue = analogRead(this->pin);
        int StrLen = sprintf(value, "BRH:%d", brightnessAnalogValue);
        value[StrLen] = '\0';
    }
};