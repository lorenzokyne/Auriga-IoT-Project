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
const char *SERVER_ADDRESS = "SERVER ADDRESS HERE";
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

void(* Reset)(void) = 0;
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

void publish(const char *topic, char* sensorValue, int QoS = 0)
{
  mqtt.publish(topic, sensorValue, QoS);
}

void setup()
{
  srand(static_cast<unsigned>(time(0)));
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
  char sensorValue[90];
  if (mqtt.isConnected())
  {
    if (gpsOnlyMode)
    {
      gpsModule.measureValue(sensorValue);
      publish(gpsTopic, sensorValue);
    }
    else
    {
      publishSensors(sensorValue);
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
  if (!mqtt.isConnected()){
    Reset();
  }
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
    mqtt.OUT->println(F("Unable to connect to the network...retrying"));
    initConnection();
  }
}

void publishSensors(char* sensorValue)
{
  gpsModule.measureValue(sensorValue);
  Serial1.listen();
  publish(gpsTopic, sensorValue);
  delay(200);
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
  linearHall.measureValue(sensorValue);
  publish(linearHallTopic, sensorValue);
  delay(200);
  motion.measureValue(sensorValue);
  publish(motionTopic, sensorValue);
}

void checkStatus()
{
  if (linearHall.checkThreshold() || strcmp(mqtt.receivedMessage, "Stacca stacca!") == 0)
  {
    display.turnOff();
  }
  else if (strcmp(mqtt.receivedMessage, "send gps") == 0)
  {
    gpsOnlyMode = true;
    display.turnOff();
  }
  else if (strcmp(mqtt.receivedMessage, "Apri tutto") == 0)
  {
    display.turnOn();
    mqtt.receivedMessage[0] = '\0';
  }
  else if (strcmp(mqtt.receivedMessage, "debug") == 0)
  {
    debugMode = !debugMode;
    mqtt.receivedMessage[0] = '\0';
  }
}
