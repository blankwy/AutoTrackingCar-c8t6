#include "screen.h"

#include "app_state.h"

#include <string.h>


BaseFont mainFont = {&font16x16, &afont12x6};


void Screen_PrintFormat(uint8_t id, uint8_t ascii_only, const BaseFont font, OLED_ColorMode color,
    uint8_t x, uint8_t y, char* format_str, ...){
        char data[255];
        va_list args;
        va_start(args,format_str);
        vsnprintf(data,sizeof(data),format_str,args);
        va_end(args);
        if(ascii_only){
            OLED_PrintASCIIString(x,y,data,font.asciiFont,color);
        }else{
            OLED_PrintString(x,y,data,font.font,color);
        }
}

void Screen_Init(){
    HAL_Delay(20);
    OLED_Init();
    OLED_NewFrame();
    OLED_PrintASCIIString(5,5,"Loading...",&afont12x6,OLED_COLOR_NORMAL);
    OLED_PrintASCIIString(5,20,"OLED_Init Completed!",&afont8x6,OLED_COLOR_NORMAL);
    OLED_ShowFrame();
}



void Screen_PageTo(ScreenStateTypeDef page){
    switch(page){
        case UI_LOADING:
            LoadingBar(0,120,10,5,50);
            break;
        case UI_MAIN:
            OLED_NewFrame();
            Screen_PrintFormat(7,0,mainFont,OLED_COLOR_NORMAL,60,20,"eee");
            ModeTab(5,0,UI_MAIN,"自动循迹");
            TopBar();
            Screen_Fresh();
            break;
        case UI_WORKOUT:
            break;
    }
}

void Screen_Fresh(){
    OLED_ShowFrame();
}

void Screen_Reset(){
    OLED_NewFrame();
}


