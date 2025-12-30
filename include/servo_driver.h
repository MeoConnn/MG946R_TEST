#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include <Arduino.h>
#include <Servo.h>

// Định nghĩa các chân điều khiển Servo trên STM32F411
#define SERVO_PITCH_PIN PA0
#define SERVO_ROLL_PIN  PA1

void Servo_Init();
void Servo_WriteAngles(float pitchAngle, float rollAngle);

#endif