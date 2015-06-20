#include <i2c_dev/i2c_mcp23017.h>
int MCP23017_init(int id){
	int i2c_dev = i2c_init(id);
	write8(i2c_dev,MCP23017_IODIRA, 0x00);//set all gpio in input mode
	write8(i2c_dev,MCP23017_IODIRB, 0x00);
	write8(i2c_dev,MCP23017_GPPUA, 0x00);//disabled pull up for all gpio 
	write8(i2c_dev,MCP23017_GPPUB, 0x00);
	write8(i2c_dev,MCP23017_GPIOA, 0x00);//clear gpio register
	write8(i2c_dev,MCP23017_GPIOB, 0x00);
	write8(i2c_dev,MCP23017_OLATA, 0x00);//clear output register
	write8(i2c_dev,MCP23017_OLATB, 0x00);
	return i2c_dev;
}

uint8_t MCP23017_readandchangepin(int i2c_dev,uint8_t port, int pin, int value){
        uint8_t curVal = read8(i2c_dev,port);
        uint8_t newVal = write_bit(curVal,pin,value);
        write8(i2c_dev,port,newVal);
        return newVal;
}

int MCP23017_setup(int i2c_dev,int pin , int value){//setup pin OUTPUT or INPUT
	uint8_t port;
	if(pin < 8){
		port = MCP23017_IODIRA;
	}
	else{
		pin = pin - 8;
		if(pin >= 8){
			exit(1);
		}
		port = MCP23017_IODIRB;
	}
	return MCP23017_readandchangepin(i2c_dev,port,pin,value);
}

int MCP23017_write(int i2c_dev,int pin , int value){//write value of pin in output mode 
	uint8_t port;
	if(pin < 8){
		port = MCP23017_OLATA;
	}
	else{
		pin = pin - 8;
		if(pin >= 8){
			pin = 0;
		}
		port = MCP23017_OLATB;
	}
	return MCP23017_readandchangepin(i2c_dev,port,pin,value);
}

int MCP23017_read(int i2c_dev,int pin){//read value of the pin
	uint8_t port;
	if(pin < 8){
		port = MCP23017_GPIOA;
	}
	else{
		pin = pin - 8;
		if(pin >= 8){
			pin = 0;
		}
		port = MCP23017_GPIOB;
	}
	uint8_t data = read8(i2c_dev,port);
	return read_bit(data,pin);
}

void MCP23017_write_all(int i2c_dev,uint8_t value){//write value of all pin in output mode 
	uint8_t* data = (uint8_t*)&value;
	write8(i2c_dev,MCP23017_OLATA, data[0]);
	write8(i2c_dev,MCP23017_OLATB, data[1]);
	return;
}

int MCP23017_read_all(int i2c_dev){//read value of all pin in input mode 
	uint8_t data[2];
	data[0] = read8(i2c_dev,MCP23017_GPIOA);
	data[1] = read8(i2c_dev,MCP23017_GPIOB);
	return (uint16_t)*data;
}




