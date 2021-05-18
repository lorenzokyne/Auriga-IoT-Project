#ifndef SENSOR_H
#define SENSOR_H
#include "Sensor.h"
#endif
#include "Arduino.h"
#include <dht_nonblocking.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
//TODO -- THIS SENSOR NEEDS TO BE CHECKED BECAUSE IT ISNT WORKING PROPERLY
class Temperature : Sensor
{

public:
    Temperature(int pin) : Sensor(pin)
    {
        dht_sensor.begin();
    };
    void measureValue(char*value)
    {
        // TEMP AND HUMIDITY SENSOR °C

        uint8_t len = sprintf(value, "%f,%f",  dht_sensor.readTemperature(),dht_sensor.readHumidity());
        value[len] = '\0';
    }
};