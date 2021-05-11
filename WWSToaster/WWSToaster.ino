// #include <dht_nonblocking.h>
// #include <Wire.h>
#include <SoftwareSerial.h>
// #include <TinyGPS.h>
#include "MQTT.h"

// #define DHT_SENSOR_TYPE DHT_TYPE_11

// SENSORS PIN
// const int BIG_SOUND_PIN = 11;
// const int DHT11_PIN = 2;
// const int GPS_RX_PIN = 4;
// const int GPS_TX_PIN = 3;
const int SIM_RX_PIN = 7;
const int SIM_TX_PIN = 8;
// const int RELAY_PIN = 9;
// const int PHOTO_RES_PIN = A0;
// const int LH_MAGNETIC_AO_PIN = A1;
// const int BIG_SOUND_AO_PIN = A2;
// const int GYRO_SDA_PIN = A4;
// const int GYRO_SCL_PIN = A5;

// GYRO
// const int MPU_addr = 0x68; // I2C address of the MPU-6050
// int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

// DHT_nonblocking dht_sensor(DHT11_PIN, DHT_SENSOR_TYPE);
// int brightnessAnalogValue = 0;
// int soundAnalogValue = 0;
// int linearHallValue = 0;
// float temperature;
// float humidity;
// float analogValue;
// float digitalValue;

// SoftwareSerial mySerial(SIM_TX_PIN, SIM_RX_PIN);

// SoftwareSerial gpsSerial(GPS_TX_PIN, GPS_RX_PIN); //arduino tx -> gps rx
// TinyGPS gps;
// float lat = 0, lon = 0; // create variable for latitude and longitu

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
    // mqtt.subscribe("sendeep");
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

  // //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  // Serial.begin(9600);

  // //Begin serial communication with Arduino and SIM800L
  // mySerial.begin(9600);

  // Serial.println("Initializing...");
  // delay(1000);

  // mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  // updateSerial();
  // mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  // updateSerial();
  // mySerial.println("AT+CMEE=2");
  // updateSerial();
  // delay(5000);
  // mySerial.println("AT+CREG=0");
  // updateSerial();
  // mySerial.println("AT+CREG=1");
  // updateSerial();
  // mySerial.println("AT+CREG=2");
  // updateSerial();
  // updateSerial();
  // mySerial.println("AT+COPS=?");
  // updateSerial();
  // delay(15000);
  // mySerial.println("AT+COPS?");
  // updateSerial();

  // delay(15000);
  // // mySerial.println("AT+COPS=1,0,\"22210\"");
  // // updateSerial();
  // // delay(10000);
  // // mySerial.println("AT+COPS=2");
  // // updateSerial();
  // // delay(10000);
  // mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  // updateSerial();
  // // mySerial.println("AT+CFUN = 0");
  // // updateSerial();
  // // delay(5000);
  // // mySerial.println("AT+CFUN = 1");
  // // updateSerial();
  // delay(1000);
  // mySerial.println("AT+CGREG?"); //Check whether it has registered in the network
  // updateSerial();
  // mySerial.println("AT+CBC");
  // updateSerial();
  // delay(1000);
  // mySerial.println("AT+CSTT=\"mobile.vodafone.it\",\"\",\"\"");
  // updateSerial();
  // delay(1000);
  // mySerial.println("AT+CIICR");
  // updateSerial();
  // delay(1000);
  // mySerial.println("AT+CIFSR");
  // updateSerial();
  // delay(5000);
  // // mySerial.println("AT+CIPSTART=\"TCP\",\"93.63.173.7\",\"1883\"");
  // mySerial.println("AT+CIPSTART=\"TCP\",\"test.mosquitto.org\",\"1883\"");
  // updateSerial();
  // delay(3000);
  // mySerial.println("AT+CIPSEND");
  // updateSerial();

  // // mySerial.println("AT+CMGF=1\r");
  // // mySerial.println("AT+CMGS=\"+39xxxxxxxxxx\"\r");
  // // updateSerial();
  // delay(1000);
  // mySerial.write("Ciao sono WWS Toaster, l'Arduino di Auriga S.p.A. <3");
  // delay(500);
  // mySerial.write((char)26);
  // delay(500);
  // mySerial.println("AT+CIPCLOSE");
  // updateSerial();

  // connect("Auriga01", 0, 0, "", "", 1, 0, 0, 0, "", "");
  // GPS
  // gpsSerial.begin(9600); // connect gps sensor
}

