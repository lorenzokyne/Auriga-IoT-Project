#ifndef SENSOR_H
#define SENSOR_H
#include "Sensor.h"
#endif
#include "Arduino.h"
#include <DHT.h>

#define DHT_SENSOR_TYPE DHT11
DHT dht_sensor(DHT11_PIN, DHT_SENSOR_TYPE);
//TODO -- THIS SENSOR NEEDS TO BE CHECKED BECAUSE IT ISNT WORKING PROPERLY
class Temperature : Sensor
{

public:
    Temperature(int pin) : Sensor((char *)"atm/temperature/value", pin)
    {
        dht_sensor.begin();
    };
    const char *humidityTopic = "atm/temperature/humidity";
    void measureValue(char*value)
    {
        // TEMP AND HUMIDITY SENSOR °C
        float temp = dht_sensor.readTemperature();
        float hum = dht_sensor.readHumidity();

        int len = sprintf(value, "%f,%f", temp+hum);
        value[len] = '\0';
    }

    char *getTopic()
    {
        return this->topic;
    }
};