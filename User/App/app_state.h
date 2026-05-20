#ifndef __APP_STATE_H
#define __APP_STATE_H

#include "main.h"
#include "key.h"
#include "screen.h"

typedef enum{
    SYS_INIT,
    SYS_IDLE,
    SYS_AUTO_TRACKING,
    SYS_AUTO_AVOIDING,
    SYS_ALARM,
    SYS_WORKOUT
} SystemStateTypeDef;

extern SystemStateTypeDef sys_state;

void SwitchCursorAtMode(void);

void ConfirmModeSwitch(void);

void ExitMode(void);

void StateMachine_Init(void);

void StateMachine_Run(void);

#endif