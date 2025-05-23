#include "key.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti_msp_dl_config.h"
#include "empty.h"

#define Long_Time  700
#define Short_Time 150
#define Press 0   

// 全局变量定义
Botton_State botton_State = {0};
Botton_PushTimeFlag botton_PushTimeFlag = {0};
Botton_PushTime botton_PushTime = {0};

// 静态变量用于控制函数调用频率
static uint32_t Last_Process_Tick = 0;

void Botton_Process(void);
void Botton_StateScan(void);

// 按键状态扫描函数 - 读取所有按键的当前状态
void Botton_StateScan(void)
{
    uint32_t pinState;
    
    // 读取K1状态 (假设K1连接到GPIOB的某个引脚)
    pinState = DL_GPIO_readPins(KEY_PORT, KEY_PIN_21_PIN);
     botton_State.K1 = (pinState & KEY_PIN_21_PIN) ? 1 : 0;
    // 如果你的按键按下时是高电平，使用下面这行代替上面的
    // botton_State.K1 = (pinState & KEY_PIN_21_PIN) ? 0 : 1;
    
    // 读取K2状态(需要根据实际引脚配置修改)
    // pinState = DL_GPIO_readPins(KEY_PORT, KEY_PIN_K2);
    // botton_State.K2 = (pinState & KEY_PIN_K2) ? 0 : 1;
    
    // 读取K3状态
    // pinState = DL_GPIO_readPins(KEY_PORT, KEY_PIN_K3);
    // botton_State.K3 = (pinState & KEY_PIN_K3) ? 0 : 1;
    
    // 读取K4状态
    // pinState = DL_GPIO_readPins(KEY_PORT, KEY_PIN_K4);
    // botton_State.K4 = (pinState & KEY_PIN_K4) ? 0 : 1;
}

// 按键处理主函数
void Botton_Process(void)
{
    // 限制函数调用频率为100ms
    if(uwTick - Last_Process_Tick < 100)
    {
        return;
    }
    Last_Process_Tick = uwTick;

    // 首先扫描所有按键状态
    Botton_StateScan();

    //////////////////////////////////////////////////////////////////
    // K1按键处理
    if(botton_State.K1 == Press && botton_State.K1L == Press) // 按键按下
    {
        botton_PushTimeFlag.K1 = 1;
    }

    if(botton_State.K1 != Press && botton_State.K1L != Press) // 按键松开
    {
        if(botton_PushTime.K1 > Long_Time)
        {
            // 长按操作 - LED输出低电平
            DL_GPIO_clearPins(LED1_PORT, LED1_PIN_22_PIN);
        }
        else if(botton_PushTime.K1 > Short_Time)
        {
            // 短按操作 - LED输出高电平
            DL_GPIO_setPins(LED1_PORT, LED1_PIN_22_PIN);
        }
        botton_PushTimeFlag.K1 = 0;
        botton_PushTime.K1 = 0;
    }

    //////////////////////////////////////////////////////////////////
    // // K2按键处理
    // if(botton_State.K2 == Press && botton_State.K2L == Press) // 按键按下
    // {
    //     botton_PushTimeFlag.K2 = 1;
    // }

    // if(botton_State.K2 != Press && botton_State.K2L != Press) // 按键松开
    // {
    //     if(botton_PushTime.K2 > Long_Time)
    //     {
    //         // K2长按操作 - 在这里添加你的代码
    //     }
    //     else if(botton_PushTime.K2 > Short_Time)
    //     {
    //         // K2短按操作 - 在这里添加你的代码
    //     }
        
    //     botton_PushTimeFlag.K2 = 0;
    //     botton_PushTime.K2 = 0;
    // }

    // //////////////////////////////////////////////////////////////////
    // // K3按键处理
    // if(botton_State.K3 == Press && botton_State.K3L == Press) // 按键按下
    // {
    //     botton_PushTimeFlag.K3 = 1;
    // }

    // if(botton_State.K3 != Press && botton_State.K3L != Press) // 按键松开
    // {
    //     if(botton_PushTime.K3 > Long_Time)
    //     {
    //         // K3长按操作 - 在这里添加你的代码
    //     }
    //     else if(botton_PushTime.K3 > Short_Time)
    //     {
    //         // K3短按操作 - 在这里添加你的代码
    //     }
        
    //     botton_PushTimeFlag.K3 = 0;
    //     botton_PushTime.K3 = 0;
    // }

    // //////////////////////////////////////////////////////////////////
    // // K4按键处理
    // if(botton_State.K4 == Press && botton_State.K4L == Press) // 按键按下
    // {
    //     botton_PushTimeFlag.K4 = 1;
    // }

    // if(botton_State.K4 != Press && botton_State.K4L != Press) // 按键松开
    // {
    //     if(botton_PushTime.K4 > Long_Time)
    //     {
    //         // K4长按操作 - 在这里添加你的代码
    //     }
    //     else if(botton_PushTime.K4 > Short_Time)
    //     {
    //         // K4短按操作 - 在这里添加你的代码
    //     }
        
    //     botton_PushTimeFlag.K4 = 0;
    //     botton_PushTime.K4 = 0;
    // }

    //////////////////////////////////////////////////////////////////
    // 保存当前状态作为上一次状态
    botton_State.K1L = botton_State.K1;
    botton_State.K2L = botton_State.K2;
    botton_State.K3L = botton_State.K3;
    botton_State.K4L = botton_State.K4;
}

    // 清除定时器中断标志
    // NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);

    // 使能定时器中断
    // NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);

// // 定时器的中断服务函数 已配置为1ms的周期   人工uwTick + 按键计时
// void TIMER_0_INST_IRQHandler(void)
// {
//     // 如果产生了定时器中断
//     switch( DL_TimerG_getPendingInterrupt(TIMER_0_INST) )
//     {
//         case DL_TIMER_IIDX_ZERO:  // 如果是0溢出中断
//             uwTick++;  // 系统滴答计数器
            
//             // 按键按下时间计数
//             if(botton_PushTimeFlag.K1) botton_PushTime.K1++;
//             if(botton_PushTimeFlag.K2) botton_PushTime.K2++;
//             if(botton_PushTimeFlag.K3) botton_PushTime.K3++;
//             if(botton_PushTimeFlag.K4) botton_PushTime.K4++;
//             break;

//         default:  // 其他的定时器中断
//             break;
//     }
// }  
