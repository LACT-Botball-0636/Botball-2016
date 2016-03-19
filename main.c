#include <kipr/botball.h>
#include "omniDrive.h"
#include "camera.h"

#define CLAW_PORT 3
#define ARM_PORT 2
#define GRABBER_PORT 0
#define CLAW_CLOSED 850
#define CLAW_OPEN 1600
#define ARM_PICKUP 1850
#define ARM_DUMP 798
#define ARM_UP 800
#define ARM_DOWN 2047
#define GRABBER_OPEN 0
#define GRABBER_CLOSED 2047
#define LIGHT_LEFT 5
#define LIGHT_RIGHT 4

//if value < 200, it is on white, if value > 3000, it is on black

void arm_pickup();
void arm_up();
void arm_dump();
void arm_down();
void grabber_open();
void grabber_close();
void claw_open();
void claw_close();
void straighten();

void arm_pickup()
{
  set_servo_position(ARM_PORT, ARM_PICKUP);
  msleep(500);
}

void arm_down()
{
  set_servo_position(ARM_PORT, ARM_DOWN);
  msleep(500);
}

void arm_up()
{
  set_servo_position(ARM_PORT,ARM_UP+600);
  msleep(3000);
  set_servo_position(ARM_PORT,ARM_UP);
  msleep(3000);
}

void arm_dump()
{
  set_servo_position(ARM_PORT,ARM_DUMP);
  msleep(500);
}

void grabber_open()
{
  set_servo_position(GRABBER_PORT,GRABBER_OPEN);
  msleep(500);
}

void grabber_close()
{
  set_servo_position(GRABBER_PORT,GRABBER_CLOSED);
  msleep(1500);
}

void claw_open()  {  set_servo_position(CLAW_PORT, CLAW_OPEN);  }

void claw_close() {  set_servo_position(CLAW_PORT, CLAW_CLOSED);  }

int main()
{	
  	enable_servos();
  	arm_dump(); //DO NOT COMMENT OUT
  	msleep(200);
  
  	claw_open();
  	//arm_down();
  	//move(30,0);
    straighten();
    line_follow(99999);
  	msleep(3000);
  	claw_close();
  	msleep(2000);
  	arm_up();
  /*
  	grabber_open();
  	msleep(200);
  	move(30,180);
  	grabber_close();
  	arm_up();
  	msleep(200);
  
  */
  
  	/*
  	clear_all_positions();
  	arm_up();
  	tempcameratestfunction();
    
  	mtp(2, 800, 1400);
  	msleep(8000);
  	
  	//initialize servos
  	grabber_close();
  	arm_pickup();
  	claw_close();
  	enable_servos();
  	
  	//push arm to knock down compost
  	arm_up();
  	msleep(500);
  	claw_open();
  	//grabber_open();*/
  	
  	//drive to first group of poms
  	//arm_pickup();
  
  
    //move(83.82, FORWARD);
  	//straighten();
  
  
  	
  	/*claw_close(); //pick up poms
  	msleep(500);
  	arm_up();
  
  	//turn around an go towards potato bin
	right(180);
  	grabber_open();
	move(55, BACKWARD);
  
  	//grab potato bin
  	grabber_close();
  	move(10, LEFT);
  	left(90);
  	move(45.72, BACKWARD);
  	right(116);
  	move(49.53, FORWARD);
  	left(125);
  	move(50.8, FORWARD);
    right(74);
  	move(60, FORWARD);
    
  */
  	disable_servos();
  	//line_follow(99999);
  	msleep(5000);
    return 0;
}