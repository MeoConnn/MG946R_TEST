#ifndef FILTERS_H
#define FILTERS_H

#include <Arduino.h>
#include "mpu6050.h"

// Cấu trúc chứa góc đã lọc
struct Attitute {
    float pitch;
    float roll;
};

// Khai báo hàm xử lý bộ lọc
void Filter_Update(MPU6050_RawData raw, Attitute &angle, float dt);

#endif