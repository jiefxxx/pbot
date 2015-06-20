#include <stdio.h>
#include <stdlib.h>
#include <tools/mapping.h>
#include <magn_api/type.h>
#include <i2c_dev/i2c_lsm303dlh_m.h>

struct magn_control* init_data(){
	struct magn_control* data = (struct magn_control*)get_memory_map(MS_MAP_PATH,sizeof(struct ms_magn));
	data->state=0;
	return data;
}

int init_magn_dev(){
	int magn_d = LSM303DLH_M_init(LSM303DLH_M_ID);
	LSM303DLH_M_setDataRate(magn_d,LSM303DLH_M_DATA_RATE_75HZ);
	LSM303DLH_M_setGain(magn_d,LSM303DLH_M_GAIN_1_3GAUSS);//set sensibility
	LSM303DLH_M_setMode(magn_d,LSM303DLH_M_CONTINUOUS_MODE);//continuous conversation
	return int;
}

int read_magn_dev(struct magn_control* magn_c,int magn_d){
	switch(magn_c->state){
		case:-1
			return -1;
		case:0
			return 0;
		case:1
			//get data from magn
			magn_c->val.x = LSM303DLH_M_readX(magn_d);
			magn_c->val.y = LSM303DLH_M_readY(magn_d);
			magn_c->val.z = LSM303DLH_M_readZ(magn_d);
			return 1;
		case:2
			magn_c->val.x = (LSM303DLH_M_readX(magn_d)+magn_c->valA.x)*magn_c->valB.x;
			magn_c->val.y = (LSM303DLH_M_readY(magn_d)+magn_c->valA.y)*magn_c->valB.y;
			magn_c->val.z = (LSM303DLH_M_readZ(magn_d)+magn_c->valA.z)*magn_c->valB.z;
			return 1;
		case:3
			magn_c->val.x = (magn_c->val.x*(100-magn_c->hoffman)/100)+
					((LSM303DLH_M_readX(magn_d)+magn_c->valA.x)*magn_c->valB.x*(100-magn_c->hoffman)/100);
			magn_c->val.y = (magn_c->val.y*(100-magn_c->hoffman)/100)+
					((LSM303DLH_M_readY(magn_d)+magn_c->valA.y)*magn_c->valB.y*(100-magn_c->hoffman)/100);
			magn_c->val.z = (magn_c->val.z*(100-magn_c->hoffman)/100)+
					((LSM303DLH_M_readZ(magn_d)+magn_c->valA.z)*magn_c->valB.z*(100-magn_c->hoffman)/100);
			return 1;
		default:
			magn_c->state = 0;
			return 0;
	}
}

int main(int argc, char *argv[]){
	struct magn_control* magn_c = init_data();
	int magn_d = init_magn_dev();
}
