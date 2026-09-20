#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} MyGPIO_TypeDef;

#define MyGPIOA   ((MyGPIO_TypeDef *)0x40010800UL)
#define MyGPIOB   ((MyGPIO_TypeDef *)0x40010C00UL)
#define MyGPIOC   ((MyGPIO_TypeDef *)0x40011000UL)
#define MyGPIOD   ((MyGPIO_TypeDef *)0x40011400UL)


typedef enum {
    GPIO_MODE_INPUT_ANALOG,
    GPIO_MODE_INPUT_FLOATING,
    GPIO_MODE_INPUT_PULLUP,
    GPIO_MODE_OUTPUT_PP_50,
    GPIO_MODE_OUTPUT_OD_50,
    GPIO_MODE_AF_PP_50,
    GPIO_MODE_AF_OD_50,
}GPIO_Mode_t;

typedef enum {
    GPIO_PULL_DOWN = 0,
    GPIO_PULL_UP   = 1
} GPIO_Pull_t;

void GPIO_Init(MyGPIO_TypeDef *port, uint8_t pin, GPIO_Mode_t mode);
void GPIO_SetPullMode(MyGPIO_TypeDef *port, uint8_t pin, GPIO_Pull_t pull);
void GPIO_SetPin(MyGPIO_TypeDef *port, uint8_t pin);
void GPIO_ClearPin(MyGPIO_TypeDef *port, uint8_t pin);
void GPIO_TogglePin(MyGPIO_TypeDef *port, uint8_t pin);
uint8_t GPIO_ReadPin(MyGPIO_TypeDef *port, uint8_t pin);

#endif