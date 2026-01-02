#include <Arduino.h>
#include <STM32FreeRTOS.h> 
#include "MPU6050.h"
#include "filters.h"
#include "servo_driver.h"

// --- BIẾN TOÀN CỤC ---
// Biến dùng chung để Task Cảm biến ghi vào và Task Servo đọc ra
#include "filters.h"

// Chỉ cần khai báo thế này là đủ
Attitude myAngle;
// Giá trị lệch đo được khi để mặt phẳng nằm ngang
float offsetPitch = -1.85; 
float offsetRoll = -1.05;

// --- KHAI BÁO CÁC TASK (Dựa theo Spec Nhóm 9) ---
void Task_Sensor_Filter(void *pvParameters); // Tương ứng T1 & T2
void Task_Servo_Control(void *pvParameters); // Tương ứng T3

void setup() {
    // 1. Khởi tạo giao tiếp máy tính
    Serial.begin(115200);
    
    // 2. Khởi tạo phần cứng (Các hàm trong file .cpp của bạn)
    MPU6050_Init();
    Servo_Init();

    // 3. Tạo các Task trong hệ điều hành
    // Task cảm biến: Ưu tiên 1 (Cao nhất), Bộ nhớ 128 words
    xTaskCreate(Task_Sensor_Filter, "Sensor", 128, NULL, 1, NULL);

    // Task Servo: Ưu tiên 3 (Thấp hơn), Bộ nhớ 128 words
    xTaskCreate(Task_Servo_Control, "Servo", 128, NULL, 3, NULL);

    // 4. Lệnh bắt đầu điều phối các Task
    vTaskStartScheduler();
}

void loop() {
   
}

// --- ĐỊNH NGHĨA CHI TIẾT CÁC TASK ---

/**
 * Task T1 & T2: Đọc dữ liệu MPU6050 và chạy bộ lọc
 * Tần số yêu cầu: 100Hz (10ms)
 */
void Task_Sensor_Filter(void *pvParameters) {
    for (;;) {
        // 1. Đọc và lọc dữ liệu
        MPU6050_RawData raw = MPU6050_Read_Raw(); 
        Filter_Update(raw, myAngle, 0.01f); 

        // 2. Tính toán giá trị đã hiệu chuẩn
        float calibP = myAngle.pitch - offsetPitch;
        float calibR = myAngle.roll - offsetRoll;

        // 3. In log trên cùng một dòng
        Serial.print("P_calib: "); 
        Serial.print(calibP);        // In Pitch hiệu chuẩn
        Serial.print(" | R_calib: "); 
        Serial.println(calibR);      // In Roll hiệu chuẩn và xuống dòng

        // Đảm bảo tần số 100Hz (10ms) theo Spec
        vTaskDelay(pdMS_TO_TICKS(10)); 
    }
}

/**
 * Task T3: Xuất xung PWM điều khiển Servo MG946R
 * Tần số: 50Hz (20ms)
 */
void Task_Servo_Control(void *pvParameters) {
    (void) pvParameters;

    for (;;) {
        // Lấy dữ liệu góc từ biến chung myAngle để điều khiển 2 Servo
        Servo_WriteAngles(myAngle.pitch, myAngle.roll);

        // Nghỉ 20ms giữa mỗi lần cập nhật góc Servo
        vTaskDelay(pdMS_TO_TICKS(20)); 
    }
}