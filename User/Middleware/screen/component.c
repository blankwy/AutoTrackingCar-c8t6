/**  复用组件  **/
#include "component.h"

#include "screen.h"


BaseFont componentFont = {&font16x16, &afont12x6};

void LoadingBar(uint8_t id, uint8_t width, uint8_t height, uint8_t x, uint8_t y){
            uint8_t progress = 0;
            OLED_DrawRectangle(x,y,width ,height,OLED_COLOR_NORMAL);
            OLED_ShowFrame();
            HAL_Delay(20);
            while(progress<=100){
               OLED_DrawFilledRectangle(x,y,(progress/100.00) *width ,height,OLED_COLOR_NORMAL);
               //Screen_PrintFormat(1,&font16x16,OLED_COLOR_NORMAL,5,25,"%d -- %.2f",progress,(progress/100.00) *width);
               OLED_ShowFrame();
               progress+=20;
               HAL_Delay(20); 
            }
}


void TopBar(){
    OLED_DrawRectangle(1,1,FULL_WIDTH-2,20,OLED_COLOR_NORMAL);
    Screen_PrintFormat(2,1,componentFont,OLED_COLOR_NORMAL,5,3,"Menu");
    Screen_PrintFormat(3,1,componentFont,OLED_COLOR_NORMAL,FULL_WIDTH-38,3,"Mode %d",sys_state);
}

void ModeTab(uint8_t id, uint8_t is_selected, uint8_t page, char* name){
    OLED_ColorMode color = OLED_COLOR_NORMAL;
    OLED_DrawRectangle(10,30,50,25,color);
    if(is_selected){
        color = OLED_COLOR_REVERSED;
        OLED_DrawFilledRectangle(10,30,50,25,!color);
    }
    Screen_PrintFormat(6,0,componentFont,color,20,35,name);
    
}