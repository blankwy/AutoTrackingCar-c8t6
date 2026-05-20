#include "key.h"

static KeyDownCallback key_events[KEY_COUNT][KEY_CALLER_COUNT]; 

/* =!= 添加 按键->引脚地址 映射*/
static uint16_t key_Pin_Map[KEY_COUNT] = {
    NEXT_BTN_Pin,
    CONFIRM_BTN_Pin
};



/*配置按键事件*/
void KEY_RegisterKeyListener(KeyTypeDef key,KeyCallerTypeDef caller,KeyDownCallback callbackFunc){
    key_events[key][caller] = callbackFunc;
}

/*注销按键事件*/
void KEY_RevokeKeyListener(KeyTypeDef key,KeyCallerTypeDef caller){
    key_events[key][caller] = NULL;
}


/*中断回调匹配*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    
        for(int key_i=0;key_i<KEY_COUNT;key_i++){
            if(GPIO_Pin==key_Pin_Map[key_i]){
                for(int caller_i=0;caller_i<KEY_CALLER_COUNT;caller_i++){
                    if(key_events[key_i][caller_i] != NULL){
                        key_events[key_i][caller_i]();
                    }
                    
                }
            }
        }
    
}

