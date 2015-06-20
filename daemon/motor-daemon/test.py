#!/usr/bin/env python
# -*- coding: utf-8 -*-

from motor_api import *
import time

LEFT_BACK_WHEEL = 0
LEFT_FRONT_WHEEL = 1
RIGHT_BACK_WHEEL = 2
RIGHT_FRONT_WHEEL = 3

CAMERA_PITCH = 10
CAMERA_YAW = 11

APPLY_STOP = -1
APPLY_INIT = 0
APPLY_RAW = 1
APPLY_VALUE = 2

def stop_daemon():
	send_action(get_controller(),APPLY_STOP)
	time.sleep(0.1)
	
def rinit_daemon():
	send_action(get_controller(),APPLY_INIT)
	time.sleep(0.1)
	
class Motor:
	def __init__(self):
		self.ctrl = get_controller()
	
	def set_default_cal(self):
		set_motor_calMax(self.ctrl,-1,4096)
		set_motor_calMin(self.ctrl,-1,800)
		
	def prep_value(self,id,value):
		set_motor_value(self.ctrl,id,value)
	
	def get_value(self,id):
		return get_motor_value(self.ctrl,id)
	
	def prep_raw(self,id,raw):
		set_motor_rawValue(self.ctrl,id,raw)
	
	def get_raw(self,id):
		return get_motor_rawValue(self.ctrl,id)
	
	def apply(self,type):
		send_action(self.ctrl,type)
	
	def set_value(self,id,value):
		self.prep_value(id,value)
		self.apply(APPLY_VALUE)
		
	def set_raw(self,id,raw):
		self.prep_raw(id,raw)
		self.apply(APPLY_RAW)
		
	def set_all(self,val_LB,val_RB,val_LF,val_RF):
		self.prep_value(LEFT_BACK_WHEEL,val_LB)
		self.prep_value(LEFT_FRONT_WHEEL,val_LF)
		self.prep_value(RIGHT_BACK_WHEEL,val_RB)
		self.prep_value(RIGHT_FRONT_WHEEL,val_RF)
		self.apply(APPLY_VALUE)
		
	def increment_all(self,val_LB,val_RB,val_LF,val_RF):
		self.set_all(self.get_value(LEFT_BACK_WHEEL)+val_LB,
				self.get_value(RIGHT_BACK_WHEEL)+val_RB,
				self.get_value(LEFT_FRONT_WHEEL)+val_LF,
				self.get_value(RIGHT_FRONT_WHEEL)+val_RF)
	
	def set_all_raw(self,val_LB,val_RB,val_LF,val_RF):
		self.prep_value(LEFT_BACK_WHEEL,val_LB)
		self.prep_value(LEFT_FRONT_WHEEL,val_LF)
		self.prep_value(RIGHT_BACK_WHEEL,val_RB)
		self.prep_value(RIGHT_FRONT_WHEEL,val_RF)
		self.apply(APPLY_VALUE)
	
	def dump(self):
		dump_motor(ctrl,-1)

class Servo:
	def __init__(self):
		self.ctrl = get_controller()
	
	def set_default_cal(self):
		set_servo_calMin(self.ctrl,CAMERA_YAW,490)
		set_servo_calMax(self.ctrl,CAMERA_YAW,2100)
		set_servo_degMin(self.ctrl,CAMERA_YAW,-90)
		set_servo_degMax(self.ctrl,CAMERA_YAW,+90)


		set_servo_calMin(self.ctrl,CAMERA_PITCH,470)
		set_servo_calMax(self.ctrl,CAMERA_PITCH,1700)
		set_servo_degMin(self.ctrl,CAMERA_PITCH,-90)
		set_servo_degMax(self.ctrl,CAMERA_PITCH,+45)
		
	def prep_value(self,id,value):
		set_servo_value(self.ctrl,id,value)
	
	def get_value(self,id):
		return get_servo_value(self.ctrl,id)
	
	def prep_raw(self,id,raw):
		set_servo_rawValue(self.ctrl,id,raw)
	
	def get_raw(self,id):
		return get_servo_rawValue(self.ctrl,id)
	
	def apply(self,type):
		send_action(self.ctrl,type)
		
	def set_camera(self,pitch,yaw):
		self.prep_value(CAMERA_YAW,yaw)
		self.prep_value(CAMERA_PITCH,pitch)
		self.apply(APPLY_VALUE)

m = Motor()
s = Servo()
m.set_default_cal()
s.set_default_cal()

s.set_camera(0,0)
m.set_all(10,10,10,10)

time.sleep(2)

s.set_camera(25,0)
m.increment_all(0,0,10,10)
m.increment_all(20,20,10,10)

time.sleep(2)

m.increment_all(0,0,10,10)
s.set_camera(0,80)

time.sleep(2)

rinit_daemon()



