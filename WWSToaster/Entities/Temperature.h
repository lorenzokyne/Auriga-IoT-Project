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
    Temperature(int pin) : Sensor(pin)
    {
        dht_sensor.begin();
    };
    void measureValue(char *value)
    {
        // TEMP AND HUMIDITY SENSOR °C
        char str_temp[7], str_hum[7];
        float temp = dht_sensor.readTemperature();
        float hum = dht_sensor.readHumidity();
        dtostrf(temp, 4, 2, str_temp);
        dtostrf(hum, 4, 2, str_hum);
        uint8_t len = sprintf(value, "%s,%s", str_temp, str_hum);
        value[len] = '\0';
    }
};