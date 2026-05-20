#ifndef __SCREEN_H
#define __SCREEN_H

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "oled.h"

#include "key.h"

#include "component.h"

#define FULL_WIDTH 128

typedef enum{
    UI_LOADING,
    UI_MAIN,
    UI_RUNNING,
    UI_WORKOUT
} ScreenStateTypeDef;

typedef enum{
    MAIN_AUTO_TRACKING,
    MAIN_AUTO_AVOIDING,
    
    MAIN_CURSOR_COUNT //计数位
} CursorAt;

//typedef struct{
//    const ChineseCell_t cnfont[];
//    const uint8_t asciiFont[];
//} BaseFont;


static uint8_t selected_id;

void Screen_Init(void);

void Screen_PrintFormat(uint8_t id, const uint8_t font, 
    uint8_t x, uint8_t y, char* format_str, ...);


void Screen_PageTo(ScreenStateTypeDef page);

void Screen_Main_CursorTo(CursorAt item);

void Screen_Reset(void);

void Screen_Fresh(void);

/*=====按键交互函数声明=*/
void KEY_NEXT_Handler();
void KEY_CONFIRM_Handler();
/*=按键交互函数声明=====*/

static void Screen_Cursor_Init();


#endif