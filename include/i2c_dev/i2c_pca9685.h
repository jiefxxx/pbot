#ifndef DEF_I2C_PCA9685
#define DEF_I2C_PCA9685

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include <i2c.h>

#define PCA9685_ID		0x40

#define PCA9685_MODE1		0x00
#define PCA9685_MODE2		0x01
#define PCA9685_SUBADR1		0x02
#define PCA9685_SUBADR2		0x03
#define PCA9685_SUBADR3		0x04
#define PCA9685_PRESCALE	0xFE
#define PCA9685_LED0_ON_L	0x06
#define PCA9685_LED0_ON_H	0x07
#define PCA9685_LED0_OFF_L	0x08
#define PCA9685_LED0_OFF_H	0x09
#define PCA9685_ALL_LED_ON_L	0xFA
#define PCA9685_ALL_LED_ON_H	0xFB
#define PCA9685_ALL_LED_OFF_L	0xFC
#define PCA9685_ALL_LED_OFF_H	0xFD

#define PCA9685_RESTART		0x80
#define PCA9685_SLEEP		0x10
#define PCA9685_ALLCALL		0x01
#define PCA9685_INVRT		0x10
#define PCA9685_OUTDRV		0x04

 

int PCA9685_init(int id);
void PCA9685_start(int i2c_dev);
void PCA9685_setPwmFreq(int i2c_dev, float freq);
void PCA9685_setPwm(int i2c_dev, int chan, int on, int off);
void PCA9685_setAllPwm(int i2c_dev, int on, int off);

#endif
