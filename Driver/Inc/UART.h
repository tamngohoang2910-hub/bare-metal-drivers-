#ifndef USART_H
#define USART_H
#include <stdint.h>

#define APB2PERIPH_BASE  0x40010000UL
#define APB1PERIPH_BASE  0x40000000UL

#define USART1_BASE (APB2PERIPH_BASE + 0x3800UL)   
#define USART2_BASE (APB1PERIPH_BASE + 0x4400UL)   
#define USART3_BASE (APB1PERIPH_BASE + 0x4800UL)   

#define USART1 ((USART_TypeDef *) USART1_BASE)
#define USART2 ((USART_TypeDef *) USART2_BASE)
#define USART3 ((USART_TypeDef *) USART3_BASE)

#define USART_CR1_UE   (1U << 13)
#define USART_CR1_TE   (1U << 3)
#define USART_CR1_RE   (1U << 2)
#define USART_CR1_M    (1U << 12)
#define USART_CR1_PCE  (1U << 10)
#define USART_CR1_PS   (1U << 9)

#define USART_SR_TXE   (1U << 7)
#define USART_SR_RXNE  (1U << 5)
#define USART_SR_TC    (1U << 6)

#define USART_CR2_STOP (3U << 12)

typedef struct{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
}USART_TypeDef;

typedef enum{
    uart_tx=USART_CR1_TE,
    uart_rx= USART_CR1_RE,
    uart_tx_and_rx = (USART_CR1_RE| USART_CR1_TE)
}USART_MODE_t;


typedef enum{
    uart_word_length_8_bit=0,
    uart_word_length_9_bit
}USART_WORDLENGTH_t;

typedef enum{
    uart_parity_odd=0,
    uart_parity_even,
    uart_parity_none
}USART_PARITY_t;

typedef enum{
    uart_stop_bit_1=0b00,
    uart_stop_bit_0_5=0b01,
    uart_stop_bit_2=0b10,
    uart_stop_bit_1_5=0b11
}USART_STOP_BIT_t;

typedef struct {
    uint32_t baudrate;
    USART_MODE_t mode;
    USART_WORDLENGTH_t length;
    USART_PARITY_t parity;
    USART_STOP_BIT_t stop_bit;
}USART_Config;

void uart_init(USART_TypeDef *Uartx, const USART_Config *Conf);
void uart_enable (USART_TypeDef *Uartx);
void uart_disable (USART_TypeDef *Uartx);
void uart_set_baudrate(USART_TypeDef *Uartx,uint32_t baudrate, uint32_t pclk);
void uart_send(USART_TypeDef *Uartx, uint8_t data);
uint8_t uart_receive(USART_TypeDef *Uartx);

#endif