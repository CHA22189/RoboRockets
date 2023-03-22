#!/usr/bin/python
import os, sys
import ctypes
KIPR=ctypes.CDLL("/usr/lib/libkipr.so")
greifer_zu = 23
greifer_offen = 2563
greifer_servo = 1
def main():
    while KIPR.WaitForLight(0):
        KIPR.motor_stop(120)
        KIPR.create_connect()
        startup(0, 10)
        startup(1, 30)
        move_to(1,400,40)
        move_to(0,720,25)
        servo(0,1800)
        KIPR.create_drive_direct(220, 220) 	
        KIPR.msleep(1000)
        KIPR.create_drive_direct(0, 0) 	
        move_to(1,1200,400)
        move_to(1,300,40)
        
        KIPR.create_drive_direct(110, 110) 	
        KIPR.msleep(1000)
        KIPR.create_drive_direct(0, 0) 	
        turn(90, False)
        KIPR.create_drive_direct(110, 110) 	
        KIPR.msleep(2000)
        KIPR.create_drive_direct(0, 0) 	
        turn(90, True)
        KIPR.create_drive_direct(110, 110) 	
        KIPR.msleep(2700)
        KIPR.create_drive_direct(0, 0) 	
        move_to(0,1350,10)
        servo(0,300)
        KIPR.msleep(2000)
        move_to(0,200,10)
        servo(0,1800)
        KIPR.msleep(2000)
        
    
    
    KIPR.create_stop()
    KIPR.create_disconnect()

def servo(serv, position):
    KIPR.enable_servos()
    KIPR.msleep(50)
    KIPR.set_servo_position(serv, position)
    KIPR.msleep(50)
    KIPR.disable_servos()
        
def startup(motor, speed):    
    while True:
        pos = KIPR.get_motor_position_counter(motor)
        KIPR.motor(motor,-speed)
        KIPR.msleep(200)
        if pos == KIPR.get_motor_position_counter(motor):
            KIPR.clear_motor_position_counter(motor)
            KIPR.motor(motor,0)
            break
def turn(degree, ccw):
    if ccw:
        degree2 = degree * 0.9
        KIPR.set_create_total_angle(0)
        while (KIPR.get_create_total_angle() < degree2):

            KIPR.create_drive_direct(-450,450)

        KIPR.create_stop()
    else:
        degree2 = degree * 0.9
        KIPR.set_create_total_angle(0)
        while (abs(KIPR.get_create_total_angle()) < degree2):

            KIPR.create_drive_direct(450,-450)

        KIPR.create_stop()
    
        
def move_to(motor, position, speed):
    if KIPR.get_motor_position_counter(motor) < position:
        while KIPR.get_motor_position_counter(motor) < position:
            KIPR.motor(motor, speed)
    else:
        while KIPR.get_motor_position_counter(motor) > position:
             KIPR.motor(motor, -speed)  
             KIPR.motor(motor,0)
            
def greifer_schliessen():
	KIPR.set_servo_position (greifer_servo, greifer_zu)
def greifer_oeffnen():
	KIPR.set_servo_position(greifer_servo, greifer_offen)
if __name__== "__main__":
    sys.stdout = os.fdopen(sys.stdout.fileno(),"w",0)
    main();
