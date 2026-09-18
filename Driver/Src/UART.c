#include <stdint.h>
#include "UART.h"
#define APB1_CLOCK_HZ  36000000UL  
#define APB2_CLOCK_HZ  72000000UL

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

// baudrate
void uart_set_baudrate(USART_TypeDef *Uartx,uint32_t baudrate, uint32_t pclk){
    uint32_t usart_div = ((25*pclk)/(4*baudrate));
    uint32_t mantissa = usart_div / 100;
    uint32_t fraction = usart_div % 100;
    fraction = (fraction*16 +50)/100;
    if (fraction >=16){
        mantissa++;
        fraction=0;
    }
    Uartx ->BRR = (mantissa<<4)|fraction;
}

void uart_init (USART_TypeDef *Uartx, USART_Config *USART_Conf){
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

    //setbaudrate 
    uint32_t pclk;
    if (Uartx == USART1){
        pclk =  APB2_CLOCK_HZ;
    }else{
        pclk = APB1_CLOCK_HZ;
    }
    uart_set_baudrate (Uartx, USART_Conf -> baudrate, pclk);

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