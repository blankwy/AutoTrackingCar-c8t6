#ifndef __SCREEN_COMPONENT_H
#define __SCREEN_COMPONENT_H

#include "app_state.h"

#include "oled.h"

#include <stdint.h>

void LoadingBar(uint8_t id, uint8_t width, uint8_t height, uint8_t x, uint8_t y);

void TopBar(void);

void ModeTab(uint8_t id, uint8_t is_selected, uint8_t page, char* name);

void StopIcon(void);

#endif