#ifndef DEF_I2C_MCP23008
#define DEF_I2C_MCP23008

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <i2c.h>


#define MCP23008_IODIR    0x00
#define MCP23008_IPOL     0x01
#define MCP23008_GPINTEN  0x02
#define MCP23008_DEFVAL   0x03
#define MCP23008_INTCON   0x04
#define MCP23008_IOCON    0x05
#define MCP23008_GPPU     0x06
#define MCP23008_INTF     0x07
#define MCP23008_INTCAP   0x08
#define MCP23008_GPIO     0x09
#define MCP23008_OLAT     0x0A

#define GPIO_0     0
#define GPIO_1     1
#define GPIO_2     2
#define GPIO_3     3
#define GPIO_4     4
#define GPIO_5     5
#define GPIO_6     6
#define GPIO_7     7

#define OUTPUT   0
#define INPUT    1

int MCP23008_init(int id);
int MCP23008_setup(int i2c_dev,int pin , int value);
int MCP23008_write(int i2c_dev,int pin , int value);
int MCP23008_read(int i2c_dev,int pin);
void MCP23008_write_all(int i2c_dev,uint8_t value);
int MCP23008_read_all(int i2c_dev);
uint8_t MCP23008_readandchangepin(int i2c_dev,uint8_t port, int pin, int value);

#endif
