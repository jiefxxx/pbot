#ifndef DEF_I2C_MCP23017
#define DEF_I2C_MCP23017

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <i2c.h>


#define MCP23017_IODIRA    0x00
#define MCP23017_IODIRB    0x01
#define MCP23017_IPOLA     0x02
#define MCP23017_IPOLB     0x03
#define MCP23017_GPINTENA  0x04
#define MCP23017_GPINTENB  0x05
#define MCP23017_DEFVALA   0x06
#define MCP23017_DEFVALB   0x07
#define MCP23017_INTCONA   0x08
#define MCP23017_INTCONB   0x09
#define MCP23017_IOCONA    0x0A
#define MCP23017_IOCONB    0x0B
#define MCP23017_GPPUA     0x0C
#define MCP23017_GPPUB     0x0D
#define MCP23017_INTFA     0x0E
#define MCP23017_INTFB     0x0F
#define MCP23017_INTCAPA   0x10
#define MCP23017_INTCAPB   0x11
#define MCP23017_GPIOA     0x12
#define MCP23017_GPIOB     0x13
#define MCP23017_OLATA     0x14
#define MCP23017_OLATB     0x15

#define GPIO_0     0
#define GPIO_1     1
#define GPIO_2     2
#define GPIO_3     3
#define GPIO_4     4
#define GPIO_5     5
#define GPIO_6     6
#define GPIO_7     7
#define GPIO_8	   8
#define GPIO_9     9
#define GPIO_10    10
#define GPIO_11    11
#define GPIO_12    12
#define GPIO_13    13
#define GPIO_14    14
#define GPIO_15    15

#define OUTPUT   0
#define INPUT    1

int MCP23017_init(int id);
int MCP23017_setup(int i2c_dev,int pin , int value);
int MCP23017_write(int i2c_dev,int pin , int value);
int MCP23017_read(int i2c_dev,int pin);
void MCP23017_write_all(int i2c_dev,uint8_t value);
int MCP23017_read_all(int i2c_dev);
uint8_t MCP23017_readandchangepin(int i2c_dev,uint8_t port, int pin, int value);

#endif
