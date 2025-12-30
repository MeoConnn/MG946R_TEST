#include "mpu6050.h"

void MPU6050_Init() {
    Wire.begin(); 
    Wire.setClock(400000); // Tốc độ I2C nhanh theo yêu cầu
    
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x6B); // Thanh ghi quản lý nguồn
    Wire.write(0);    // Đánh thức cảm biến
    Wire.endTransmission(true);
}

MPU6050_RawData MPU6050_Read_Raw() {
    MPU6050_RawData data;
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x3B); // Đọc từ thanh ghi gia tốc X
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDR, 14, true);

    data.ax = (Wire.read() << 8) | Wire.read();
    data.ay = (Wire.read() << 8) | Wire.read();
    data.az = (Wire.read() << 8) | Wire.read();
    Wire.read(); Wire.read(); // Bỏ qua nhiệt độ
    data.gx = (Wire.read() << 8) | Wire.read();
    data.gy = (Wire.read() << 8) | Wire.read();
    data.gz = (Wire.read() << 8) | Wire.read();
    return data;
}