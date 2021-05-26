#ifndef SENSOR_H
#define SENSOR_H
#include "Sensor.h"
#endif
#include "Arduino.h"

class LinearHall : Sensor
{

public:
    LinearHall(int pin) : Sensor(pin){};
    int16_t linearHallValue = 500;

    void measureValue(char *value)
    {
        value[0] = '\0';
        // LINEAR HALL
        linearHallValue = analogRead(this->pin);
        int StrLen = sprintf(value, "LHL:%d", linearHallValue);
        value[StrLen] = '\0';
    }

    bool checkThreshold()
    {
        return this->linearHallValue > 600 || this->linearHallValue < 400;
    }
};