// void connect(char *ClientIdentifier, char UserNameFlag, char PasswordFlag, char *UserName, char *Password, char CleanSession, char WillFlag, char WillQoS, char WillRetain, char *WillTopic, char *WillMessage)
// {
//   // ConnectionAcknowledgement = NO_ACKNOWLEDGEMENT;
//   char array[256];
//   sprintf(array, "0x%x", (char)(1 * 16));
//   char ProtocolName[7] = "MQTT";
//   int localLength = (2 + strlen(ProtocolName)) + 1 + 3 + (2 + strlen(ClientIdentifier));
//   if (WillFlag != 0)
//   {
//     localLength = localLength + 2 + strlen(WillTopic) + 2 + strlen(WillMessage);
//   }
//   if (UserNameFlag != 0)
//   {
//     localLength = localLength + 2 + strlen(UserName);

//     if (PasswordFlag != 0)
//     {
//       localLength = localLength + 2 + strlen(Password);
//     }
//   }
//   char* aaa;
//   strcat(aaa, sendLength(localLength));
//   strcat(aaa, sendUTFString(ProtocolName));
//   strcat(aaa, ""+(char(4)));
//   strcat(aaa, ""+(char(UserNameFlag * 128 + PasswordFlag * 64 + WillRetain * 32 + WillQoS * 8 + WillFlag * 4 + CleanSession * 2)));
//   strcat(aaa, ""+(char(60 / 256)));
//   strcat(aaa, ""+(char(60 % 256)));
//   strcat(aaa, sendUTFString(ClientIdentifier));
//   if (WillFlag != 0)
//   {
//     strcat(aaa, sendUTFString(WillTopic));
//     strcat(aaa, sendUTFString(WillMessage));
//   }
//   if (UserNameFlag != 0)
//   {
//     strcat(aaa, sendUTFString(UserName));
//     if (PasswordFlag != 0)
//     {
//       strcat(aaa, sendUTFString(Password));
//     }
//   }
//   publish(0,0,0,1,"hello", "aaas");
// }

// void publish(char DUP, char Qos, char RETAIN, unsigned int MessageID, char *Topic, char *Message)
// {
//   Serial.print(char(3 * 16 + DUP * 8 + Qos * 2 + RETAIN));
//   int localLength = (2 + strlen(Topic));
//   if (Qos > 0)
//   {
//     localLength += 2;
//   }
//   localLength += strlen(Message);
//   sendLength(localLength);
//   sendUTFString(Topic);
//   if (Qos > 0)
//   {
//     Serial.print(char(MessageID / 256));
//     Serial.print(char(MessageID % 256));
//   }
//   Serial.print(Message);
// }

// char* sendUTFString(char *string)
// {
//   int localLength = strlen(string);
//   char* finale;
//   const char* div =  ""+(char(localLength / 256));
//   const char* perc = ""+(char(localLength % 256));
//   return strcat(strcat(strcat(finale, div), perc), string);

// }

// char* sendLength(int len)
// {
//   bool length_flag = false;
//   char* final;
//   while (length_flag == false)
//   {
//     if ((len / 128) > 0)
//     {
//       const char* a = ""+(char(len % 128 + 128));
//       strcat(final, a);
//       len /= 128;
//     }
//     else
//     {
//       length_flag = true;
//       const char* b =  ""+(char(len));
//      strcat(final,b);
//     }
//   }
// }

