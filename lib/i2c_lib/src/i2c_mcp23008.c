#include <i2c_dev/i2c_mcp23008.h>
int MCP23008_init(int id){
	int i2c_dev = i2c_init(id);
	write8(i2c_dev,MCP23008_IODIR, 0x00);//set all gpio in input mode
	write8(i2c_dev,MCP23008_GPPU, 0x00);//disabled pull up for all gpio 
	write8(i2c_dev,MCP23008_GPIO, 0x00);//clear gpio register
	write8(i2c_dev,MCP23008_OLAT, 0x00);//clear output register
	return i2c_dev;
}

uint8_t MCP23008_readandchangepin(int i2c_dev,uint8_t port, int pin, int value){
        uint8_t curVal = read8(i2c_dev,port);
        uint8_t newVal = write_bit(curVal,pin,value);
        write8(i2c_dev,port,newVal);
        return newVal;
}

int MCP23008_setup(int i2c_dev,int pin , int value){//setup pin OUTPUT or INPUT
	return MCP23008_readandchangepin(i2c_dev,MCP23008_IODIR,pin,value);
}

int MCP23008_write(int i2c_dev,int pin , int value){//write value of pin in output mode 
	return MCP23008_readandchangepin(i2c_dev,MCP23008_OLAT,pin,value);
}

int MCP23008_read(int i2c_dev,int pin){//read value of the pin
	uint8_t data = read8(i2c_dev,MCP23008_GPIO);
	return read_bit(data,pin);
}

void MCP23008_write_all(int i2c_dev,uint8_t value){//write value of all pin in output mode 
	write8(i2c_dev,MCP23008_OLAT, value);
	return;
}

int MCP23008_read_all(int i2c_dev){//read value of all pin in input mode 
	return read8(i2c_dev,MCP23008_GPIO);
}
