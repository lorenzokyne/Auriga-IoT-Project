#ifndef SENSOR_H
#define SENSOR_H
#include "Sensor.h"
#endif
#include "Arduino.h"
#include <Wire.h>

class Gyroscope : Sensor
{
private:
    const int MPU_addr = 0x68; // I2C address of the MPU-6050
    char *accelerometerValue;

public:
    Gyroscope(int pin) : Sensor("atm/gyro/value", pin){};
    const char *accelerometerTopic = "atm/gyro/acc";
    
    void measureValue()
    {
        int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
        Wire.begin();
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
        AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
        AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
        AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
        // Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
        GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
        GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
        GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
        int StrLen = sprintf((char *)this->value, "%s%d %s%d %s%d", "GyX = ", GyX, "GyY = ", GyY, "GyZ = ", GyZ);
        this->value[StrLen] = '\0';
        StrLen = sprintf((char *)this->accelerometerValue, "%s%d %s%d %s%d", "AcX = ", AcX, "AcY = ", AcY, "AcZ = ", AcZ);
        this->accelerometerValue[StrLen] = '\0';
        delay(333);
        int brightnessAnalogValue = analogRead(this->pin);
        int StrLen = sprintf((char *)this->value, "%d", brightnessAnalogValue);
        this->value[StrLen] = '\0';
    }

    char *getValue()
    {
        return this->value;
    }

    char *getTopic()
    {
        return this->topic;
    }

    char *getAccelerometerValue()
    {
        return this->value;
    }
};