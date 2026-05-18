#include "app_state.h"

#include "screen.h"

SystemStateTypeDef sys_state = SYS_INIT;

void StateMachine_Init(){

    Screen_Init();
    Screen_PageTo(UI_LOADING);
    
    sys_state = SYS_IDLE;
}

void StateMachine_Run(){
    
    switch(sys_state){
        /*³õÊ¼»¯*/
        case SYS_INIT:
            StateMachine_Init();
            break;
        /*¿ÕÏÐ×´Ì¬*/
        case SYS_IDLE:
            Screen_PageTo(UI_MAIN);
            break;
        /*×Ô¶¯Ñ­¼£*/
        case SYS_AUTO_TRACKING:
            
            break;
        /*¸æ¾¯×´Ì¬*/
        case SYS_ALARM:
            
            break;
        /*Íê³É×´Ì¬*/
        case SYS_WORKOUT:
            
            sys_state = SYS_IDLE;
            break;
    }
    
}