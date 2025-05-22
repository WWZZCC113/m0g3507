#ifndef KEY_H
#define KEY_H

#include <stdint.h>
#include "ti/driverlib/dl_gpio.h"
#include "ti_msp_dl_config.h"

// 数据类型定义
typedef uint32_t u32;

// 按键状态结构体
typedef struct {
    uint8_t K1;     // 当前K1状态
    uint8_t K1L;    // 上一次K1状态
    uint8_t K2;     // 当前K2状态
    uint8_t K2L;    // 上一次K2状态
    uint8_t K3;     // 当前K3状态
    uint8_t K3L;    // 上一次K3状态
    uint8_t K4;     // 当前K4状态
    uint8_t K4L;    // 上一次K4状态
} Botton_State;

// 按键按下时间标志结构体
typedef struct {
    uint8_t K1;
    uint8_t K2;
    uint8_t K3;
    uint8_t K4;
} Botton_PushTimeFlag;

// 按键按下时间计数结构体
typedef struct {
    uint32_t K1;
    uint32_t K2;
    uint32_t K3;
    uint32_t K4;
} Botton_PushTime;

// 外部变量声明
extern Botton_State botton_State;
extern Botton_PushTimeFlag botton_PushTimeFlag;
extern Botton_PushTime botton_PushTime;
extern uint32_t uwTick;

// 函数声明
void Botton_Process(void);
void Botton_StateScan(void);

// GPIO端口和引脚定义（需要根据你的实际配置修改）
// 这些宏应该在ti_msp_dl_config.h中定义，如果没有请手动添加
/*
#define KEY_PORT            GPIOB
#define KEY_PIN_21_PIN      DL_GPIO_PIN_21

// 如果你有其他按键，请取消注释并修改相应的引脚
// #define KEY_PIN_K2          DL_GPIO_PIN_XX
// #define KEY_PIN_K3          DL_GPIO_PIN_XX
// #define KEY_PIN_K4          DL_GPIO_PIN_XX

#define LED1_PORT           GPIOB
#define LED1_PIN_22_PIN     DL_GPIO_PIN_22
*/

#endif // KEY_H