#ifndef DEF_I2C_L3GD20
#define DEF_I2C_L3GD20

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <i2c.h>

#define L3GD20_ID		0x6B

#define L3GD20_WHO_AM_I		0x0F
#define L3GD20_CTRL_REG1	0x20
#define L3GD20_CTRL_REG2	0x21
#define L3GD20_CTRL_REG3	0x22
#define L3GD20_CTRL_REG4	0x23
#define L3GD20_CTRL_REG5	0x24
#define L3GD20_REFERENCE	0x25
#define L3GD20_OUT_TEMP		0x26
#define L3GD20_STATUS_REG	0x27
#define L3GD20_OUT_X_L		0x28
#define L3GD20_OUT_X_H		0x29
#define L3GD20_OUT_Y_L		0x2A
#define L3GD20_OUT_Y_H		0x2B
#define L3GD20_OUT_Z_L		0x2C
#define L3GD20_OUT_Z_H		0x2D
#define L3GD20_FIFO_CTRL_REG	0x2E
#define L3GD20_FIFO_SRC_REG	0x2F
#define L3GD20_INT1_CFG		0x30
#define L3GD20_INT1_SRC		0x31
#define L3GD20_INT1_TSH_XH	0x32
#define L3GD20_INT1_TSH_XL	0x33
#define L3GD20_INT1_TSH_YH	0x34
#define L3GD20_INT1_TSH_YL	0x35
#define L3GD20_INT1_TSH_ZH	0x36
#define L3GD20_INT1_TSH_ZL	0x37
#define L3GD20_INT1_DURATION	0x38

#define L3GD20_FIFO_MODE		0x20
#define L3GD20_STREAM_MODE		0x40
#define L3GD20_STREAM_TO_FIFO_MODE	0x60
#define L3GD20_BYPASS_TO_STREAM_MODE	0x80

#define ENABLE	1
#define DISABLE	0

#define L3GD20_DATA_RATE_95_HZ		0x0
#define L3GD20_DATA_RATE_190_HZ		0x1
#define L3GD20_DATA_RATE_380_HZ		0x2
#define L3GD20_DATA_RATE_760_HZ		0x3

int L3GD20_init(int id);					//get the file id i2c-dev
void L3GD20_setBandwidth(int i2c_dev,uint8_t Bandwidth);	//
void L3GD20_setDataRate(int i2c_dev,uint8_t);			//	
void L3GD20_setAxis(int i2c_dev,int,int,int);			//	
void L3GD20_setPower(int i2c_dev,int);				//
void L3GD20_setFifo(int i2c_dev,int);				//
void L3GD20_setHigPass(int i2c_dev,int);			//
void L3GD20_setFifoMode(int i2c_dev,int);			//
void L3GD20_rebootMem(int i2c_dev);				//
int L3GD20_checkOverrunFifo(int i2c_dev);
int L3GD20_checkDataAvailableX(int i2c_dev);
int L3GD20_checkDataAvailableY(int i2c_dev);
int L3GD20_checkDataAvailableZ(int i2c_dev);
int L3GD20_checkDataAvailableXYZ(int i2c_dev);
int L3GD20_getSizeFifo(int i2c_dev);
int L3GD20_readX(int i2c_dev);
int L3GD20_readY(int i2c_dev);
int L3GD20_readZ(int i2c_dev);
//void calibrate(int i2c_dev);
//int readCalX(int i2c_dev);
//int readCalY(int i2c_dev);
//int readCalZ(int i2c_dev);

#endif
