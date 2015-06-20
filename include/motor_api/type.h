#ifndef DEF_MOTOR_API_DATA
#define DEF_MOTOR_API_DATA


#define MS_MAP_PATH "/home/jief/robot_api/map/motor_api.map"
#define MS_SEM 666
#define MOTOR_COUNT 4
#define SERVO_COUNT 12
#define MAX_RAW_VAL 4096

struct ms_data{
	int value;
	int calMax;
	int calMin;
	int rawValue;
	int degMax;
	int degMin;
};

struct ms_control{
	int semid;
	int state;
	struct ms_data motor[MOTOR_COUNT];
	struct ms_data servo[SERVO_COUNT];
};

#endif
