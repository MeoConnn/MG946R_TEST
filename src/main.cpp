#include <Arduino.h>
#include "mpu6050.h"      // Mảnh 1
#include "filters.h"      // Mảnh 2
#include "servo_driver.h" // Mảnh 3

Attitute myAngle = {0, 0};
unsigned long lastTime;

void setup() {
    Serial.begin(115200);
    
    MPU6050_Init();   // Khởi tạo cảm biến
    Servo_Init();     // Khởi tạo Servo
    
    lastTime = millis();
}

void loop() {
    unsigned long currentTime = millis();
    float dt = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;

    // 1. Đọc dữ liệu
    MPU6050_RawData raw = MPU6050_Read_Raw();

    // 2. Lọc dữ liệu lấy góc mượt
    Filter_Update(raw, myAngle, dt);

    // 3. Điều khiển Servo phản ứng theo góc nghiêng
    Servo_WriteAngles(myAngle.pitch, myAngle.roll);

    // In kiểm tra
    Serial.print("P:"); Serial.print(myAngle.pitch);
    Serial.print(" | R:"); Serial.println(myAngle.roll);

    delay(10);
}