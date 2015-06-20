#include <i2c_dev/i2c_lsm303dlh_m.h>
int LSM303DLH_M_init(int id){
	int i2c_dev= i2c_init(id);
	write8(i2c_dev,LSM303DLH_CRA_REG_M, 0x10);
	write8(i2c_dev,LSM303DLH_CRB_REG_M, 0x20);
	write8(i2c_dev,LSM303DLH_MR_REG_M, 0x3);
	return i2c_dev;
}

void LSM303DLH_M_setDataRate(int i2c_dev, int mode){
	uint8_t val = read8(i2c_dev,LSM303DLH_CRA_REG_M);
	switch(mode){
		case LSM303DLH_M_DATA_RATE_0_75HZ:
			val = write_bit(val,2,0);
			val = write_bit(val,3,0);
			val = write_bit(val,4,0);
			break;
		case LSM303DLH_M_DATA_RATE_1_5HZ:
			val = write_bit(val,2,1);
			val = write_bit(val,3,0);
			val = write_bit(val,4,0);
			break;
		case LSM303DLH_M_DATA_RATE_3_0HZ:
			val = write_bit(val,2,0);
			val = write_bit(val,3,1);
			val = write_bit(val,4,0);
			break;
		case LSM303DLH_M_DATA_RATE_7_5HZ:
			val = write_bit(val,2,1);
			val = write_bit(val,3,1);
			val = write_bit(val,4,0);
			break;
		case LSM303DLH_M_DATA_RATE_15HZ:
			val = write_bit(val,2,0);
			val = write_bit(val,3,0);
			val = write_bit(val,4,1);
			break;
		case LSM303DLH_M_DATA_RATE_30HZ:
			val = write_bit(val,2,1);
			val = write_bit(val,3,0);
			val = write_bit(val,4,1);
			break;
		case LSM303DLH_M_DATA_RATE_75HZ:
			val = write_bit(val,2,0);
			val = write_bit(val,3,1);
			val = write_bit(val,4,1);
			break;
	}
	write8(i2c_dev,LSM303DLH_CRA_REG_M, val);
}

void LSM303DLH_M_setGain(int i2c_dev, int mode){
	write8(i2c_dev,LSM303DLH_CRB_REG_M, mode);
}

void LSM303DLH_M_setMode(int i2c_dev, int mode){
	write8(i2c_dev,LSM303DLH_MR_REG_M, mode);
}

int LSM303DLH_M_checkReady(int i2c_dev){
	return read_bit(read8(i2c_dev,LSM303DLH_SR_REG_M),0);
}

int LSM303DLH_M_checkLock(int i2c_dev){
	return read_bit(read8(i2c_dev,LSM303DLH_SR_REG_M),1);
}

int LSM303DLH_M_checkVoltRegu(int i2c_dev){
	return read_bit(read8(i2c_dev,LSM303DLH_SR_REG_M),2);
}

int LSM303DLH_M_readX(int i2c_dev){
	int d1=read8(i2c_dev,LSM303DLH_OUT_X_L_M); 
	int d2= read8(i2c_dev,LSM303DLH_OUT_X_H_M);
	int ret = (short)((d2 << 8) | d1);
	return ret;
}

int LSM303DLH_M_readY(int i2c_dev){
	int d1=read8(i2c_dev,LSM303DLH_OUT_Z_L_M); 
	int d2= read8(i2c_dev,LSM303DLH_OUT_Z_H_M);
	short ret = (short)((d2 << 8) | d1);
	return ret;
}

int LSM303DLH_M_readZ(int i2c_dev){
	int d1=read8(i2c_dev,LSM303DLH_OUT_Y_L_M); 
	int d2= read8(i2c_dev,LSM303DLH_OUT_Y_H_M);
	int ret = (short)((d2 << 8) | d1);
	return ret;
}
