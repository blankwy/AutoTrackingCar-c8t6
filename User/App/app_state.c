#include "app_state.h"


SystemStateTypeDef sys_state = SYS_INIT;

CursorAt selectMode = MAIN_AUTO_TRACKING;

SystemStateTypeDef cursor_sys_state_map[MAIN_CURSOR_COUNT]={
    SYS_AUTO_TRACKING,
    SYS_AUTO_AVOIDING
};

void StateMachine_Init(){

    Screen_Init();
    Screen_PageTo(UI_LOADING);
    sys_state = SYS_IDLE;
}

void StateMachine_Run(){
    Screen_Reset();
    switch(sys_state){
        /*初始化*/
        case SYS_INIT:
            StateMachine_Init();
            break;
        /*空闲状态*/
        case SYS_IDLE:
            Screen_PageTo(UI_MAIN);
            KEY_RevokeKeyListener(KEY_NEXT,KEY_KEYDOWN_ON_APP_STATE_RUNNING);
            KEY_RevokeKeyListener(KEY_CONFIRM,KEY_KEYDOWN_ON_APP_STATE_RUNNING);
            KEY_RegisterKeyListener(KEY_NEXT,KEY_KEYDOWN_ON_APP_STATE_IDLE,SwitchCursorAtMode);
            KEY_RegisterKeyListener(KEY_CONFIRM,KEY_KEYDOWN_ON_APP_STATE_IDLE,ConfirmModeSwitch);
            break;
        /*自动循迹*/
        case SYS_AUTO_TRACKING:
            Screen_PageTo(UI_RUNNING);
            KEY_RevokeKeyListener(KEY_CONFIRM,KEY_KEYDOWN_ON_APP_STATE_IDLE);
            KEY_RegisterKeyListener(KEY_CONFIRM,KEY_KEYDOWN_ON_APP_STATE_RUNNING,ExitMode);
            //
        
            break;
        /*自动避障*/
        case SYS_AUTO_AVOIDING:
            Screen_PageTo(UI_RUNNING);
            KEY_RevokeKeyListener(KEY_CONFIRM,KEY_KEYDOWN_ON_APP_STATE_IDLE);
            KEY_RegisterKeyListener(KEY_CONFIRM,KEY_KEYDOWN_ON_APP_STATE_RUNNING,ExitMode);
            //
        
            break;
        /*告警状态*/
        case SYS_ALARM:
            
            break;
        /*完成状态*/
        case SYS_WORKOUT:
            Screen_PageTo(UI_WORKOUT);
            HAL_Delay(1000);
            sys_state = SYS_IDLE;
            break;
    }
    
}

void SwitchCursorAtMode(){
    selectMode = (selectMode+1)%MAIN_CURSOR_COUNT;
}

void ConfirmModeSwitch(){
    
    sys_state = cursor_sys_state_map[selectMode];
    
}

void ExitMode(){
    sys_state = SYS_WORKOUT;
}