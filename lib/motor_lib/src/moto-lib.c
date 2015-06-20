#include <motor_api/lib.h>
#include <tools/mapping.h>
#include <tools/semaphore.h>
#include <motor_api/type.h>

struct ms_control* get_controller(){
	struct ms_control* data = (struct ms_control*)get_memory_map(MS_MAP_PATH,sizeof(struct ms_control));
	return data;
}

void send_action(struct ms_control* data, int action){
	data->state = action;
	binary_semaphore_post(data->semid);
	if(action == -1){
		release_memory_map((void*)data,sizeof(struct ms_control));
	}
}


int set_motor_rawValue(struct ms_control* data ,int motor, int value){
	if(motor>MOTOR_COUNT)return -1;
	if((value<(MAX_RAW_VAL)*-1)||(value>MAX_RAW_VAL))return -2;
	if(motor<0){
		int i;
		for(i=0;i<MOTOR_COUNT;i++){
			data->motor[i].rawValue = value;
		}
		return 0;
	}
	data->motor[motor].rawValue = value;
	return 0;
}
int set_motor_value(struct ms_control* data ,int motor, int value){
	if(motor>MOTOR_COUNT)return -1;
	if((value<(100)*-1)||(value>100))return -2;
	if(motor<0){
		int i;
		for(i=0;i<MOTOR_COUNT;i++){
			data->motor[i].value = value;
		}
		return 0;
	}
	data->motor[motor].value = value;
	return 0;
}
int set_motor_calMax(struct ms_control* data ,int motor, int value){
	if(motor>MOTOR_COUNT)return -1;
	if((value<0)||(value>MAX_RAW_VAL))return -2;
	if(motor<0){
		int i;
		for(i=0;i<MOTOR_COUNT;i++){
			data->motor[i].calMax = value;
		}
		return 0;
	}
	data->motor[motor].calMax = value;
	return 0;
}
int set_motor_calMin(struct ms_control* data ,int motor, int value){
	if(motor>MOTOR_COUNT)return -1;
	if((value<0)||(value>MAX_RAW_VAL))return -2;
	if(motor<0){
		int i;
		for(i=0;i<MOTOR_COUNT;i++){
			data->motor[i].calMin = value;
		}
		return 0;
	}
	data->motor[motor].calMin = value;
	return 0;
}
int get_motor_rawValue(struct ms_control* data, int motor){
	if(motor>MOTOR_COUNT)return 0;
	return data->motor[motor].rawValue;
}
int get_motor_value(struct ms_control* data, int motor){
	if(motor>MOTOR_COUNT)return 0;
	return data->motor[motor].value;
}
int get_motor_calMax(struct ms_control* data, int motor){
	if(motor>MOTOR_COUNT)return 0;
	return data->motor[motor].calMax;
}
int get_motor_calMin(struct ms_control* data, int motor){
	if(motor>MOTOR_COUNT)return 0;
	return data->motor[motor].calMin;
}
int get_motor_degMax(struct ms_control* data, int motor){
	if(motor>MOTOR_COUNT)return 0;
	return data->motor[motor].calMax;
}
int get_motor_degMin(struct ms_control* data, int motor){
	if(motor>MOTOR_COUNT)return 0;
	return data->motor[motor].calMin;
}


