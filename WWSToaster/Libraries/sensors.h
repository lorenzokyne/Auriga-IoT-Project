
// #include <Wire.h>
// #include <SoftwareSerial.h>
// #include <TinyGPS.h>


//SENSORS PIN
const int DHT11_PIN = 2;
const int GPS_RX_PIN = 4;
const int GPS_TX_PIN = 3;
const int SIM_RX_PIN = 7;
const int SIM_TX_PIN = 8;
const int RELAY_PIN = 9;
const int PHOTO_RES_PIN = A0;
const int LH_MAGNETIC_AO_PIN = A1;
const int BIG_SOUND_AO_PIN = A2;
const int GYRO_SDA_PIN = A4;
const int GYRO_SCL_PIN = A5;

// // //GYRO
// // const int MPU_addr = 0x68; // I2C address of the MPU-6050
// // int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

// int soundAnalogValue = 0;
// int linearHallValue = 0;
// float analogValue;
// float digitalValue;

// // SoftwareSerial gpsSerial(GPS_TX_PIN, GPS_RX_PIN); //arduino tx -> gps rx
// // TinyGPS gps;
// float lat = 0, lon = 0; // create variable for latitude and longitude

char *brightnessTest()
{
    // BRIGHTNESS SENSOR
    // 0 = LIGHT - 1000 = DARKNESS
    int brightnessAnalogValue = 0;
    char brightnessStr[5];
    brightnessAnalogValue = analogRead(PHOTO_RES_PIN);
    int StrLen = sprintf((char *)brightnessStr, "%d", brightnessAnalogValue);
    brightnessStr[StrLen] = '\0';
    return brightnessStr;
}

void tempHumidityTest(float *temperature, float *humidity)
{
    // TEMP AND HUMIDITY SENSOR °C
    if (dht_sensor.measure(temperature, humidity))
    {
        Serial.print("T = ");
        Serial.print(*temperature, 1);
        Serial.print(" deg. C, H = ");
        Serial.print(*humidity, 1);
        Serial.println("%");
    }
}

// void gyro()
// {
//     //// GYRO
//     // Wire.begin();
//     // Wire.beginTransmission(MPU_addr);
//     // Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
//     // Wire.endTransmission(false);
//     // Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
//     // AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
//     // AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
//     // AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
//     // // Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
//     // GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
//     // GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
//     // GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
//     // Serial.print("AcX = ");
//     // Serial.print(AcX);
//     // Serial.print(" | AcY = ");
//     // Serial.println(AcY);
//     // Serial.print(" | AcZ = ");
//     // Serial.print(AcZ);
//     // Serial.print(" | Tmp = ");
//     // Serial.print(Tmp / 340.00 + 36.53); //equation for temperature in degrees C from datasheet
//     // Serial.print(" | GyX = ");
//     // Serial.print(GyX);
//     // Serial.print(" | GyY = ");
//     // Serial.println(GyY);
//     // Serial.print(" | GyZ = ");
//     // Serial.println(GyZ);
//     // delay(333);
// }

// // void gpsCall()
// // {

// //     Serial.println("Searching GPS signal...");
// //     while (gpsSerial.available())
// //     {
// //         Serial.print("READ: " + gpsSerial.read()); // check for gps data
// //         if (gps.encode(gpsSerial.read()))          // encode gps data
// //         {
// //             gps.f_get_position(&lat, &lon); // get latitude and longitude
// //             // display position

// //             Serial.println("Position: ");
// //             Serial.print("Latitude:");
// //             Serial.print(lat, 6);
// //             Serial.print(";");
// //             Serial.print("Longitude:");
// //             Serial.println(lon, 6);

// //             Serial.print(lat);
// //             Serial.print(" ");
// //         }
// //         String latitude = String(lat, 6);
// //         String longitude = String(lon, 6);
// //         Serial.println(latitude + ";" + longitude);
// //         delay(1000);
// //     }
// //     delay(500);
// // }

// void switchRelayOn()
// {
//     digitalWrite(RELAY_PIN, HIGH);
// }

// void switchRelayOff()
// {
//     digitalWrite(RELAY_PIN, LOW);
// }

// int linear_hall()
// {
//     // LINEAR HALL
//     linearHallValue = analogRead(LH_MAGNETIC_AO_PIN);
//     Serial.println(linearHallValue, DEC);
//     return linearHallValue;
// }

void microphoneTest(char microphoneStr[5])
{
    // MICROPHONE SENSOR
    int microphoneValue = analogRead(BIG_SOUND_AO_PIN); // Read the value of the analog interface A0 assigned to digitalValue
    int StrLen = sprintf((char *)microphoneStr, "%d", microphoneValue);
    microphoneStr[StrLen] = '\0';
}