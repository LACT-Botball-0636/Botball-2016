#include <kipr/botball.h>
#include "createDrive.h"

//Servo constants
#define SERV_ARM 3
#define ARM_DOWN 1700
#define ARM_UP 280
#define ARM_MIDDLE 1000

#define SERV_CLAW 1
#define CLAW_CLOSED 900
#define CLAW_OPEN 1601
#define CLAW_SUPER_OPEN 2047

#define SERV_SHOULDER 0
#define SHOULDER_DOWN 1800
#define SHOULDER_MIDDLE 900
#define SHOULDER_UP 0

#define SERV_ELBOW 2
#define ELBOW_DOWN 0
#define ELBOW_MIDDLE 800
#define ELBOW_UP 1600

//Motor constants
#define MOT_GRAB 0
#define GRAB_SPEED -100
#define GRAB_OPEN 750

#define DEFAULT_SPEED 200

void arm_down()
{
  set_servo_position(SERV_ARM,ARM_DOWN);
}
void arm_middle()
{
  set_servo_position(SERV_ARM,ARM_MIDDLE);
}
void arm_up()
{
  set_servo_position(SERV_ARM,ARM_UP);
}
void init_pos()
{
  set_servo_position(SERV_ELBOW,ELBOW_UP);
  set_servo_position(SERV_SHOULDER,SHOULDER_UP);
  arm_up();
}
void claw_open()
{
  set_servo_position(SERV_CLAW,CLAW_OPEN);
}
void claw_close()
{
  set_servo_position(SERV_CLAW,CLAW_CLOSED);
}
void claw_super_open()
{
  set_servo_position(SERV_CLAW,CLAW_SUPER_OPEN);
}
void grabber_down()
{
  printf("%d\n",gmpc(MOT_GRAB));
  mtp(MOT_GRAB,500,GRAB_OPEN);
  printf("%d\n",gmpc(MOT_GRAB));
  set_servo_position(SERV_SHOULDER,SHOULDER_DOWN);
  set_servo_position(SERV_ELBOW,ELBOW_DOWN);
}

void grabber_up()
{
  printf("%d\n",gmpc(MOT_GRAB));
  mtp(MOT_GRAB,1000,-500);
  printf("%d\n",gmpc(MOT_GRAB));
  msleep(1000);
  mav(MOT_GRAB,GRAB_SPEED);
  msleep(2000);
  int posShoulder = SHOULDER_DOWN;
  int posElbow = ELBOW_DOWN;
  int i;
  for(i = 0; i < 10;i++)
  {
    posShoulder-=180;
    set_servo_position(SERV_SHOULDER,posShoulder);
    posElbow+=160;
    set_servo_position(SERV_ELBOW,posElbow);
    msleep(750);
  }
  /*
    set_servo_position(SERV_SHOULDER,SHOULDER_MIDDLE);
  set_servo_position(SERV_ELBOW,ELBOW_MIDDLE);
  msleep(1000);
  set_servo_position(SERV_SHOULDER,SHOULDER_UP);
  set_servo_position(SERV_ELBOW,ELBOW_UP);
  msleep(1000);*/
}
int main()
{
  /* test code
  arm_down();
  claw_close();
  enable_servos();
  cmpc(MOT_GRAB);
  grabber_down();
  grabber_up();
  arm_up();
  printf("done");
  while(1==1)
  {
    msleep(1);
  }
  */
  create_connect();
  cmpc(MOT_GRAB);
  printf("%d\n",gmpc(MOT_GRAB));
  //set servos to initial positions now
  init_pos();
  enable_servos();
  printf("started");

  //pile 1
  create_forward(60,DEFAULT_SPEED);
  msleep(500);
  create_line_follow(35,DEFAULT_SPEED);
  claw_open();
  msleep(500);
  create_right(30,200);
  create_drive_direct(-50,50);
  while(analog(RIGHT_LINE)<2500)
  {
    msleep(1);
  }
  create_stop();
  arm_down();
  msleep(1000);
  create_forward(13,DEFAULT_SPEED/8);
  claw_close();
  msleep(500);
  create_right(5,DEFAULT_SPEED/2);
  arm_middle();
  create_line_follow(24,DEFAULT_SPEED);
  create_left(90,DEFAULT_SPEED/2);
  while(analog(LEFT_LINE)<2500||analog(RIGHT_LINE)<2500)
  {
    create_drive_direct(-DEFAULT_SPEED/5,-DEFAULT_SPEED/5);
    if(analog(LEFT_LINE)>=2500)
    {
      create_drive_direct(0,-DEFAULT_SPEED/5);
    }
    else if(analog(RIGHT_LINE)>=2500)
    {
      create_drive_direct(-DEFAULT_SPEED/5,0);
    }
  }
  create_stop();
  create_forward(12,DEFAULT_SPEED/2);
  create_right(90,DEFAULT_SPEED/2);
  //bin
  create_line_follow(12,DEFAULT_SPEED);
  create_left(215,DEFAULT_SPEED);
  grabber_down();
  msleep(1000);
  create_backward(8,DEFAULT_SPEED/2);

  //pile 2
  grabber_up();
  arm_up();
  msleep(500);
  create_left(90,DEFAULT_SPEED);
  claw_super_open();
  msleep(500);
  create_backward(15,DEFAULT_SPEED);
  arm_down();
  msleep(1000);
  create_forward(10,DEFAULT_SPEED);
  claw_close();
  msleep(500);
  arm_middle();
  msleep(500);
  create_backward(20,DEFAULT_SPEED);
  arm_up();
  msleep(500);
  create_forward(5,DEFAULT_SPEED);
  create_right(62,DEFAULT_SPEED);
  claw_open();
  arm_down();
  msleep(500);
  //pile 3
  create_forward(25,DEFAULT_SPEED);
  claw_close();
  msleep(500);
  arm_up();
  msleep(500);
  //last pile
  create_left(70,DEFAULT_SPEED);
  create_backward(30,DEFAULT_SPEED);
  create_forward(5,DEFAULT_SPEED);
  create_left(90,DEFAULT_SPEED);
  create_line_follow(30,DEFAULT_SPEED);
  create_forward(30,DEFAULT_SPEED);
  create_right(90,DEFAULT_SPEED);
  create_line_follow(15,DEFAULT_SPEED);
  arm_down();
  claw_open();
  msleep(500);
  create_left(5,DEFAULT_SPEED);
  create_forward(12,DEFAULT_SPEED);
  claw_close();
  create_right(10,DEFAULT_SPEED);
  arm_up();
  create_line_follow(20,DEFAULT_SPEED);
  
  
  //pile 4
  return 0;
}