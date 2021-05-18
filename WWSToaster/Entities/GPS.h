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
        float lat = 0, lon = 0; // create variable for latitude and longitude
        // Serial.println("Searching GPS signal...");
        if (gpsSerial.available())
        {
            // Serial.print("READ: " + gpsSerial.read()); // check for gps data
            if (gps.encode(gpsSerial.read())) // encode gps data
            {
                gps.f_get_position(&lat, &lon); // get latitude and longitude
            }
            String latitude = String(lat, 6);
            String longitude = String(lon, 6);
            int len = sprintf(value, "Lat:%s;Lon:%s", latitude, longitude);
            value[len] = '\0';
        }
    }
};