int k = 0;
void loop()
{
  k++;
  if (mqtt.isConnected())
  {
    k=0;
    len = sprintf((char *)msg, "%u", 65);
    msg[len] = '\0';
    mqtt.publish("gps", msg, 0);
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

// void updateSerial()
// {
//   delay(500);
//   while (Serial.available())
//   {
//     mySerial.write(Serial.read()); //Forward what Serial received to Software Serial Port
//   }
//   while (mySerial.available())
//   {
//     Serial.write(mySerial.read()); //Forward what Software Serial received to Serial Port
//   }
// }

// void brightness()
// {
//   // BRIGHTNESS SENSOR
//   // 0 = LIGTH - 1000 = DARKESS
//   brightnessAnalogValue = analogRead(PHOTO_RES_PIN);
//   Serial.println(brightnessAnalogValue, DEC);
// }

// void temp_humidity()
// {
//   // TEMP AND HUMIDITY SENSOR °C
//   if (dht_sensor.measure(&temperature, &humidity))
//   {
//     Serial.print("T = ");
//     Serial.print(temperature, 1);
//     Serial.print(" deg. C, H = ");
//     Serial.print(humidity, 1);
//     Serial.println("%");
//   }
// }

// void gyro()
// {
//   // GYRO
//   Wire.beginTransmission(MPU_addr);
//   Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
//   Wire.endTransmission(false);
//   Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
//   AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
//   AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
//   AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
//   // Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
//   GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
//   GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
//   GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
//   Serial.print("AcX = ");
//   Serial.print(AcX);
//   Serial.print(" | AcY = ");
//   Serial.println(AcY);
//   Serial.print(" | AcZ = ");
//   Serial.print(AcZ);
//   Serial.print(" | Tmp = ");
//   Serial.print(Tmp / 340.00 + 36.53); //equation for temperature in degrees C from datasheet
//   Serial.print(" | GyX = ");
//   Serial.print(GyX);
//   Serial.print(" | GyY = ");
//   Serial.println(GyY);
//   Serial.print(" | GyZ = ");
//   Serial.println(GyZ);
//   delay(333);
// }

// void gpsCall()
// {

//   // Serial.println("Searching GPS signal...");
//   // while (gpsSerial.available())
//   // {
//   //   Serial.print("READ: " + gpsSerial.read()); // check for gps data
//   //   if (gps.encode(gpsSerial.read()))          // encode gps data
//   //   {
//   //     gps.f_get_position(&lat, &lon); // get latitude and longitude
//   //     // display position

//   //     Serial.println("Position: ");
//   //     Serial.print("Latitude:");
//   //     Serial.print(lat, 6);
//   //     Serial.print(";");
//   //     Serial.print("Longitude:");
//   //     Serial.println(lon, 6);

//   //     Serial.print(lat);
//   //     Serial.print(" ");
//   //   }
//   //   String latitude = String(lat, 6);
//   //   String longitude = String(lon, 6);
//   //   Serial.println(latitude + ";" + longitude);
//   //   delay(1000);
//   // }
//   // delay(500);
// }

// void relay()
// {

//   // RELAY
//   digitalWrite(RELAY_PIN, HIGH);
//   delay(1000);
//   digitalWrite(RELAY_PIN, LOW);
//   delay(1000);
// }

// void linear_hall()
// {

//   // LINEAR HALL
//   linearHallValue = analogRead(LH_MAGNETIC_AO_PIN);
//   Serial.println(linearHallValue, DEC);
// }

// void microphone()
// {
//   // MICROPHONE SENSOR
//   analogValue = analogRead(BIG_SOUND_AO_PIN); // Read the value of the analog interface A0 assigned to digitalValue
//   digitalValue = digitalRead(BIG_SOUND_PIN);  // Read the value of the digital interface 7 assigned to digitalValue
//   Serial.print("ANALOG = ");
//   Serial.println(analogValue);
//   delay(200);
// }
