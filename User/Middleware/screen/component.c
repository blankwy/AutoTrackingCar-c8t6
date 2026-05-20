/**  复用组件  **/
#include "component.h"

#include "screen.h"



void LoadingBar(uint8_t id, uint8_t width, uint8_t height, uint8_t x, uint8_t y){
            uint8_t progress = 0;
            OLED_DrawRectangle(x,y,width ,height,0);
            OLED_Update();
            HAL_Delay(20);
            while(progress<=100){
               OLED_DrawRectangle(x,y,(progress/100.00) *width ,height,1);
               //Screen_PrintFormat(1,&font16x16,OLED_COLOR_NORMAL,5,25,"%d -- %.2f",progress,(progress/100.00) *width);
               OLED_Update();
               progress+=20;
               HAL_Delay(20);
            }
}


void TopBar(){
    OLED_DrawRectangle(1,1,FULL_WIDTH-2,20,0);
    Screen_PrintFormat(2,OLED_6X8,5,3,"Menu");
    Screen_PrintFormat(3,OLED_6X8,FULL_WIDTH-38,3,"Mode %d",sys_state);
}

void ModeTab(uint8_t id, uint8_t is_selected, uint8_t page, char* name){
    uint8_t color = 0;
    OLED_DrawRectangle(10,30,80,25,color);
    if(is_selected){
        color = 1;
        OLED_DrawRectangle(10,30,80,25,color);
    }
    Screen_PrintFormat(6,OLED_8X16,20,35,name);
    
}

void StopIcon(){
    OLED_DrawRectangle(100,35,5,30,0);
    OLED_DrawRectangle(110,35,5,30,0);
}