#ifndef DEF_I2C
#define DEF_I2C
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define I2C_FILE "/dev/i2c-1"

int i2c_init(int addr);
void write8(int i2c_dev,uint8_t cmd,uint8_t value);
uint8_t read8(int i2c_dev,uint8_t cmd);
void write16(int i2c_dev,uint8_t cmd,uint16_t value);
uint16_t read16(int i2c_dev,uint8_t cmd);
uint64_t write_bit( uint64_t bitmap, int bit, int value);
uint64_t read_bit(uint64_t bitmap,int bit);

int file;
#endif
