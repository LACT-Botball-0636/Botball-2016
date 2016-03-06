#include <kipr/botball.h>
#include "omniDrive.h"
#define CLAW_PORT 3
#define ARM_PORT 2
#define GRABBER_PORT 0
#define CLAW_CLOSED 960
#define CLAW_OPEN 1665
#define ARM_PICKUP 2012
#define ARM_DUMP 798
#define ARM_UP 1144
#define GRABBER_OPEN 0
#define GRABBER_CLOSED 900

void arm_up()
{
  set_servo_position(2,ARM_UP);
}

void grabber_open()
{
  set_servo_position(0,GRABBER_OPEN);
}

void grabber_close()
{
  set_servo_position(0,GRABBER_CLOSED);
}

int main()
{	
  	/*
  	clear_all_positions();
  	mtp(2, 800, 1400);
  	msleep(8000);
    */
  	enable_servos();
  	arm_up();
  	grabber_open();
  	
    move(80.645, FORWARD);
	right(180);
	move(55, BACKWARD);
  	grabber_close();
  	//servo code to lift the box up here
  	right(90);
  	move(45.72, BACKWARD);
  	right(116);
  	move(49.53, FORWARD);
  	left(125);
  	move(50.8, FORWARD);
    right(74);
  	move(60, FORWARD);
    
  
  	disable_servos();
    return 0;
}