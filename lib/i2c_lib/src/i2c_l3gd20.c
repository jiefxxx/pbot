#include <i2c_dev/i2c_l3gd20.h>
int L3GD20_init(int id){
	int i2c_dev = i2c_init(id);
	int WAI = read8(i2c_dev,L3GD20_WHO_AM_I);
	if(WAI != 0xD4){
		printf("L3GD20 id invalide\n");
		exit(1);	
	}
	write8(i2c_dev,L3GD20_CTRL_REG1,0x0);
	write8(i2c_dev,L3GD20_CTRL_REG2,0x0);
	write8(i2c_dev,L3GD20_CTRL_REG3,0x0);
	write8(i2c_dev,L3GD20_CTRL_REG4,0x0);
	write8(i2c_dev,L3GD20_CTRL_REG5,0x0);
	write8(i2c_dev,L3GD20_FIFO_CTRL_REG,0x0);
	write8(i2c_dev,L3GD20_INT1_CFG,0x0);
	write8(i2c_dev,L3GD20_INT1_TSH_XH,0x0);
	write8(i2c_dev,L3GD20_INT1_TSH_XL,0x0);
	write8(i2c_dev,L3GD20_INT1_TSH_YH,0x0);
	write8(i2c_dev,L3GD20_INT1_TSH_YL,0x0);
	write8(i2c_dev,L3GD20_INT1_TSH_ZH,0x0);
	write8(i2c_dev,L3GD20_INT1_TSH_ZL,0x0);
	write8(i2c_dev,L3GD20_INT1_DURATION,0x0);
	return i2c_dev;
}

void L3GD20_setAxis(int i2c_dev,int enX,int enY, int enZ){
	uint8_t val = read8(i2c_dev,L3GD20_CTRL_REG1);
	val = write_bit(val,0,enY);
	val = write_bit(val,1,enX);
	val = write_bit(val,2,enZ);
	write8(i2c_dev,L3GD20_CTRL_REG1, val);
}

void L3GD20_setPower(int i2c_dev,int en){
	uint8_t val = read8(i2c_dev,L3GD20_CTRL_REG1);
	val = write_bit(val,3,en);
	write8(i2c_dev,L3GD20_CTRL_REG1, val);
}

void L3GD20_rebootMem(int i2c_dev){
	uint8_t val = read8(i2c_dev,L3GD20_CTRL_REG5);
	val = write_bit(val,7,1);
	write8(i2c_dev,L3GD20_CTRL_REG5, val);
}

void L3GD20_setFifo(int i2c_dev,int en){
	uint8_t val = read8(i2c_dev,L3GD20_CTRL_REG5);
	val = write_bit(val,6,en);
	write8(i2c_dev,L3GD20_CTRL_REG5, val);
}

void L3GD20_setHigPass(int i2c_dev,int en){
	uint8_t val = read8(i2c_dev,L3GD20_CTRL_REG5);
	val = write_bit(val,4,en);
	write8(i2c_dev,L3GD20_CTRL_REG5, val);
}


void L3GD20_setFifoMode(int i2c_dev,int mode){
	uint8_t val = read8(i2c_dev,L3GD20_FIFO_CTRL_REG);
	switch(mode){
		case L3GD20_STREAM_MODE:
			val = write_bit(val,5,0);
			val = write_bit(val,6,1);
			val = write_bit(val,7,0);
			break;
		case L3GD20_FIFO_MODE:
			val = write_bit(val,5,1);
			val = write_bit(val,6,0);
			val = write_bit(val,7,0);
			break;
		case L3GD20_STREAM_TO_FIFO_MODE:
			val = write_bit(val,5,1);
			val = write_bit(val,6,1);
			val = write_bit(val,7,0);
			break;
		case L3GD20_BYPASS_TO_STREAM_MODE:
			val = write_bit(val,5,0);
			val = write_bit(val,6,0);
			val = write_bit(val,7,1);
			break;
	}
	write8(i2c_dev,L3GD20_FIFO_CTRL_REG, val);
}

void L3GD20_setDataRate(int i2c_dev,uint8_t DataRate){
	uint8_t RegisterValue;

	RegisterValue = read8(i2c_dev,L3GD20_CTRL_REG1);

	RegisterValue &= ~(0xC0);
	RegisterValue |= ((DataRate & 0x03) << 6);

	write8(i2c_dev,L3GD20_CTRL_REG1, RegisterValue);
}

