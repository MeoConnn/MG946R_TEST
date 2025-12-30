#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>
#include <Wire.h>

#define MPU6050_ADDR 0x68

struct MPU6050_RawData {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
};

void MPU6050_Init();
MPU6050_RawData MPU6050_Read_Raw();

#endif