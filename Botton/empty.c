#include "empty.h"
#include "key.h"

uint32_t uwTick = 0;

int main(void)
{
    SYSCFG_DL_init();
    
    // 清除定时器中断标志
    NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
    // 使能定时器中断
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);

    while (1)
    {   
        // 调用按键处理函数，内部已经包含了状态读取和防抖处理
        Botton_Process();
        
        // 如果需要，可以添加其他任务
        // 由于Botton_Process已经有100ms的调用限制，这里不会占用太多CPU
    }
}

// 定时器的中断服务函数 已配置为1ms的周期（建议修改为1ms以提高精度）
void TIMER_0_INST_IRQHandler(void)
{
    // 如果产生了定时器中断
    switch( DL_TimerG_getPendingInterrupt(TIMER_0_INST) )
    {
        case DL_TIMER_IIDX_ZERO:  // 如果是0溢出中断
            uwTick++;  // 系统滴答计数器
            
            // 按键按下时间计数
            if(botton_PushTimeFlag.K1) botton_PushTime.K1++;
            if(botton_PushTimeFlag.K2) botton_PushTime.K2++;
            if(botton_PushTimeFlag.K3) botton_PushTime.K3++;
            if(botton_PushTimeFlag.K4) botton_PushTime.K4++;
            break;

        default:  // 其他的定时器中断
            break;
    }
}