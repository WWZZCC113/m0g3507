#ifndef __UART_H_
#define __UART_H_

#include "ti_msp_dl_config.h"

extern volatile unsigned char uart_data ;

void UART_0_INST_IRQHandler(void);
void uart0_send_char(char ch);
void uart0_send_string(char* str);

#endif