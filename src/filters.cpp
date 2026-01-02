#include "filters.h"   
#include "MPU6050.h"   
#include <math.h>      

void Filter_Update(MPU6050_RawData raw, Attitude &angle, float dt) {
    float alpha = 0.98;
    
    // Tính toán góc từ gia tốc (Sử dụng tên biến ax, ay, az từ MPU6050.h)
    float accelPitch = atan2((float)raw.ay, (float)raw.az) * 180 / M_PI;
    float accelRoll = atan2(-(float)raw.ax, sqrt((float)raw.ay * raw.ay + (float)raw.az * raw.az)) * 180 / M_PI;

    // Chuyển đổi vận tốc góc (Sử dụng gx, gy từ MPU6050.h)
    float gyroPitchRate = raw.gx / 131.0;
    float gyroRollRate = raw.gy / 131.0;

    // Bộ lọc bù (Complementary Filter) để giữ thăng bằng
    angle.pitch = alpha * (angle.pitch + gyroPitchRate * dt) + (1 - alpha) * accelPitch;
    angle.roll = alpha * (angle.roll + gyroRollRate * dt) + (1 - alpha) * accelRoll;
}