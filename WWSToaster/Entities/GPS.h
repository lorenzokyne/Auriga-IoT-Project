#ifndef SENSOR_H
#define SENSOR_H
#include "Sensor.h"
#endif
#include "Arduino.h"
#include <TinyGPS.h>

extern SoftwareSerial gpsSerial; //arduino tx -> gps rx

TinyGPS gps;

class GPS : Sensor
{
private:
    int rxPin;

public:
    GPS() : Sensor(){};

    void setup()
    {
        gpsSerial.begin(9600); // connect gps sensor
    }

    void measureValue(char *value)
    {
        gpsSerial.listen();
        value[0] = '\0';
        float lat = 41.095491, lon = 16.862459; // create variable for latitude and longitude
        unsigned long age;

        smartdelay(1000);
        gps.satellites();
        gps.hdop();
        gps.f_get_position(&lat, &lon, &age);
        char latitude[12];
        char longitude[12];
        dtostrf(lat, 11, 6, latitude);
        dtostrf(lon, 11, 6, longitude);
        int len = sprintf(value, "GPS:Lat:%s;Lon:%s", latitude, longitude);
        value[len] = '\0';
    }

    static void smartdelay(unsigned long ms)
    {
        unsigned long start = millis();
        do
        {
            while (gpsSerial.available())
                gps.encode(gpsSerial.read());
        } while (millis() - start < ms);
    }
};