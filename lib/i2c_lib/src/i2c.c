#include <i2c.h>
#include <i2c-dev.h>

int i2c_init(int addr){
	int i2c_dev;
	if ((i2c_dev = open(I2C_FILE,O_RDWR)) < 0){
		printf("Failed to open the bus.\n");
		exit(1);
	}
 
	if (ioctl(i2c_dev,I2C_SLAVE,addr) < 0){
		printf("Failed to acquire bus access and/or talk to slave.\n");
		exit(1);
	}
	return i2c_dev;
}

void write8(int i2c_dev,uint8_t cmd,uint8_t value){
	i2c_smbus_write_byte_data(i2c_dev,cmd,value);
}
uint8_t read8(int i2c_dev,uint8_t cmd){
	return i2c_smbus_read_byte_data(i2c_dev,cmd);
}
void write16(int i2c_dev,uint8_t cmd,uint16_t value){
	i2c_smbus_write_word_data(i2c_dev,cmd,value);
}
uint16_t read16(int i2c_dev,uint8_t cmd){
	return i2c_smbus_read_word_data(i2c_dev,cmd);
}
uint64_t write_bit( uint64_t bitmap, int bit, int value){
	if(value == 0){
	    return bitmap & ~(1 << bit);
	}
	else if(value == 1){
	    return bitmap | (1 << bit);
	}
	return bitmap;
}
uint64_t read_bit(uint64_t bitmap,int bit){
	int e = 0;
	e = bitmap & (1 << bit);
	if (e != 0){
		e = 1;
	}
	return e;
}
