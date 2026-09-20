#include <stdint.h>
#include "I2C.h"

void I2C_enable(I2C_TypeDef *I2Cx){
    I2Cx -> CR1 |= I2C_CR1_PE;
}

void I2C_reset(I2C_TypeDef * I2Cx){
    if (I2Cx ==NULL){
        return;
    }else{
        I2Cx->CR1 |= I2C_CR1_SWRST;
        I2Cx -> CR1 &= ~I2C_CR1_SWRST;
    }
}

void I2C_Init (I2C_TypeDef *I2Cx, const I2C_Config_t *Conf){
     if (I2Cx == NULL || Conf == NULL) {
        return;
    }
    I2Cx -> CR1 &= ~I2C_CR1_SWRST;
    if (Conf ->  AddressMode ==  i2c_10_b){

    }
}
void I2C_start ( I2C_TypeDef *I2Cx){
    if (I2Cx == NULL){
        return;
    }
    else {
        I2Cx -> CR1 |= I2C_CR1_START;
    }while (!(I2Cx -> SR1 & I2C_SR1_SB));
}
void I2C_send_data (I2C_TypeDef *I2Cx, uint8_t data){
    while (!(I2Cx -> SR1 & I2C_SR1_TXE));
    I2Cx-> DR = (uint16_t)data;
    while(!(I2Cx -> SR1 & I2C_SR1_BTF));
}

void I2C_send_address(I2C_TypeDef *I2Cx, uint8_t addr, I2C_direction_t direct ){
    if (I2Cx ==NULL){
        return;
    }
    I2Cx -> DR = (uint32_t)(addr <<1U)|(direct);
    while (!(I2Cx -> SR1 & I2C_SR1_ADDR));
    volatile uint32_t x;
    x = I2Cx -> SR1;
    x = I2Cx -> SR2;
}

void I2C_Stop (I2C_TypeDef *I2Cx){
    if (I2Cx == NULL){
        return;
    }
    I2Cx ->CR1 |= I2C_CR1_STOP;
}
