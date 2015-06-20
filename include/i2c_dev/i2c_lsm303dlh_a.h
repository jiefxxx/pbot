#ifndef DEF_I2C_LSM303DLH_A
#define DEF_I2C_LSM303DLH_A

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <i2c.h>

#define LSM303DLH_A_ID			(0x32 >> 1)

#define LSM303DLH_CTRL_REG1_A		0x20
#define LSM303DLH_CTRL_REG2_A		0x21
#define LSM303DLH_CTRL_REG3_A		0x22
#define LSM303DLH_CTRL_REG4_A		0x23
#define LSM303DLH_CTRL_REG5_A		0x24
#define LSM303DLH_HP_FILTER_RESET_A	0x25
#define LSM303DLH_REFERENCE_A		0x26
#define LSM303DLH_STATUS_REG_A		0x27
#define LSM303DLH_OUT_X_L_A		0x28
#define LSM303DLH_OUT_X_H_A		0x29
#define LSM303DLH_OUT_Y_L_A		0x2A
#define LSM303DLH_OUT_Y_H_A		0x2B
#define LSM303DLH_OUT_Z_L_A		0x2C
#define LSM303DLH_OUT_Z_H_A		0x2D
#define LSM303DLH_INT1_CFG_A		0x30
#define LSM303DLH_INT1_SOURCE_A		0x31
#define LSM303DLH_INT1_THS_A		0x32
#define LSM303DLH_INT1_DURATION_A	0x33
#define LSM303DLH_INT2_CFG_A		0x34
#define LSM303DLH_INT2_SOURCE_A		0x35
#define LSM303DLH_INT2_THS_A		0x36
#define LSM303DLH_INT2_DURATION_A	0x37

#define LSM303DLH_A_POWERDOWN_MODE	0x00
#define LSM303DLH_A_NORMAL_MODE		0x20
#define LSM303DLH_A_LOWERPOWER_1_MODE	0x40
#define LSM303DLH_A_LOWERPOWER_2_MODE	0x60
#define LSM303DLH_A_LOWERPOWER_3_MODE	0x80
#define LSM303DLH_A_LOWERPOWER_4_MODE	0xA0
#define LSM303DLH_A_LOWERPOWER_5_MODE	0xC0

#define LSM303DLH_A_DATA_RATE_50HZ	0x00
#define LSM303DLH_A_DATA_RATE_100HZ	0x08
#define LSM303DLH_A_DATA_RATE_400HZ	0x10
#define LSM303DLH_A_DATA_RATE_1000HZ	0x18

#define ENABLE	1
#define DISABLE	0

int LSM303DLH_A_init(int id);
void LSM303DLH_A_setAxis(int i2c_dev,int enX,int enY, int enZ);
void LSM303DLH_A_setDataRate(int i2c_dev,int mode);
void LSM303DLH_A_setPowerMode(int i2c_dev,int mode);
int LSM303DLH_A_checkDataAvailableX(int i2c_dev);
int LSM303DLH_A_checkDataAvailableY(int i2c_dev);
int LSM303DLH_A_checkDataAvailableZ(int i2c_dev);
int LSM303DLH_A_checkDataAvailableXYZ(int i2c_dev);
int LSM303DLH_A_readX(int i2c_dev);
int LSM303DLH_A_readY(int i2c_dev);
int LSM303DLH_A_readZ(int i2c_dev);

#endif
