#include <i2c_dev/i2c_lsm303dlh_a.h>
int LSM303DLH_A_init(int id){
	int i2c_dev = i2c_init(id);
	write8(i2c_dev,LSM303DLH_CTRL_REG1_A, 0x0);
	write8(i2c_dev,LSM303DLH_CTRL_REG2_A, 0x0);
	write8(i2c_dev,LSM303DLH_CTRL_REG3_A, 0x0);
	write8(i2c_dev,LSM303DLH_CTRL_REG4_A, 0x0);
	write8(i2c_dev,LSM303DLH_CTRL_REG5_A, 0x0);
	write8(i2c_dev,LSM303DLH_REFERENCE_A, 0x0);
	write8(i2c_dev,LSM303DLH_INT1_CFG_A, 0x0);
	write8(i2c_dev,LSM303DLH_INT1_THS_A, 0x0);
	write8(i2c_dev,LSM303DLH_INT1_DURATION_A, 0x0);
	write8(i2c_dev,LSM303DLH_INT2_CFG_A, 0x0);
	write8(i2c_dev,LSM303DLH_INT2_THS_A, 0x0);
	write8(i2c_dev,LSM303DLH_INT2_DURATION_A, 0x0);
	return i2c_dev;
}

void LSM303DLH_A_setAxis(int i2c_dev,int enX,int enY, int enZ){
	uint8_t val = read8(i2c_dev,LSM303DLH_CTRL_REG1_A);
	val = write_bit(val,0,enY);
	val = write_bit(val,1,enX);
	val = write_bit(val,2,enZ);
	write8(i2c_dev,LSM303DLH_CTRL_REG1_A, val);
}

void LSM303DLH_A_setDataRate(int i2c_dev,int mode){
	uint8_t val = read8(i2c_dev,LSM303DLH_CTRL_REG1_A);
	switch(mode){
		case LSM303DLH_A_DATA_RATE_50HZ:
			val = write_bit(val,3,0);
			val = write_bit(val,4,0);
			break;
		case LSM303DLH_A_DATA_RATE_100HZ:
			val = write_bit(val,3,1);
			val = write_bit(val,4,0);
			break;
		case LSM303DLH_A_DATA_RATE_400HZ:
			val = write_bit(val,3,0);
			val = write_bit(val,4,1);
			break;
		case LSM303DLH_A_DATA_RATE_1000HZ:
			val = write_bit(val,3,1);
			val = write_bit(val,4,1);
			break;
	}
	write8(i2c_dev,LSM303DLH_CTRL_REG1_A, val);
}

void LSM303DLH_A_setPowerMode(int i2c_dev,int mode){
	uint8_t val = read8(i2c_dev,LSM303DLH_CTRL_REG1_A);
	switch(mode){
		case LSM303DLH_A_POWERDOWN_MODE:
			val = write_bit(val,5,0);
			val = write_bit(val,6,0);
			val = write_bit(val,7,0);
			break;
		case LSM303DLH_A_NORMAL_MODE:
			val = write_bit(val,5,1);
			val = write_bit(val,6,0);
			val = write_bit(val,7,0);
			break;
		case LSM303DLH_A_LOWERPOWER_1_MODE:
			val = write_bit(val,5,0);
			val = write_bit(val,6,1);
			val = write_bit(val,7,0);
			break;
		case LSM303DLH_A_LOWERPOWER_2_MODE:
			val = write_bit(val,5,1);
			val = write_bit(val,6,1);
			val = write_bit(val,7,0);
			break;
		case LSM303DLH_A_LOWERPOWER_3_MODE:
			val = write_bit(val,5,0);
			val = write_bit(val,6,0);
			val = write_bit(val,7,1);
			break;
		case LSM303DLH_A_LOWERPOWER_4_MODE:
			val = write_bit(val,5,1);
			val = write_bit(val,6,0);
			val = write_bit(val,7,1);
			break;
		case LSM303DLH_A_LOWERPOWER_5_MODE:
			val = write_bit(val,5,0);
			val = write_bit(val,6,1);
			val = write_bit(val,7,1);
			break;
	}
	write8(i2c_dev,LSM303DLH_CTRL_REG1_A, val);
}


int LSM303DLH_A_checkDataAvailableX(int i2c_dev){
	return read_bit(read8(i2c_dev,LSM303DLH_STATUS_REG_A),0);
}

int LSM303DLH_A_checkDataAvailableY(int i2c_dev){
	return read_bit(read8(i2c_dev,LSM303DLH_STATUS_REG_A),1);
}

int LSM303DLH_A_checkDataAvailableZ(int i2c_dev){
	return read_bit(read8(i2c_dev,LSM303DLH_STATUS_REG_A),2);
}

int LSM303DLH_A_checkDataAvailableXYZ(int i2c_dev){
	return read_bit(read8(i2c_dev,LSM303DLH_STATUS_REG_A),3);
}

int LSM303DLH_A_readX(int i2c_dev){
	while(LSM303DLH_A_checkDataAvailableX(i2c_dev)==0);
	int d1=read8(i2c_dev,LSM303DLH_OUT_X_L_A); 
	int d2= read8(i2c_dev,LSM303DLH_OUT_X_H_A);
	int ret = (short)((d2 << 8) | d1);
	return ret;
}

int LSM303DLH_A_readY(int i2c_dev){
	while(LSM303DLH_A_checkDataAvailableY(i2c_dev)==0);
	int d1=read8(i2c_dev,LSM303DLH_OUT_Y_L_A); 
	int d2= read8(i2c_dev,LSM303DLH_OUT_Y_H_A);
	short ret = (short)((d2 << 8) | d1);
	return ret;
}

int LSM303DLH_A_readZ(int i2c_dev){
	while(LSM303DLH_A_checkDataAvailableZ(i2c_dev)==0);
	int d1=read8(i2c_dev,LSM303DLH_OUT_Z_L_A); 
	int d2= read8(i2c_dev,LSM303DLH_OUT_Z_H_A);
	int ret = (short)((d2 << 8) | d1);
	return ret;
}

