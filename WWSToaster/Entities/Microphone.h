#ifndef SENSOR_H
    #define SENSOR_H
    #include "Sensor.h"
#endif
#include "Arduino.h"

class Microphone : Sensor
{

public:
    Microphone(int pin) : Sensor("atm/microphone/value", pin){};

    void measureValue()
    {
        // MICROPHONE SENSOR
        int microphoneValue = analogRead(this->pin); // Read the value of the analog interface A0 assigned to digitalValue
        int StrLen = sprintf(this->value, "%d", microphoneValue);
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