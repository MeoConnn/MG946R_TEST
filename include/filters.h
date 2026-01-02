#ifndef FILTERS_H
#define FILTERS_H

#include "MPU6050.h"

struct Attitude {
    float pitch;
    float roll;
};

void Filter_Update(MPU6050_RawData raw, Attitude &angle, float dt);

#endif