#include "screen.h"

#include "app_state.h"


#include <string.h>

static CursorAt cursor_item = MAIN_AUTO_TRACKING;

static uint8_t is_running = 0;

void Screen_PrintFormat(uint8_t id, const uint8_t font, 
    uint8_t x, uint8_t y, char* format_str, ...){
        char data[255];
        va_list args;
        va_start(args,format_str);
        vsnprintf(data,sizeof(data),format_str,args);
        va_end(args);
        OLED_Printf(x,y,font,data);
}

void Screen_Init(){
    HAL_Delay(20);
    OLED_Init();
    Screen_Reset();
    Screen_PrintFormat(0,OLED_6X8,5,5,"Initial loading...");
    Screen_PrintFormat(1,OLED_6X8,5,20,"OLED_Init Completed!");
    Screen_Fresh();
}



void Screen_PageTo(ScreenStateTypeDef page){
    switch(page){
        case UI_LOADING:
            //Screen_Reset();
            LoadingBar(0,120,5,5,50);
            Screen_Fresh();
            break;
        case UI_MAIN:
            is_running = 0;
            Screen_Reset();
            TopBar();
            Screen_Cursor_Init();
            Screen_Main_CursorTo(cursor_item);
            Screen_Fresh();
            break;
        case UI_RUNNING:
            is_running = 1;
            Screen_Reset();
            TopBar();
            StopIcon();
            Screen_Cursor_Init();
            Screen_Main_CursorTo(cursor_item);
            Screen_Fresh();
            break;
        case UI_WORKOUT:
            is_running = 0;
            Screen_Reset();
            TopBar();
            Screen_PrintFormat(1,OLED_8X16,5,25,"完成");
            Screen_Fresh();
            break;
    }
}

void Screen_Main_CursorTo(CursorAt item){
    OLED_ClearArea(5,25,80,25);
    cursor_item = item;
    switch(cursor_item){
                
                case MAIN_AUTO_TRACKING:
                    ModeTab(5,is_running,UI_MAIN+is_running,"自动循迹");
                    break;
                case MAIN_AUTO_AVOIDING:
                    ModeTab(5,is_running,UI_MAIN+is_running,"自动避障");
                    break;
                case MAIN_CURSOR_COUNT:
                    break;
            }
}

/*注册按键光标交互监听*/
void Screen_Cursor_Init(){
    KEY_RevokeKeyListener(KEY_NEXT,KEY_KEYDOWN_ON_SCREEN_RUNNING);
    KEY_RevokeKeyListener(KEY_CONFIRM,KEY_KEYDOWN_ON_SCREEN_RUNNING);
    KEY_RegisterKeyListener(KEY_NEXT,KEY_KEYDOWN_ON_SCREEN_IDLE,KEY_NEXT_Handler);
    KEY_RegisterKeyListener(KEY_CONFIRM,KEY_KEYDOWN_ON_SCREEN_IDLE,KEY_CONFIRM_Handler);
            
    
}

void KEY_NEXT_Handler(){
    Screen_Main_CursorTo((cursor_item+1)%MAIN_CURSOR_COUNT);
    //Screen_PrintFormat(7,OLED_8X16,60,40,"CURSOR=%d",(cursor_item+1)%MAIN_CURSOR_COUNT);
    Screen_Fresh();
}

void KEY_CONFIRM_Handler(){
    char* msg = "Start";
    if(is_running){
        msg="Complete!";
    }
    Screen_PrintFormat(7,OLED_8X16,70,50,"Start");
    Screen_Fresh();
}

void Screen_Fresh(){
    OLED_Update();
}

void Screen_Reset(){
    OLED_Clear();
}


