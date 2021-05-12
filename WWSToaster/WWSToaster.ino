#include <SoftwareSerial.h>
#include "MQTT.h"
#include "sensors.h"

const int SIM_RX_PIN = 7;
const int SIM_TX_PIN = 8;

unsigned long count = 0;
char msg[10];
int len;

extern SoftwareSerial Serial1;
MQTT mqtt(Serial);

void setup()
{
  Serial.begin(9600);
  // Serial1.begin(9600);

  if (mqtt.initialize())
  {
    mqtt.connect("WWSToaster-00", "atm", "atm");
    // mqtt.subscribe("atm");
    // mqtt.OUT->println(F("Connected & Subscribed..."));
  }
  else
  {
    mqtt.OUT->println(F("Unable to connect to the network.."));
  }
  // Wire.begin();
  // Wire.beginTransmission(MPU_addr);
  // Wire.write(0x6B); // PWR_MGMT_1 register
  // Wire.write(0);    // set to zero (wakes up the MPU-6050)
  // Wire.endTransmission(true);
  // Serial.begin(9600);
  // pinMode(BIG_SOUND_PIN, INPUT);
  // pinMode(RELAY_PIN, OUTPUT);

  

  // connect("Auriga01", 0, 0, "", "", 1, 0, 0, 0, "", "");
  // GPS
  // gpsSerial.begin(9600); // connect gps sensor
}

int k = 0;
void loop()
{
  delay(5000);
  k++;
  if (mqtt.isConnected())
  {
    k = 0;
    len = sprintf((char *)msg, "%u", count++);
    msg[len] = '\0';
    mqtt.publish("atm/gps/location", msg, 0);
    
  }
  if (k < 5)
    mqtt.loop();
  else
    mqtt.disconnect();

  delay(1000);
}

void serialEvent1()
{
  mqtt.serialEvent();
}
