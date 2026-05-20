# AutoTrackCar — Agent Guide

STM32F103C8T6 black-line tracking car. CubeMX-generated HAL + Keil MDK-ARM.

## Project Anatomy

```
AutoTrackCar.ioc          ← CubeMX config (regenerate via CubeMX, not hand-edit)
Core/Inc/  Core/Src/      ← CubeMX-generated HAL code (gpio, i2c, tim, dma, it, msp, main)
Drivers/                  ← STM32F1 HAL + CMSIS (CubeMX-managed, read-only)
MDK-ARM/                  ← Keil uVision project + build artifacts
User/App/                 ← app_state.c/h — state machine (the main loop dispatcher)
User/Hardware/key/        ← Button driver — callback-based event system via EXTI
User/Hardware/oled/       ← 128x64 I2C OLED driver (framebuffer-based, GB2312 charset)
User/Middleware/screen/   ← Page-based UI layer (screen.c) + reusable components (component.c)
```

**Empty directories** (placeholders for future code): `motor/`, `pid/`, `servo/`, `usart/`, `Middleware/c/`, `debug/`

## Key Architecture Facts

### Main Loop
`main()` → `HAL_Init()` → `SystemClock_Config()` → `MX_*_Init()` → `while(1) { StateMachine_Run(); }`

### State Machine
States: `SYS_INIT` → `SYS_IDLE` → `SYS_AUTO_TRACKING` / `SYS_AUTO_AVOIDING` → `SYS_WORKOUT` → back to `SYS_IDLE`.  
`SYS_ALARM` defined in enum but not implemented.  
`StateMachine_Run()` runs every loop iteration — it's NOT event-driven.

### Key / Event System
Buttons (PA11=CONFIRM, PA12=NEXT, EXTI falling, pull-up) fire `HAL_GPIO_EXTI_Callback()` which fans out to a static 2D callback table: `key_events[KeyTypeDef][KeyCallerTypeDef]`.

Four "caller layers": `SCREEN_IDLE`, `SCREEN_RUNNING`, `APP_STATE_IDLE`, `APP_STATE_RUNNING` — each context registers/unregisters its own handlers.  
Always match `KEY_RegisterKeyListener` / `KEY_RevokeKeyListener` pairs when entering/leaving a state.

### OLED Display
- 128x64, I2C2 (PB10=SCL, PB11=SDA), address `0x78`, 400kHz Fast Mode
- **Double-buffered**: draw to `OLED_DisplayBuf[1024]`, then call `OLED_Update()` to flush
- I2C mode configurable via `#define` in `oled.h`: `IIC_Mode_Blocking` (default), `IIC_Mode_IT`, or `IIC_Mode_DMA`
- Chinese (GB2312) charset enabled — *not* UTF-8
- Interrupt handler for IT/DMA mode: `OLED_IIC_ISR(&hi2c2)` called from `HAL_I2C_MasterTxCpltCallback`

### PWM / Servo
- TIM3 CH1 on PA6, 50Hz PWM (prescaler 720-1, period 2000-1 at 72MHz → 100kHz timer → 50Hz)
- Default pulse: 150 (out of 2000)

### CubeMX Regeneration Rules
- **NEVER edit CubeMX-generated files outside `USER CODE BEGIN/END` markers**. Regeneration preserves only code inside these markers.
- Peripheral init functions (`MX_GPIO_Init`, `MX_I2C2_Init`, `MX_TIM3_Init`, `MX_DMA_Init`) are regenerated — add callbacks and post-init in the USER CODE sections.
- `Core/Inc/main.h` defines button pin macros (`CONFIRM_BTN_Pin`, `NEXT_BTN_Pin`) — reference these, not raw pins.

## Build & Debug

**Toolchain**: Keil MDK-ARM v5.32 (`.uvprojx` project in `MDK-ARM/`)

| Action | Command |
|---|---|
| Build all | Open `MDK-ARM/AutoTrackCar.uvprojx` in uVision → Build (F7) |
| Flash | uVision → Load (F8) |
| OpenCode build | `skill(name="build-keil")` |
| OpenCode flash | `skill(name="flash-keil")` |
| OpenCode HAL guidance | `skill(name="stm32-hal-development")` |

**Build artifacts** (.o, .d, .axf, .hex, .map) are committed to git — no `.gitignore` exists.

## Hardware Config (72MHz System Clock)

- HSE 8MHz → PLL x9 → 72MHz SYSCLK
- APB1: 36MHz (÷2), APB2: 72MHz (÷1)
- DMA1 Ch4 for I2C2 TX
- Interrupts: EXTI15_10 (buttons, preempt 0), I2C2_EV/ER (preempt 0), DMA1_Ch4 (preempt 0)
- Stack: 0x400 (1KB), Heap: 0x200 (512B) — defined in startup file

## Style & Conventions

- Hardware drivers in `User/Hardware/<component>/` with `<component>.c` + `<component>.h`
- Middleware in `User/Middleware/` — screen module provides page-based UI abstraction over OLED
- App logic in `User/App/` — currently only `app_state.c/h`
- All user code goes inside `/* USER CODE BEGIN/END */` sections in Core/ files
- GB2312 encoding for Chinese strings — set `--no-multibyte-chars` in Keil MCB155 to compile
- OLED font sizes: `OLED_8X16` and `OLED_6X8`
