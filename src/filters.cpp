#include "filters.h"

// Hệ số lọc (càng gần 1 thì càng mượt nhưng càng chậm)
const float alpha = 0.96; 

void Filter_Update(MPU6050_RawData raw, Attitute &angle, float dt) {
    // 1. Tính góc từ Gia tốc kế (Accelerometer)
    // Công thức: atan2 tính góc dựa trên trọng lực
    float accelPitch = atan2(raw.ay, sqrt(pow(raw.ax, 2) + pow(raw.az, 2))) * 180 / PI;
    float accelRoll = atan2(-raw.ax, sqrt(pow(raw.ay, 2) + pow(raw.az, 2))) * 180 / PI;

    // 2. Chuyển đổi vận tốc góc từ Gyro (đơn vị thô sang độ/giây)
    // Với dải đo mặc định +/- 250 deg/s, hệ số chia là 131
    float gyroPitchRate = raw.gx / 131.0;
    float gyroRollRate = raw.gy / 131.0;

    // 3. Công thức Bộ lọc bù
    // Góc mới = alpha * (Góc cũ + Vận tốc góc * thời gian) + (1 - alpha) * (Góc gia tốc)
    angle.pitch = alpha * (angle.pitch + gyroPitchRate * dt) + (1 - alpha) * accelPitch;
    angle.roll = alpha * (angle.roll + gyroRollRate * dt) + (1 - alpha) * accelRoll;
}