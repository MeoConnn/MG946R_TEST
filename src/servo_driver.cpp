#include "servo_driver.h"

Servo servoPitch;
Servo servoRoll;

void Servo_Init() {
    servoPitch.attach(SERVO_PITCH_PIN);
    servoRoll.attach(SERVO_ROLL_PIN);
    
    // Đưa về vị trí cân bằng ban đầu (90 độ)
    servoPitch.write(90);
    servoRoll.write(90);
}

void Servo_WriteAngles(float pitchAngle, float rollAngle) {
    // Chuyển đổi từ góc nghiêng (-45 đến 45) sang góc Servo (45 đến 135)
    // Giả sử 0 độ của cảm biến tương ứng với 90 độ của Servo
    int s1_pos = constrain(90 + (int)pitchAngle, 0, 180);
    int s2_pos = constrain(90 + (int)rollAngle, 0, 180);
    
    servoPitch.write(s1_pos);
    servoRoll.write(s2_pos);
}