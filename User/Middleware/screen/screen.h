#ifndef __SCREEN_H
#define __SCREEN_H

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "oled.h"

#include "component.h"

#define FULL_WIDTH 128

typedef enum{
    UI_LOADING=0,
    UI_MAIN=1,
    UI_WORKOUT=2
} ScreenStateTypeDef;

typedef struct{
    const Font *font;
    const ASCIIFont *asciiFont;
} BaseFont;


static uint8_t selected_id;

void Screen_Init(void);

void Screen_PrintFormat(uint8_t id, uint8_t ascii_only, const BaseFont font, OLED_ColorMode color, 
    uint8_t x, uint8_t y, char* format_str, ...);




void Screen_PageTo(ScreenStateTypeDef page);


void Screen_Reset(void);

void Screen_Fresh(void);

#endif