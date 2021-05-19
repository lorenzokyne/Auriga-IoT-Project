#ifndef SENSOR_H
    #define SENSOR_H
    #include "Sensor.h"
#endif
#include "Arduino.h"

class Microphone : Sensor
{

public:
    Microphone(int pin) : Sensor(pin){};

    void measureValue(char *value)
    {
        value[0]='\0';
        // MICROPHONE SENSOR
        int microphoneValue = analogRead(this->pin); // Read the value of the analog interface A0 assigned to digitalValue
        int StrLen = sprintf(value, "MPH:%d", microphoneValue);
        value[StrLen] = '\0';
    }
};