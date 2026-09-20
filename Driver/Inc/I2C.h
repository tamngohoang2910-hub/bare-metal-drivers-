#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define I2C1_BASE 	0x4000 5400
#define I2C2_BASE   0x4000 5800

#define I2C1 ((I2C_TypeDef *)I2C1_BASE)
#define I2C2 ((I2C_TypeDef *)I2C2_BASE)

#define I2C_CR1_PE (1U<<0) 
#define I2C_CR1_START (1U<<8) 
#define I2C_CR1_STOP (1U<<9)
#define I2C_CR1_ACK (1U<<10)
#define I2C_CR1_SWRST (1U<<15)

#define I2C_SR1_SB          (1U << 0)   /* START đã phát. Xóa: đọc SR1 → ghi DR */
#define I2C_SR1_ADDR        (1U << 1)   /* Địa chỉ đã gửi/khớp. Xóa: đọc SR1 → đọc SR2 */
#define I2C_SR1_BTF         (1U << 2)   /* Byte truyền/nhận xong. Xóa: đọc SR1 → đọc/ghi DR */
#define I2C_SR1_ADD10       (1U << 3)   /* Header 10 bit đã gửi. Xóa: đọc SR1 → ghi DR */
#define I2C_SR1_STOPF       (1U << 4)   /* Slave thấy STOP. Xóa: đọc SR1 → ghi CR1 */
                                        /* bit 5: reserved */
#define I2C_SR1_RXNE        (1U << 6)   /* DR có dữ liệu nhận. Xóa: đọc DR */
#define I2C_SR1_TXE         (1U << 7)   /* DR trống. Xóa: ghi DR */
#define I2C_SR1_BERR        (1U << 8)   /* Lỗi bus. Xóa: ghi 0 */
#define I2C_SR1_ARLO        (1U << 9)   /* Mất arbitration. Xóa: ghi 0 */
#define I2C_SR1_AF          (1U << 10)  /* Không nhận được ACK. Xóa: ghi 0 */
#define I2C_SR1_OVR         (1U << 11)  /* Overrun/Underrun. Xóa: ghi 0 */
#define I2C_SR1_PECERR      (1U << 12)  /* Lỗi PEC. Xóa: ghi 0 */
                                        /* bit 13: reserved */
#define I2C_SR1_TIMEOUT     (1U << 14)  /* Timeout SMBus. Xóa: ghi 0 */
#define I2C_SR1_SMBALERT    (1U << 15)  /* SMBus Alert. Xóa: ghi 0 */
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
}I2C_TypeDef;

typedef enum {
    i2c_read =0,
    i2c_write
}I2C_direction_t;

typedef enum{
    i2c_7_b=0,
    i2c_10_b
}I2C_mode_t;

typedef enum{
    i2c_ack=0,
    i2c_nack,
}I2C_ack_t;

typedef enum {
    i2c_speed_std  = 100000,
    i2c_speed_fast = 400000
} i2c_Speed_t;

typedef enum {
    i2c_duty_2 = 0,
    i2c_duty_16_9
} I2C_DutyCycle_t;
 

typedef enum {
    i2c_ok = 0,
    i2c_busy,
    i2c_timeout,
    i2c_ack_fail,
    i2c_error
} I2C_Status_t;

typedef struct {
    uint32_t          ClockSpeed;  
    I2C_DutyCycle_t   DutyCycle;
    I2C_mode_t AddressMode;
    I2C_ack_t         ACK;
} I2C_Config_t;

#endif