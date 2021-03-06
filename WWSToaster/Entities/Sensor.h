//SENSORS PIN
const int DHT11_PIN = 2;
const int GPS_RX_PIN = 4;
const int GPS_TX_PIN = 3;
const int SIM_RX_PIN = 6;
const int SIM_TX_PIN = 7;
const int RELAY_PIN = 5;
const int MOTION_PIN = A0;
const int LH_MAGNETIC_AO_PIN = A1;
const int BIG_SOUND_AO_PIN = A2;
const int PHOTO_RES_PIN = A3;
const int GYRO_SDA_PIN = A4;
const int GYRO_SCL_PIN = A5;
#include <time.h>
bool debugMode = false;
class Sensor
{
protected:
    int pin;

public:
    Sensor(int pin)
    {
        this->pin = pin;
        debugMode = false;
    };
    Sensor(){};
    virtual void measureValue(char *value);
};
