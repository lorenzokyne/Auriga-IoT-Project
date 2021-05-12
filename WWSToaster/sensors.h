#include <dht_nonblocking.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11

//SENSORS PIN
const int BIG_SOUND_PIN = 11;
const int DHT11_PIN = 2;
const int GPS_RX_PIN = 4;
const int GPS_TX_PIN = 3;
const int RELAY_PIN = 9;
const int PHOTO_RES_PIN = A0;
const int LH_MAGNETIC_AO_PIN = A1;
const int BIG_SOUND_AO_PIN = A2;
const int GYRO_SDA_PIN = A4;
const int GYRO_SCL_PIN = A5;

// //GYRO
// const int MPU_addr = 0x68; // I2C address of the MPU-6050
// int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

DHT_nonblocking dht_sensor(DHT11_PIN, DHT_SENSOR_TYPE);
int brightnessAnalogValue = 0;
int soundAnalogValue = 0;
int linearHallValue = 0;
float temperature;
float humidity;
float analogValue;
float digitalValue;

// SoftwareSerial gpsSerial(GPS_TX_PIN, GPS_RX_PIN); //arduino tx -> gps rx
// TinyGPS gps;
float lat = 0, lon = 0; // create variable for latitude and longitude

int brightness()
{
    // BRIGHTNESS SENSOR
    // 0 = LIGHT - 1000 = DARKNESS
    brightnessAnalogValue = analogRead(PHOTO_RES_PIN);
    Serial.println(brightnessAnalogValue, DEC);
    return brightnessAnalogValue;
}

void getTempHumidity(float &temperature, float &umidity)
{
    // TEMP AND HUMIDITY SENSOR °C
    if (dht_sensor.measure(&temperature, &humidity))
    {
        Serial.print("T = ");
        Serial.print(temperature, 1);
        Serial.print(" deg. C, H = ");
        Serial.print(humidity, 1);
        Serial.println("%");
    }
}

void gyro()
{
    //// GYRO
    // Wire.begin();
    // Wire.beginTransmission(MPU_addr);
    // Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
    // Wire.endTransmission(false);
    // Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
    // AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    // AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    // AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    // // Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    // GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    // GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    // GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    // Serial.print("AcX = ");
    // Serial.print(AcX);
    // Serial.print(" | AcY = ");
    // Serial.println(AcY);
    // Serial.print(" | AcZ = ");
    // Serial.print(AcZ);
    // Serial.print(" | Tmp = ");
    // Serial.print(Tmp / 340.00 + 36.53); //equation for temperature in degrees C from datasheet
    // Serial.print(" | GyX = ");
    // Serial.print(GyX);
    // Serial.print(" | GyY = ");
    // Serial.println(GyY);
    // Serial.print(" | GyZ = ");
    // Serial.println(GyZ);
    // delay(333);
}

// void gpsCall()
// {

//     Serial.println("Searching GPS signal...");
//     while (gpsSerial.available())
//     {
//         Serial.print("READ: " + gpsSerial.read()); // check for gps data
//         if (gps.encode(gpsSerial.read()))          // encode gps data
//         {
//             gps.f_get_position(&lat, &lon); // get latitude and longitude
//             // display position

//             Serial.println("Position: ");
//             Serial.print("Latitude:");
//             Serial.print(lat, 6);
//             Serial.print(";");
//             Serial.print("Longitude:");
//             Serial.println(lon, 6);

//             Serial.print(lat);
//             Serial.print(" ");
//         }
//         String latitude = String(lat, 6);
//         String longitude = String(lon, 6);
//         Serial.println(latitude + ";" + longitude);
//         delay(1000);
//     }
//     delay(500);
// }

void switchRelayOn()
{
    digitalWrite(RELAY_PIN, HIGH);
}

void switchRelayOff()
{
    digitalWrite(RELAY_PIN, LOW);
}

int linear_hall()
{
    // LINEAR HALL
    linearHallValue = analogRead(LH_MAGNETIC_AO_PIN);
    Serial.println(linearHallValue, DEC);
    return linearHallValue;
}

float microphone()
{
    // MICROPHONE SENSOR
    analogValue = analogRead(BIG_SOUND_AO_PIN); // Read the value of the analog interface A0 assigned to digitalValue
    digitalValue = digitalRead(BIG_SOUND_PIN);  // Read the value of the digital interface 7 assigned to digitalValue
    Serial.print("ANALOG = ");
    Serial.println(analogValue);
    return analogValue;
}