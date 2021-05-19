#include <SoftwareSerial.h>
#include <MQTT.h>
#include "Entities\Microphone.h"
#include "Entities\Brightness.h"
#include "Entities\Temperature.h"
#include "Entities\Gyroscope.h"

//Environment vars
const char *SERVER_ADDRESS = "93.63.173.7";
const int SERVER_PORT = 1883;
const char *clientName = "WWSToaster-00";
const char *username = "atm";
const char *password = "atm";

const char *gyroTopic = "atm/gyro/value";
const char *temperatureTopic = "atm/temperature/value";
const char *brightnessTopic = "atm/darkness/value";
const char *microphoneTopic = "atm/microphone/value";
char sensorValue[100];

extern SoftwareSerial Serial1;
MQTT mqtt((char *)SERVER_ADDRESS, (int)SERVER_PORT, Serial);

//Sensors instances
Brightness brightness(PHOTO_RES_PIN);
Temperature temperature(DHT11_PIN);
Gyroscope gyroscope(GYRO_SDA_PIN);
Microphone microphone(BIG_SOUND_AO_PIN);

void publish(const char *topic, char *sensorValue, int QoS = 0)
{
  mqtt.publish(topic, sensorValue, QoS);
}

void setup()
{
  Serial.begin(9600);
  initConnection();
  Wire.begin();
  Wire.beginTransmission(gyroscope.MPU_addr);
  Wire.write(0x6B);
  Wire.write(0); // set zero (wakes up the MPU-6050
  Wire.endTransmission(true);
  TWCR = 0;
  // GPS
  // gpsSerial.begin(9600); // connect gps sensor
}

void loop()
{
  delay(5000);
  if (mqtt.isConnected())
  {
    microphone.measureValue(sensorValue);
    publish(microphoneTopic, sensorValue);
    delay(200);
    brightness.measureValue(sensorValue);
    publish(brightnessTopic, sensorValue);
    delay(200);
    temperature.measureValue(sensorValue);
    publish(temperatureTopic, sensorValue);
    delay(200);
    gyroscope.measureValue(sensorValue);
    publish(gyroTopic, sensorValue);
    delay(200);
  }
  mqtt.loop();
}

void serialEvent1()
{
  mqtt.serialEvent();
}

void initConnection()
{
  if (mqtt.initialize())
  {
    mqtt.connect(clientName, username, password);
    mqtt.subscribe((char *)clientName);
    mqtt.OUT->println(F("Connected & Subscribed..."));
  }
  else
  {
    mqtt.OUT->println(F("Unable to connect to the network.."));
  }
}
