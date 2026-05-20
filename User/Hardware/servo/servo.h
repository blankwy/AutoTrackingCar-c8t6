#ifndef __SERVO_H
#define __SERVO_H

#include "tim.h"
#include "stm32f1xx_hal.h"


void Servo_Init();

void Servo_SetAngle(uint8_t angle);

#endif