int set_servo_rawValue(struct ms_control* data, int servo, int value){
	if(servo>SERVO_COUNT)return -1;
	if((value<(MAX_RAW_VAL)*-1)||(value>MAX_RAW_VAL))return -2;
	if(servo<0){
		int i;
		for(i=0;i<SERVO_COUNT;i++){
			data->servo[i].rawValue = value;
		}
		return 0;
	}
	data->servo[servo].rawValue = value;
	return 0;
}
int set_servo_value(struct ms_control* data, int servo, int value){
	if(servo>SERVO_COUNT)return -1;
	if((value<(180)*-1)||(value>180))return -2;
	if(servo<0){
		int i;
		for(i=0;i<SERVO_COUNT;i++){
			data->servo[i].value = value;
		}
		return 0;
	}
	data->servo[servo].value = value;
	return 0;
}
int set_servo_calMax(struct ms_control* data, int servo, int value){
	if(servo>SERVO_COUNT)return -1;
	if((value<0)||(value>MAX_RAW_VAL))return -2;
	if(servo<0){
		int i;
		for(i=0;i<SERVO_COUNT;i++){
			data->servo[i].calMax = value;
		}
		return 0;
	}
	data->servo[servo].calMax = value;
	return 0;
}
int set_servo_calMin(struct ms_control* data, int servo, int value){
	if(servo>SERVO_COUNT)return -1;
	if((value<0)||(value>MAX_RAW_VAL))return -2;
	if(servo<0){
		int i;
		for(i=0;i<SERVO_COUNT;i++){
			data->servo[i].calMin = value;
		}
		return 0;
	}
	data->servo[servo].calMin = value;
	return 0;
}
int set_servo_degMax(struct ms_control* data, int servo, int value){
	if(servo<0){
		int i;
		for(i=0;i<SERVO_COUNT;i++){
			data->servo[i].degMax = value;
		}
		return i;
	}
	data->servo[servo].degMax = value;
	return 1;
}
int set_servo_degMin(struct ms_control* data, int servo, int value){
	if(servo<0){
		int i;
		for(i=0;i<SERVO_COUNT;i++){
			data->servo[i].degMin = value;
		}
		return 0;
	}
	data->servo[servo].degMin = value;
	return 0;
}
int get_servo_rawValue(struct ms_control* data, int servo){
	if(servo>SERVO_COUNT)return 0;
	return data->servo[servo].rawValue;
}
int get_servo_value(struct ms_control* data, int servo){
	if(servo>SERVO_COUNT)return 0;
	return data->servo[servo].value;
}
int get_servo_calMax(struct ms_control* data, int servo){
	if(servo>SERVO_COUNT)return 0;
	return data->servo[servo].calMax;
}
int get_servo_calMin(struct ms_control* data, int servo){
	if(servo>SERVO_COUNT)return 0;
	return data->servo[servo].calMin;
}
int get_servo_degMax(struct ms_control* data, int servo){
	if(servo>SERVO_COUNT)return 0;
	return data->servo[servo].degMax;
}
int get_servo_degMin(struct ms_control* data, int servo){
	if(servo>SERVO_COUNT)return 0;
	return data->servo[servo].degMin;
}
void dump_motor(struct ms_control* data,int motor){
	if(motor<0){
		int i;
		for(i=0;i<MOTOR_COUNT;i++){
			printf("[%i]calMax:%i calMin:%i val:%i rawVal:%i\n",
				i,
				get_motor_calMax(data,i),
				get_motor_calMin(data,i),
				get_motor_value(data,i),
				get_motor_rawValue(data,i));
		}
		return;
	}
	printf("[%i]calMax:%i calMin:%i val:%i rawVal:%i\n",
				motor,
				get_motor_calMax(data,motor),
				get_motor_calMin(data,motor),
				get_motor_value(data,motor),
				get_motor_rawValue(data,motor));
}
void dump_servo(struct ms_control* data,int servo){
	if(servo<0){
		int i;
		for(i=0;i<SERVO_COUNT;i++){
			printf("[%i]calMax:%i degMax:%i calMin:%i degMin:%i val:%i rawVal:%i\n",
				i,
				get_servo_calMax(data,i),
				get_servo_degMax(data,i),
				get_servo_calMin(data,i),
				get_servo_degMin(data,i),
				get_servo_value(data,i),
				get_servo_rawValue(data,i));
		}
		return;
	}
	printf("[%i]calMax:%i degMax:%i calMin:%i degMin:%i val:%i rawVal:%i\n",
				servo,
				get_servo_calMax(data,servo),
				get_servo_degMax(data,servo),
				get_servo_calMin(data,servo),
				get_servo_degMin(data,servo),
				get_servo_value(data,servo),
				get_servo_rawValue(data,servo));
}

