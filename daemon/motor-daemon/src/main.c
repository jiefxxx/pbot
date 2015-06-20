#include <stdio.h>
#include <stdlib.h>
#include <tools/mapping.h>
#include <tools/semaphore.h>
#include <motor_api/type.h>
#include <i2c_dev/i2c_pca9685.h>
#include <i2c_dev/i2c_mcp23008.h>

#define PWM_MOTOR_1		0xF
#define PWM_MOTOR_2		0XE
#define PWM_MOTOR_3		0XD
#define PWM_MOTOR_4		0XC

#define L2F 0x02
#define L2B 0x01
#define R2B 0x04
#define R2F 0x08
#define L1B 0X10
#define L1F 0x20
#define R1F 0x80
#define R1B 0x40

struct ms_control* init_data(){
	struct ms_control* data = (struct ms_control*)get_memory_map(MS_MAP_PATH,sizeof(struct ms_control));
	binary_semaphore_deallocate(data->semid);
	data->semid = binary_semaphore_allocation(MS_SEM, IPC_CREAT | IPC_EXCL | 0666);
	binary_semaphore_initialize(data->semid);
	
	data->state = 0;
	int i;
	for(i=0;i<MOTOR_COUNT;i++){
		data->motor[i].value = 0;
		data->motor[i].rawValue = 0;
	}
	for(i=0;i<SERVO_COUNT;i++){
		data->servo[i].value = 0;
		data->servo[i].rawValue = 0;
	}
	return data;
}

void release_data(struct ms_control* data){
	binary_semaphore_deallocate(data->semid);
	release_memory_map((void*)data,sizeof(struct ms_control));
}

void calc_data_motor(struct ms_control* data){
	int i;
	for(i=0;i<MOTOR_COUNT;i++){
		if (data->motor[i].value == 0){
			data->motor[i].rawValue=0;
		}
		if((data->motor[i].value > 0)&&(data->motor[i].value<=100)){
			data->motor[i].rawValue=data->motor[i].calMin+(data->motor[i].value*(data->motor[i].calMax-data->motor[i].calMin)/100);
		}
		if((data->motor[i].value < 0)&&(data->motor[i].value>=-100)){
			data->motor[i].rawValue=-1*(data->motor[i].calMin+(data->motor[i].value*-1*(data->motor[i].calMax-data->motor[i].calMin)/100));
		}
	}
	for(i=0;i<SERVO_COUNT;i++){
		if((data->servo[i].degMax-data->servo[i].degMin)!=0){
			data->servo[i].rawValue=data->servo[i].calMin+((data->servo[i].value-data->servo[i].degMin)*(data->servo[i].calMax-data->servo[i].calMin)/(data->servo[i].degMax-data->servo[i].degMin));
		}
	}
}

void aply_data_motor(struct ms_control* data,int gpio,int pwm){
	int ret = 0;
	int motor_map[3][4];
	motor_map[0][0]=L1F;
	motor_map[0][1]=R1F;
	motor_map[0][2]=L2F;
	motor_map[0][3]=R2F;
	motor_map[1][0]=L1B;
	motor_map[1][1]=R1B;
	motor_map[1][2]=L2B;
	motor_map[1][3]=R2B;
	motor_map[2][0]=PWM_MOTOR_1;
	motor_map[2][1]=PWM_MOTOR_2;
	motor_map[2][2]=PWM_MOTOR_3;
	motor_map[2][3]=PWM_MOTOR_4;
	int i;
	for(i=0;i<MOTOR_COUNT;i++){
		if (data->motor[i].rawValue == 0){
			PCA9685_setPwm(pwm,motor_map[2][i],0,0);
		}
		if(data->motor[i].rawValue > 0){
			PCA9685_setPwm(pwm,motor_map[2][i],0,data->motor[i].rawValue);
			ret = ret|motor_map[0][i];
		}
		if(data->motor[i].value < 0){
			PCA9685_setPwm(pwm,motor_map[2][i],0,(data->motor[i].rawValue*-1));
			ret = ret|motor_map[1][i];
		}
	}
	MCP23008_write_all(gpio,ret);
	for(i=0;i<SERVO_COUNT;i++){
		PCA9685_setPwm(pwm,i,0,data->servo[i].rawValue);
	}
}

void init_gpio_extend(int gpio){
	MCP23008_setup(gpio,0,OUTPUT);
	MCP23008_setup(gpio,1,OUTPUT);
	MCP23008_setup(gpio,2,OUTPUT);
	MCP23008_setup(gpio,3,OUTPUT);
	MCP23008_setup(gpio,4,OUTPUT);
	MCP23008_setup(gpio,5,OUTPUT);
	MCP23008_setup(gpio,6,OUTPUT);
	MCP23008_setup(gpio,7,OUTPUT);
	MCP23008_write_all(gpio,0);
}
void init_pwm(int pwm){
	PCA9685_start(pwm);
	PCA9685_setAllPwm(pwm,0,0);
}

int main(int argc, char *argv[]){
	struct ms_control* data_ctrl = init_data();
	
	int gpio;
	int pwm;
	
	gpio = MCP23008_init(0x20);
	init_gpio_extend(gpio);
	
	pwm = PCA9685_init(0x40);
	init_pwm(pwm);
	
	while(1){
		printf("wait data\n");
		binary_semaphore_wait(data_ctrl->semid);
		switch(data_ctrl->state){
			case -1:
				MCP23008_write_all(gpio,0);
				PCA9685_setAllPwm(pwm,0,0);
				printf("close \n");
				release_data(data_ctrl);
				return 0;
			case 0:
				MCP23008_write_all(gpio,0);
				PCA9685_setAllPwm(pwm,0,0);
				data_ctrl = init_data();
				printf("systeme in pause \n");
				break;
			case 1:
				aply_data_motor(data_ctrl,gpio,pwm);
				printf("addapt data \n");
				break;
			case 2:
				calc_data_motor(data_ctrl);
				aply_data_motor(data_ctrl,gpio,pwm);
				printf("calcul data \n");
				break;
		}
	}
}
