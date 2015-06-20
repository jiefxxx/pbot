#ifndef DEF_I2C_LSM303DLH_M
#define DEF_I2C_LSM303DLH_M

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <i2c.h>

#define LSM303DLH_M_ID			(0x3C >> 1)

#define LSM303DLH_CRA_REG_M		0x00
#define LSM303DLH_CRB_REG_M		0x01
#define LSM303DLH_MR_REG_M		0x02
#define LSM303DLH_OUT_X_H_M		0x03
#define LSM303DLH_OUT_X_L_M		0x04
#define LSM303DLH_OUT_Y_H_M		0x05
#define LSM303DLH_OUT_Y_L_M		0x06
#define LSM303DLH_OUT_Z_H_M		0x07
#define LSM303DLH_OUT_Z_L_M		0x08
#define LSM303DLH_SR_REG_M		0x09
#define LSM303DLH_IRA_REG_M		0x0A
#define LSM303DLH_IRB_REG_M		0x0B
#define LSM303DLH_IRC_REG_M		0x0C

#define LSM303DLH_M_CONTINUOUS_MODE	0x00
#define LSM303DLH_M_SINGLE_MODE		0x01
#define LSM303DLH_M_SLEEP_MODE		0x02

#define LSM303DLH_M_DATA_RATE_0_75HZ	0x00
#define LSM303DLH_M_DATA_RATE_1_5HZ	0x04
#define LSM303DLH_M_DATA_RATE_3_0HZ	0x08
#define LSM303DLH_M_DATA_RATE_7_5HZ	0x0C
#define LSM303DLH_M_DATA_RATE_15HZ	0x10
#define LSM303DLH_M_DATA_RATE_30HZ	0x14
#define LSM303DLH_M_DATA_RATE_75HZ	0x18

#define LSM303DLH_M_GAIN_1_3GAUSS	0x20
#define LSM303DLH_M_GAIN_1_9GAUSS	0x40
#define LSM303DLH_M_GAIN_2_5GAUSS	0x60
#define LSM303DLH_M_GAIN_4_0GAUSS	0x80
#define LSM303DLH_M_GAIN_4_7GAUSS	0xA0
#define LSM303DLH_M_GAIN_5_6GAUSS	0xC0
#define LSM303DLH_M_GAIN_8_1GAUSS	0xE0

#define ENABLE	1
#define DISABLE	0

int LSM303DLH_M_init(int id);
void LSM303DLH_M_setDataRate(int i2c_dev, int mode);
void LSM303DLH_M_setGain(int i2c_dev, int mode);
void LSM303DLH_M_setMode(int i2c_dev, int mode);
int LSM303DLH_M_readX(int i2c_dev);
int LSM303DLH_M_readY(int i2c_dev);
int LSM303DLH_M_readZ(int i2c_dev);
int LSM303DLH_M_checkReady(int i2c_dev);
int LSM303DLH_M_checkLock(int i2c_dev);
int LSM303DLH_M_checkVoltRegu(int i2c_dev);

#endif
