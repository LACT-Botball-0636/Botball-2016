#include <kipr/botball.h>
#include "createDrive.h"

//Servo constants
#define SERV_ARM 3
#define ARM_DOWN 1700
#define ARM_UP 0
#define ARM_HIGHER 500
#define ARM_MIDDLE 800
#define ARM_FLOAT 1103

#define SERV_CLAW 1
#define CLAW_CLOSED 980
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
#define GRAB_SPEED -50
#define GRAB_OPEN 750

#define DEFAULT_SPEED 200

void arm_float()
{
  set_servo_position(SERV_ARM,ARM_FLOAT);
}
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
  set_servo_position(SERV_ELBOW,ELBOW_UP);
  set_servo_position(SERV_ARM,ARM_UP);
  msleep(500);
  set_servo_position(SERV_CLAW,CLAW_CLOSED+100);
  msleep(1000);
  
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
void init_pos()
{
  set_servo_position(SERV_ELBOW,ELBOW_UP);
  set_servo_position(SERV_SHOULDER,SHOULDER_UP);
  set_servo_position(SERV_ARM,470);
  claw_super_open();
}
void grabber_down()
{
  printf("%d\n",gmpc(MOT_GRAB));
  mav(MOT_GRAB,300);
  printf("%d\n",gmpc(MOT_GRAB));
  set_servo_position(SERV_SHOULDER,SHOULDER_DOWN);
  set_servo_position(SERV_ELBOW,ELBOW_DOWN);
}

