#include <kipr/botball.h>
#include "omniDrive.h"
#include "camera.h"

#define CLAW_PORT 3
#define ARM_PORT 2
#define GRABBER_PORT 0
#define CLAW_CLOSED 850
#define CLAW_OPEN 1600
#define ARM_PICKUP 1900
#define ARM_DUMP 798
#define ARM_UP 1700
#define ARM_DOWN 2047
#define GRABBER_OPEN 0
#define GRABBER_CLOSED 900
#define LIGHT_LEFT 5
#define LIGHT_RIGHT 4

//if value < 200, it is on white, if value > 3000, it is on black

void line_follow();
void arm_pickup();
void arm_up();
void grabber_open();
void grabber_close();
void claw_open();
void claw_closed();

void line_follow(int dist) 
{
  cmpc(MOT_LEFT);
  cmpc(MOT_RIGHT);
  int lGoal = dist * CMtoBEMF * ANGLEADJUST;
  int rGoal = dist * CMtoBEMF * ANGLEADJUST;
          mav(MOT_RIGHT, MOT_RIGHT_SPEED);
          mav(MOT_LEFT, MOT_LEFT_SPEED);
        while(gmpc(MOT_LEFT)<lGoal && gmpc(MOT_RIGHT)<rGoal)
        {
          if(analog(LIGHT_RIGHT) < 1500 && analog(LIGHT_LEFT) < 1500)
          {
              mav(MOT_FRONT, 0);
          }
          else if(analog(LIGHT_RIGHT) > 1500)
          {
              while(analog(LIGHT_LEFT) < 1500)
              {
                  mav(MOT_FRONT, 200);
              }
          }
          else if (analog(LIGHT_LEFT) > 1500)
          {
              while(analog(LIGHT_RIGHT) < 1500)
              {
                  mav(MOT_FRONT, -200);
              }
          }
      }
}

void arm_pickup()
{
  set_servo_position(ARM_PORT, ARM_PICKUP);
}

void arm_up()
{
  set_servo_position(ARM_PORT,ARM_UP);
}

void grabber_open()
{
  set_servo_position(GRABBER_PORT,GRABBER_OPEN);
}

void grabber_close()
{
  set_servo_position(GRABBER_PORT,GRABBER_CLOSED);
}

void claw_open()  {  set_servo_position(CLAW_PORT, CLAW_OPEN);  }

void claw_close() {  set_servo_position(CLAW_PORT, CLAW_CLOSED);  }

int main()
{	
  	
  	clear_all_positions();
  	arm_up();
  	tempcameratestfunction();
      /*
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
  	//grabber_open();
  	
  	//drive to first group of poms
  	arm_pickup();
    move(83.82, FORWARD);
  	while(LIGHT_LEFT > 200 && LIGHT_RIGHT > 200)
    {
        if(LIGHT_RIGHT > 2600)
            move_at_speed(1, RIGHT, 200); 
        else if(LIGHT_LEFT > 2600)
            move_at_speed(1, LEFT, 200);
    }
  */
  	
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
    
  
  	disable_servos();*/
    /*
  	line_follow();
  	msleep(5000);
    */
    return 0;
}