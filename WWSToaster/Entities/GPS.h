#ifndef SENSOR_H
#define SENSOR_H
#include "Sensor.h"
#endif
#include "Arduino.h"
#include <TinyGPS.h>

SoftwareSerial gpsSerial(GPS_TX_PIN, GPS_RX_PIN); //arduino tx -> gps rx
class GPS : Sensor
{
private:
    int rxPin;
    TinyGPS gps;

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
        float lat = 41.09549121687406, lon = 16.862459713449084; // create variable for latitude and longitude
        // Serial.println("Searching GPS signal...");
        while (gpsSerial.available())
        {// check for gps data
            if (gps.encode(gpsSerial.read())) // encode gps data
            {
                gps.f_get_position(&lat, &lon); // get latitude and longitude
            }
        }
        char latitude[11], longitude[11];
        dtostrf(lat, 10, 6, latitude);
        dtostrf(lon, 10, 6, longitude);
        int len = sprintf(value, "GPS:Lat:%s;Lon:%s", latitude, longitude);
        value[len] = '\0';
    }
};