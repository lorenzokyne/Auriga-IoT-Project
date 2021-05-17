//SENSORS PIN
const int DHT11_PIN = 2;
const int GPS_RX_PIN = 4;
const int GPS_TX_PIN = 3;
const int SIM_RX_PIN = 7;
const int SIM_TX_PIN = 8;
const int RELAY_PIN = 9;
const int PHOTO_RES_PIN = A0;
const int LH_MAGNETIC_AO_PIN = A1;
const int BIG_SOUND_AO_PIN = A2;
const int GYRO_SDA_PIN = A4;
const int GYRO_SCL_PIN = A5;

class Sensor
{
protected:
    char *topic;
    int pin;

public:
    Sensor(char *topic, int pin)
    {
        this->topic = (char *)malloc(sizeof(char) * strlen(topic));
        this->topic = topic;
        this->pin = pin;
    };
    virtual void measureValue(char * value);
    virtual char *getTopic();
};