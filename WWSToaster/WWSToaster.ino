#include <SoftwareSerial.h>
#include "MQTT.h"
// #include "sensors.h"

const int SIM_RX_PIN = 7;
const int SIM_TX_PIN = 8;

unsigned long count = 0;
int len;

extern SoftwareSerial Serial1;
MQTT mqtt(Serial);

const char* clientName = "WWSToaster-00";
const char* username = "atm";
const char* password = "atm";

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
    char msg[10];
    len = sprintf((char *)msg, "%s", "Hello");
    msg[len] = '\0';
    mqtt.publish("atm/gps/location", msg, 0);
    
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
    mqtt.subscribe((char*)clientName);
    mqtt.OUT->println(F("Connected & Subscribed..."));
  }
  else
  {
    mqtt.OUT->println(F("Unable to connect to the network.."));
  }
}
