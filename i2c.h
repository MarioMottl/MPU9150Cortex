/*
Kommentar
*/
#ifndef I2C_H_INCLUDED
#define I2C_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <armv10_std.h>

#define GPIOB_IDR GPIOB_BASE + 2*sizeof(uint32_t)
#define SDA *((volatile unsigned long *)(BITBAND_PERI(GPIOB_ODR,7))) //PB7
#define SCL *((volatile unsigned long *)(BITBAND_PERI(GPIOB_ODR,6))) //PB6
#define SDA_IN *((volatile unsigned long *)(BITBAND_PERI(GPIOB_IDR,7))) //PB7 - Input
#define SCL_IN *((volatile unsigned long *)(BITBAND_PERI(GPIOB_IDR,6))) //PB6 - Input


//Funktionen
void i2c_init(void);
void i2c_delay(void);
void i2c_start(void);
void i2c_stop(void);
unsigned char i2c_write(unsigned char data);
unsigned char i2c_read(char ack);

#endif