void grabber_up()
{
  int elbowPositions[20] = {50,50, 50,50, 50,50, 65,65, 65,65, 65,65, 65,65, 100,100, 100,100, 100,100};
  printf("%d\n",gmpc(MOT_GRAB));
  mav(MOT_GRAB,-500);
  printf("%d\n",gmpc(MOT_GRAB));
  msleep(1250);
  mav(MOT_GRAB,GRAB_SPEED);
  int posShoulder = SHOULDER_DOWN;
  int posElbow = ELBOW_DOWN;
  int i;
  for(i = 0; i < 20;i++)
  {
    posShoulder-=90;
    set_servo_position(SERV_SHOULDER,posShoulder);
    posElbow+=elbowPositions[i];
    set_servo_position(SERV_ELBOW,posElbow);
    msleep(250);
  }
  set_servo_position(SERV_ELBOW,ELBOW_UP);
}
void grabber_down_slow()
{
  int elbowPositions[20] = {25,25, 25,25, 50,50, 50,50, 50,50, 50,50, 60,60, 130,130, 130,130, 140,140};
  set_servo_position(SERV_ELBOW,ELBOW_DOWN+(300+520+600));
  int posShoulder = SHOULDER_UP;
  int posElbow = ELBOW_DOWN+(300+520+600);
  int i;
  for(i = 19; i >= 0;i--)
  {
    posShoulder+=90;
    set_servo_position(SERV_SHOULDER,posShoulder);
    posElbow-=elbowPositions[i];
    set_servo_position(SERV_ELBOW,posElbow);
    msleep(250);
  }
}
int main()
{
  create_connect();
  cmpc(MOT_GRAB);
  printf("%d\n",gmpc(MOT_GRAB));
  //set servos to initial positions now
  init_pos();
  enable_servos();
  shut_down_in(119.9);
  printf("started");
  msleep(6000);

  //pile 1
  create_forward(60,DEFAULT_SPEED+50);
  create_line_follow(35,DEFAULT_SPEED+50);
  claw_open();
  msleep(500);
  create_right(30,200);
  create_drive_direct(-DEFAULT_SPEED/2,DEFAULT_SPEED/2);
  while(analog(RIGHT_LINE)<2500)
  {
    msleep(1);
  }
  create_stop();
  arm_down();
  msleep(1000);
  create_left(1,DEFAULT_SPEED/5);
  create_forward(13,DEFAULT_SPEED/5);
  claw_close();
  msleep(750);
  create_right(5,DEFAULT_SPEED/2);
  arm_middle();
  msleep(500);
  create_line_follow(48,DEFAULT_SPEED);
  create_right(90,DEFAULT_SPEED);
  create_backward(15,DEFAULT_SPEED/2);
  create_forward(5,DEFAULT_SPEED);
  create_right(80,DEFAULT_SPEED/2);
  
  //bin
  grabber_down();
  msleep(1000);
  create_backward(9,DEFAULT_SPEED/2);

  //pile 2
  grabber_up();
  create_right(10,DEFAULT_SPEED);
  create_forward(28,DEFAULT_SPEED);
  arm_up();
  create_left(90,DEFAULT_SPEED);
  claw_super_open();
  msleep(500);
  create_backward(18,DEFAULT_SPEED);
  create_forward(2,DEFAULT_SPEED);
  create_left(40,DEFAULT_SPEED);
  arm_down();
  msleep(1000);
  create_forward(5,DEFAULT_SPEED);
  msleep(250);
  claw_close();
  msleep(500);
  arm_middle();
  msleep(500);
  create_backward(5,DEFAULT_SPEED);
  create_right(40,DEFAULT_SPEED);
  create_backward(8,DEFAULT_SPEED);
  arm_up();
  create_forward(5,DEFAULT_SPEED);
  create_right(40,DEFAULT_SPEED);
  claw_open();
  create_backward(1,DEFAULT_SPEED);
  arm_down();
  msleep(1000);
  create_forward(8,DEFAULT_SPEED);
  //pile 3
  claw_close();
  msleep(500);
  create_backward(9,DEFAULT_SPEED);
  arm_up();
  //last pile
  set_servo_position(SERV_ELBOW,ELBOW_UP-(150));
  msleep(500);
  create_left(45,DEFAULT_SPEED);
  create_backward(20,DEFAULT_SPEED);
  create_forward(5,DEFAULT_SPEED);
  create_left(90,DEFAULT_SPEED);
  arm_middle();
  msleep(500);
  create_line_follow(20,DEFAULT_SPEED);
  create_right(180,DEFAULT_SPEED);
  create_drive_direct(DEFAULT_SPEED/2,-DEFAULT_SPEED/2);
  while(analog(LEFT_LINE)<2500)
  {
    msleep(1);
  }
  create_stop();
  create_backward(57,DEFAULT_SPEED);
  create_forward(5,DEFAULT_SPEED);
  create_left(90,DEFAULT_SPEED/2);
  create_backward(3,DEFAULT_SPEED);
  arm_down();
  claw_open();
  create_drive_direct(-DEFAULT_SPEED/2,DEFAULT_SPEED/2);
  while(analog(RIGHT_LINE)<2500);
  {
    msleep(1);
  }
  create_stop();
  create_left(6,DEFAULT_SPEED/2);
  msleep(500);
  create_forward(8,DEFAULT_SPEED/2);
  create_forward(15,DEFAULT_SPEED/5);
  claw_close();
  msleep(500);
  create_backward(1,DEFAULT_SPEED/2);
  msleep(500);
  create_right(3,DEFAULT_SPEED/5);
  arm_middle();
  create_line_follow(5,DEFAULT_SPEED);
  create_forward(10,DEFAULT_SPEED);
  while(analog(LEFT_LINE)<2500||analog(RIGHT_LINE)<2500)
  {
    create_drive_direct(DEFAULT_SPEED*2/3,DEFAULT_SPEED*2/3);
    if(analog(LEFT_LINE)>=2500)
    {
      create_drive_direct(0,DEFAULT_SPEED/2);
    }
    else if(analog(RIGHT_LINE)>=2500)
    {
      create_drive_direct(DEFAULT_SPEED/2,0);
    }
  }
  create_stop();
  create_forward(2,DEFAULT_SPEED);
  arm_up();
  set_servo_position(SERV_ELBOW,ELBOW_UP-(150));
  arm_middle();
  msleep(1000);
  create_backward(30,DEFAULT_SPEED);
  claw_open();
  arm_float();
  create_forward(15,DEFAULT_SPEED/2);
  create_stop();
  arm_down();
  msleep(250);
  claw_close();
  msleep(500);
  arm_middle();
  msleep(500);
  while(analog(LEFT_LINE)<2500||analog(RIGHT_LINE)<2500)
  {
    create_drive_direct(DEFAULT_SPEED/2,DEFAULT_SPEED/2);
    if(analog(LEFT_LINE)>=2500)
    {
      create_drive_direct(0,DEFAULT_SPEED/2);
    }
    else if(analog(RIGHT_LINE)>=2500)
    {
      create_drive_direct(DEFAULT_SPEED/2,0);
    }
  }
  create_stop();
  create_forward(2,DEFAULT_SPEED);
  arm_up();
  set_servo_position(SERV_ELBOW,ELBOW_UP-(150));
  create_forward(15,DEFAULT_SPEED);
  create_right(90,DEFAULT_SPEED);
  create_backward(20,DEFAULT_SPEED/2);
  set_servo_position(SERV_ARM,ARM_UP);
  msleep(1000);
  create_line_follow(15,DEFAULT_SPEED/2);
  create_left(45,DEFAULT_SPEED);
  msleep(500);
  set_servo_position(SERV_ARM,ARM_MIDDLE-150);
  msleep(500);
  set_servo_position(SERV_ARM,ARM_MIDDLE);
  msleep(500);
  create_right(90,DEFAULT_SPEED);
  set_servo_position(SERV_ARM,ARM_UP);
  create_drive_direct(-DEFAULT_SPEED,DEFAULT_SPEED);
  while(analog(RIGHT_LINE)<2500)
  {
    msleep(1);
  }
  create_stop();
  arm_float();
  claw_open();
  create_line_follow(25,DEFAULT_SPEED);
  arm_down();
  msleep(250);
  claw_close();
  msleep(500);
  arm_middle();
  msleep(500);
  arm_up();
  create_right(135,DEFAULT_SPEED);
  create_drive_direct(DEFAULT_SPEED/2,-DEFAULT_SPEED/2);
  while(analog(LEFT_LINE)<2500)
  {
    msleep(1);
  }
  create_stop();
  create_left(5,DEFAULT_SPEED);
  create_line_follow(30,DEFAULT_SPEED);
  create_right(180,DEFAULT_SPEED);
  create_drive_direct(DEFAULT_SPEED/2,-DEFAULT_SPEED/2);
  while(analog(LEFT_LINE)<2500)
  {
    msleep(1);
  }
  create_stop();
  create_backward(20,DEFAULT_SPEED/2);
  create_forward(5,DEFAULT_SPEED);
  create_left(97,DEFAULT_SPEED);
  arm_middle();
  while(analog(LEFT_LINE)<2500||analog(RIGHT_LINE)<2500)
  {
    create_drive_direct(-DEFAULT_SPEED*2/3,-DEFAULT_SPEED*2/3);
    if(analog(LEFT_LINE)>=2500)
    {
      create_drive_direct(0,-DEFAULT_SPEED/5);
    }
    else if(analog(RIGHT_LINE)>=2500)
    {
      create_drive_direct(-DEFAULT_SPEED/5,0);
    }
  }
  create_backward(65,DEFAULT_SPEED+100);
  create_right(140,DEFAULT_SPEED);
  create_forward(30,DEFAULT_SPEED);
  create_left(40,DEFAULT_SPEED);
  create_line_follow(90,DEFAULT_SPEED+100);
  create_left(193,DEFAULT_SPEED);
  grabber_down_slow();
  int counter = 0;
  while(1==1);
  {
    msleep(1000);
    counter++;
    printf("%d seconds unused\n",counter);
  }
  return 0;
}