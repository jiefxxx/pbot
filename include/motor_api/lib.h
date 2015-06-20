#ifndef DEF_MOTOR_API_LIB
#define DEF_MOTOR_API_LIB

#include <stdio.h>
#include <stdlib.h>

struct ms_control* get_controller();

void send_action(struct ms_control* data, int action);

int set_motor_rawValue(struct ms_control* data ,int motor, int value);
int set_motor_value(struct ms_control* data ,int motor, int value);
int set_motor_calMax(struct ms_control* data ,int motor, int value);
int set_motor_calMin(struct ms_control* data ,int motor, int value);
int get_motor_rawValue(struct ms_control* data, int motor);
int get_motor_value(struct ms_control* data, int motor);
int get_motor_calMax(struct ms_control* data, int motor);
int get_motor_calMin(struct ms_control* data, int motor);

int set_servo_rawValue(struct ms_control* data, int servo, int value);
int set_servo_value(struct ms_control* data, int servo, int value);
int set_servo_calMax(struct ms_control* data, int servo, int value);
int set_servo_calMin(struct ms_control* data, int servo, int value);
int get_servo_rawValue(struct ms_control* data, int servo);
int get_servo_value(struct ms_control* data, int servo);
int get_servo_calMax(struct ms_control* data, int servo);
int get_servo_calMin(struct ms_control* data, int servo);

void dump_motor(struct ms_control* data,int motor);
void dump_servo(struct ms_control* data,int servo);

#endif
