#include <stdint.h>
#include "GPIO.h"


void GPIO_Init(MyGPIO_TypeDef *port, uint8_t pin, GPIO_Mode_t mode)
{
    uint32_t pos = (pin % 8) * 4;   

    if (pin < 8) {
        port->CRL &= ~(0xF << pos);       
        port->CRL |=  (mode << pos);     
    } else {
        port->CRH &= ~(0xF << pos);
        port->CRH |=  (mode << pos);
    }
}

void GPIO_SetPullMode( MyGPIO_TypeDef *port, uint8_t pin, GPIO_Pull_t pull)
{
    if (pull == GPIO_PULL_UP) {
        port->ODR |= (1 << pin);
    } else {
        port->ODR &= ~(1 << pin);
    }
}

void GPIO_SetPin(MyGPIO_TypeDef *port, uint8_t pin)
{
    port->BSRR = (1 << pin);           
}

void GPIO_ClearPin(MyGPIO_TypeDef *port, uint8_t pin)
{
    port->BSRR = (1 << (pin + 16));    
}

void GPIO_TogglePin(MyGPIO_TypeDef *port, uint8_t pin)
{
    port->ODR ^= (1 << pin);           
}

uint8_t GPIO_ReadPin(MyGPIO_TypeDef *port, uint8_t pin)
{
    return (port->IDR >> pin) & 0x01;
}