#include <SoftwareSerial.h>
#include <MQTT.h>
#include "Entities\Microphone.h"
#include "Entities\Brightness.h"
#include "Entities\Temperature.h"
#include "Entities\Gyroscope.h"
#include "Entities\LinearHall.h"
#include "Entities\GPS.h"
#include "Entities\Display.h"
#include "Entities\Motion.h"
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
const char *linearHallTopic = "atm/linearhall/value";
const char *gpsTopic = "atm/gps/value";
const char *motionTopic = "atm/motion/value";
char sensorValue[100];

SoftwareSerial Serial1(SIM_TX_PIN, SIM_RX_PIN);
SoftwareSerial gpsSerial(GPS_TX_PIN, GPS_RX_PIN); //arduino tx -> gps rx
MQTT mqtt((char *)SERVER_ADDRESS, (int)SERVER_PORT, Serial);

bool gpsOnlyMode = false;

//Sensors instances
GPS gpsModule;
Brightness brightness(PHOTO_RES_PIN);
Temperature temperature(DHT11_PIN);
Gyroscope gyroscope(GYRO_SDA_PIN);
Microphone microphone(BIG_SOUND_AO_PIN);
LinearHall linearHall(LH_MAGNETIC_AO_PIN);
Motion motion(MOTION_PIN);
Display display;

void publish(const char *topic, int QoS = 0)
{
  mqtt.publish(topic, sensorValue, QoS);
}

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
  gpsModule.setup();
  display.setup();
  initConnection();
  gyroscope.setup();
  display.started();
}

void loop()
{
  if (mqtt.isConnected())
  {
    if (gpsOnlyMode)
    {
      gpsModule.measureValue(sensorValue);
      publish(gpsTopic);
    }
    else
    {
      publishSensors();
    }
  }

  if (gpsOnlyMode)
  {
    delay(1000);
  }
  else
  {
    delay(5000);
  }

  mqtt.loop();
  checkStatus();
  
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

void publishSensors()
{
  gpsModule.measureValue(sensorValue);
  Serial1.listen();
  publish(gpsTopic);
  delay(200);
  microphone.measureValue(sensorValue);
  publish(microphoneTopic);
  delay(200);
  brightness.measureValue(sensorValue);
  publish(brightnessTopic);
  delay(200);
  temperature.measureValue(sensorValue);
  publish(temperatureTopic);
  delay(200);
  gyroscope.measureValue(sensorValue);
  publish(gyroTopic);
  delay(200);
  linearHall.measureValue(sensorValue);
  publish(linearHallTopic);
  delay(200);
  motion.measureValue(sensorValue);
  publish(motionTopic);
}

void checkStatus(){
  
  if (strcmp(mqtt.receivedMessage, "Stacca stacca!") == 0)
  {
    display.turnOff();
  }
  else if (strcmp(mqtt.receivedMessage, "send gps") == 0)
  {
    gpsOnlyMode = true;
  }
  else if (strcmp(mqtt.receivedMessage, "Apri tutto") == 0)
  {
    display.turnOn();
  }
}
