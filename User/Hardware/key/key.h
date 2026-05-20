#ifndef __KEY_H
#define __KEY_H

#include "stm32f1xx_hal.h"
#include "main.h"

/**
    添加新按键：在此文件注册按键、调用者
                在key.c注册 按键->引脚 映射
**/

/* =!=注册 按键*/
typedef enum{
    KEY_NEXT,
    KEY_CONFIRM,
    
    KEY_COUNT //计数位
} KeyTypeDef;


//typedef void (*KeyDownCallback)(KeyTypeDef);
typedef void (*KeyDownCallback)();


/* =!=注册调用者*/
typedef enum{
    KEY_KEYDOWN_ON_SCREEN_IDLE,
    KEY_KEYDOWN_ON_SCREEN_RUNNING,
    KEY_KEYDOWN_ON_APP_STATE_IDLE,
    KEY_KEYDOWN_ON_APP_STATE_RUNNING,
    
    KEY_CALLER_COUNT //计数位
} KeyCallerTypeDef;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

/*监听注册*/
void KEY_RegisterKeyListener(KeyTypeDef key,KeyCallerTypeDef caller,KeyDownCallback callbackFunc);

/*监听注销*/
void KEY_RevokeKeyListener(KeyTypeDef key,KeyCallerTypeDef caller);


#endif

