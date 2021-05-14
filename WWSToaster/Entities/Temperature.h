#ifndef SENSOR_H
    #define SENSOR_H
    #include "Sensor.h"
#endif
#include "Arduino.h"
#include <dht_nonblocking.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11
DHT_nonblocking dht_sensor(DHT11_PIN, DHT_SENSOR_TYPE);
//TODO -- THIS SENSOR NEEDS TO BE CHECKED BECAUSE IT ISNT WORKING PROPERLY
class Temperature : Sensor
{
private:
    char *humidity;

public:
    Temperature(int pin) : Sensor("atm/temperature/value", pin){};
    const char *humidityTopic = "atm/temperature/humidity";
    void measureValue()
    {
        // TEMP AND HUMIDITY SENSOR °C
        float temp;
        float hum;
        if (dht_sensor.measure(&temp, &hum))
        {
            int len = sprintf(this->value, "%f", temp);
            this->value[len] = '\0';
            len = sprintf(this->humidity, "%f", hum);
            this->humidity[len] = '\0';
        }
    }

    char *getValue()
    {
        return this->value;
    }

    char *getTopic()
    {
        return this->topic;
    }

    char *getHumidity()
    {
        return this->humidity;
    }
};