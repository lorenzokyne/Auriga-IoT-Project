#include <dht_nonblocking.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11

const int BIG_SOUND_PIN = 1;
const int DHT11_PIN = 2;
const int GPS_RX_PIN = 3;
const int GPS_TX_PIN = 4;
const int SIM_RX_PIN = 7;
const int SIM_TX_PIN = 8;
const int RELAY_PIN = 9;
const int PHOTO_RES_PIN = A0;
const int LH_MAGNETIC_AO_PIN = A1;
const int BIG_SOUND_AO_PIN = A2;
const int GYRO_SDA_PIN = A4;
const int GYRO_SCL_PIN = A5;

// GYRO
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

DHT_nonblocking dht_sensor(DHT11_PIN, DHT_SENSOR_TYPE);
int brightnessAnalogValue = 0;
int soundAnalogValue = 0;
int linearHallValue = 0;
float temperature;
float humidity;

SoftwareSerial mySerial(SIM_TX_PIN, SIM_RX_PIN);

void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode(BIG_SOUND_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  mySerial.println("AT+CBC"); 
  updateSerial();
}
void loop()
{
  // TEMP AND HUMIDITY SENSOR °C 
  // if (dht_sensor.measure(&temperature, &humidity))
  // {
  //   Serial.print("T = ");
  //   Serial.print(temperature, 1);
  //   Serial.print(" deg. C, H = ");
  //   Serial.print(humidity, 1);
  //   Serial.println("%");
  // } 

  // MICROPHONE SENSOR
  // analogValue = analogRead(BIG_SOUND_AO_PIN); // Read the value of the analog interface A0 assigned to digitalValue
  // digitalValue=digitalRead(BIG_SOUND_PIN); // Read the value of the digital interface 7 assigned to digitalValue
  // Serial.print("ANALOG = ");
  // Serial.println(analogValue);
  // delay(200);

  // BRIGHTNESS SENSOR
  // 0 = LIGTH - 1000 = DARKESS
  //  brightnessAnalogValue = analogRead(PHOTO_RES_PIN);
  //  Serial.println(brightnessAnalogValue, DEC);

  // LINEAR HALL
  //  linearHallValue = analogRead(LH_MAGNETIC_AO_PIN);
  //  Serial.println(linearHallValue, DEC);

  // RELAY
  // digitalWrite(RELAY_PIN, HIGH);
  // delay(1000);
  // digitalWrite(RELAY_PIN, LOW);
  // delay(1000);

  // GYRO
//   Wire.beginTransmission(MPU_addr);
//   Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
//   Wire.endTransmission(false);
//   Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
//   AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
//   AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
//   AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
//   // Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
//   GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
//   GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
//   GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
//   Serial.print("AcX = "); Serial.print(AcX);
//   Serial.print(" | AcY = "); Serial.println(AcY);
//  Serial.print(" | AcZ = "); Serial.print(AcZ);
//  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
//  Serial.print(" | GyX = "); Serial.print(GyX);
//   Serial.print(" | GyY = "); Serial.println(GyY);
//  Serial.print(" | GyZ = "); Serial.println(GyZ);
//   delay(333);

  // updateSerial();
}

// void Serialcom(){
//   delay(500);
//   while (Serial.available())
//   {
//     sim800l.write(Serial.read());
//   }
//   while (sim800l.available())
//   {
//     Serial.write(sim800l.read());
  // }

  void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}