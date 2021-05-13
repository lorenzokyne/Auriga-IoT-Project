#include "Sensor.h"
#include "Arduino.h"

class Microphone : Sensor
{

public:
    Microphone() : Sensor("atm/microphone/value"){};

    void setValue()
    {
        // MICROPHONE SENSOR
        int microphoneValue = analogRead(BIG_SOUND_AO_PIN); // Read the value of the analog interface A0 assigned to digitalValue
        int StrLen = sprintf((char *)microphoneStr, "%d", microphoneValue);
        microphoneStr[StrLen] = '\0';
    }
    char *getValue()
    {
        //TODO
    }
};