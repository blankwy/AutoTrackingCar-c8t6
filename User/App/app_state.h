#ifndef __APP_STATE_H
#define __APP_STATE_H

typedef enum{
    SYS_INIT,
    SYS_IDLE,
    SYS_AUTO_TRACKING,
    SYS_ALARM,
    SYS_WORKOUT
} SystemStateTypeDef;

extern SystemStateTypeDef sys_state;

void StateMachine_Init(void);

void StateMachine_Run(void);

#endif