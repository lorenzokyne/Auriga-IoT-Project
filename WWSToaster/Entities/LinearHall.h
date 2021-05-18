#ifndef SENSOR_H
#define SENSOR_H
#include "Sensor.h"
#endif
#include "Arduino.h"

class LinearHall : Sensor
{

public:
    LinearHall(int pin) : Sensor(pin){};

    void measureValue(char *value)
    {
        value[0] = '\0';
        // LINEAR HALL
        int linearHallValue = analogRead(this->pin);
        int StrLen = sprintf(value, "%d", linearHallValue);
        value[StrLen] = '\0';
    }
};