void L3GD20_setBandwidth(int i2c_dev,uint8_t Bandwidth){
	uint8_t RegisterValue;

	RegisterValue = read8(i2c_dev,L3GD20_CTRL_REG1);

	RegisterValue &= ~(0x30);
	RegisterValue |= ((Bandwidth & 0x03) << 4);

	write8(i2c_dev,L3GD20_CTRL_REG1, RegisterValue);
}

int L3GD20_getSizeFifo(int i2c_dev){
	uint8_t val = read8(i2c_dev,L3GD20_FIFO_SRC_REG);
	if (read_bit(val,5) == 1){
		return 0;
	}
	val = write_bit(val,6,0);
	val = write_bit(val,7,0);
	return val;
}

int L3GD20_checkOverrunFifo(int i2c_dev){
	return read_bit(read8(i2c_dev,L3GD20_FIFO_SRC_REG),6);
}

int L3GD20_checkDataAvailableX(int i2c_dev){
	return read_bit(read8(i2c_dev,L3GD20_STATUS_REG),0);
}

int L3GD20_checkDataAvailableY(int i2c_dev){
	return read_bit(read8(i2c_dev,L3GD20_STATUS_REG),1);
}

int L3GD20_checkDataAvailableZ(int i2c_dev){
	return read_bit(read8(i2c_dev,L3GD20_STATUS_REG),2);
}

int L3GD20_checkDataAvailableXYZ(int i2c_dev){
	return read_bit(read8(i2c_dev,L3GD20_STATUS_REG),3);
}

int L3GD20_readX(int i2c_dev){
	while(L3GD20_checkDataAvailableX(i2c_dev)==0);
	int d1=read8(i2c_dev,L3GD20_OUT_X_L); 
	int d2= read8(i2c_dev,L3GD20_OUT_X_H);
	int ret = (short)((d2 << 8) | d1);
	return ret;
}

int L3GD20_readY(int i2c_dev){
	while(L3GD20_checkDataAvailableY(i2c_dev)==0);
	int d1=read8(i2c_dev,L3GD20_OUT_Y_L); 
	int d2= read8(i2c_dev,L3GD20_OUT_Y_H);
	short ret = (short)((d2 << 8) | d1);
	return ret;
}

int L3GD20_readZ(int i2c_dev){
	while(L3GD20_checkDataAvailableZ(i2c_dev)==0);
	int d1=read8(i2c_dev,L3GD20_OUT_Z_L); 
	int d2= read8(i2c_dev,L3GD20_OUT_Z_H);
	int ret = (short)((d2 << 8) | d1);
	return ret;
}
//relic
/*
void calibrate(){
	stats statsX = stats();
	stats statsY = stats();
	stats statsZ = stats();
	for(int i = 0;i<30;i++){
		int x = readX();
		int y = readY();
		int z = readZ();
	}
	for(int i = 0;i<200;i++){
		int x = readX();
		int y = readY();
		int z = readZ();
		statsX.add_val(x);
		statsY.add_val(y);
		statsZ.add_val(z);
		//printf("x : %i\n",x);
		//printf("y : %i\n",y); 
		//printf("z : %i\n",z); 
	}
	meanX = statsX.get_mean();
	maxX = statsX.get_max();
	minX = statsX.get_min();
	
	meanY = statsY.get_mean();
	maxY = statsY.get_max();
	minY = statsY.get_min();
	
	meanZ = statsZ.get_mean();
	maxZ = statsZ.get_max();
	minZ = statsZ.get_min();
}
*/
/*
int readCalX(int i2c_dev){
	int val = readX();
        if(val >= minX && val <= maxX){
            return 0;
	}
        else{
            return (val - meanX)*gain;
	}
}

int readCalY(int i2c_dev){
	int val = readY();
        if(val >= minY && val <= maxY){
            return 0;
	}
        else{
            return (val - meanY)*gain;
	}
}

int readCalZ(int i2c_dev){
	int val = readZ();
        if(val >= minZ && val <= maxZ){
            return 0;
	}
        else{
            return (val - meanZ)*gain;
	}
}
*/
