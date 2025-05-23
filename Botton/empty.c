#include "empty.h"
#include "key.h"
#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti_msp_dl_config.h"
#include "UART.h"
#include <stdio.h>
#include <string.h>

uint32_t uwTick = 0;

int main(void)
{
    SYSCFG_DL_init();
    
    // 清除定时器中断标志
    NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
    NVIC_ClearPendingIRQ(UART0_INT_IRQn);
    // 使能定时器中断
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    //
    printf("Hello \n");


    while (1)
    {   
        Botton_Process();
    
    }
}


// 定时器的中断服务函数 已配置为1ms的周期
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

int fputc(int c, FILE* stream)
{
	DL_UART_Main_transmitDataBlocking(UART0, c);
    return c;
}
 
int fputs(const char* restrict s, FILE* restrict stream)
{
    uint16_t i, len;
    len = strlen(s);
    for(i=0; i<len; i++)
    {
        DL_UART_Main_transmitDataBlocking(UART0, s[i]);
    }
    return len;
}
 
int puts(const char *_ptr)
{
        int count = fputs(_ptr,stdout);
        count +=fputs("\n",stdout);
        return count;
}
