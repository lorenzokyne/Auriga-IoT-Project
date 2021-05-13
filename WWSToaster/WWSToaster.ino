#include <SoftwareSerial.h>
#include "MQTT.h"
#include "sensors.h"

const int SIM_RX_PIN = 7;
const int SIM_TX_PIN = 8;

unsigned long count = 0;
int len;

extern SoftwareSerial Serial1;
MQTT mqtt(Serial);

const char *clientName = "WWSToaster-00";
const char *username = "atm";
const char *password = "atm";

void publish(char* topic, char* sensorValue, int QoS = 0){
  mqtt.publish(topic, sensorValue, QoS);
}

void setup()
{
  Serial.begin(9600);

  initConnection();

  // GPS
  // gpsSerial.begin(9600); // connect gps sensor
}

void loop()
{
  delay(5000);
  if (mqtt.isConnected())
  {
    // float temperature;
    // float humidity;
    // char temp[5];
    // getTempHumidity(&temperature, &humidity);
    // int tempLen = snprintf((char *)temp, 5,"%f", temperature);
    // temp[tempLen] = '\0';
    // mqtt.OUT->println(temp);
    // mqtt.publish("atm/temperature/value", temp, 0);
    char value[5];
    microphone(value);
    mqtt.OUT->println(value);
    mqtt.publish("atm/microphone/value", value, 0);
    // publish("atm/darkness/value",brightness());
    // publish("atm/microphone/value",microphone());
    // publish("atm/microphone/value",microphone());
  }
  mqtt.loop();
  // else
  // {
  //   initConnection();
  // }

  delay(1000);
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
