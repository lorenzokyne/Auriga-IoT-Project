class Sensor
{
protected:
    char *value = "";
    char *topic;
    int pin;

public:
    Sensor(char *topic, int pin)
    {
        this->topic = topic;
        this->pin = pin;
    };
    virtual void measureValue();
    virtual char *getValue();
    virtual char *getTopic();
};