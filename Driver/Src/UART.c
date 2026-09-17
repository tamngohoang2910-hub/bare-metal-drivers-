#include <stdint.h>
#include "UART.h"
#define uart_baud 115200
#define SYSTEM_CLOCK  72000000UL

void uart_enable(USART_TypeDef *Uartx){
    if (Uartx ==0) 
    return;
    Uartx-> CR1 |= (1<< 13); // Bật bit UE 
}
void uart_disable(USART_TypeDef *Uartx){
    if (Uartx==0)
    return;
    Uartx -> CR1 &= ~(1<<13); //xóa bit UE
}
void uart_init (USART_TypeDef *Uartx,USART_Config *USART_Conf){
    if (Uartx==0 || USART_Conf==0 ){
        return;
    }
    Uartx-> CR1 |= (1<< 13);// tắt trước khi cấu hình

    //số bit 
    if (USART_Conf -> length == uart_word_length_9_bit){
        Uartx -> CR1 |= USART_CR1_M;
    }else{
        Uartx -> CR1 &= ~USART_CR1_M;
    }

    //parity
    if (USART_Conf -> parity != uart_parity_none){
        Uartx->CR1 |= USART_CR1_PCE; // bật parity
        if (USART_Conf -> parity ==uart_parity_odd){
            Uartx -> CR1 |= USART_CR1_PS;
        }
        else{
            Uartx -> CR1 &= ~ USART_CR1_PS;
        }
    }else{
        Uartx->CR1 &= ~USART_CR1_PCE;
    }

    //stop bit
    Uartx -> CR2 &= ~ USART_CR2_STOP;
    Uartx -> CR2 |= (uint32_t)(USART_Conf -> stop_bit <<12);
    
    //mode 
    Uartx -> CR1 &= ~ (USART_CR1_TE | USART_CR1_RE);
    Uartx -> CR1 |= (uint32_t)(USART_Conf -> mode);
}
void uart_send(USART_TypeDef* Uartx, uint8_t data){
    if (Uartx==0) return;
    while (!(USART1 -> SR & USART_SR_TXE));
    USART1 -> DR =data;
}
void uart_receive(USART_TypeDef* Uartx){
    if (Uartx==0) return;
    while (!(USART1-> SR & USART_SR_TXE));
    return (uint8_t)(USART1-> DR & 0XFF);
}