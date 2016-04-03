#include "createDrive.h"
#include <math.h>

void create_line_follow(int dist, int speed)
{
  dist*=10;
  set_create_distance(0);
  create_drive_straight(speed);
  while(abs(get_create_distance())<abs(dist))
  {
    if(analog(LEFT_LINE)>2500)
    {
      create_drive_direct(speed*.75,speed*1.25);
    }
    else if(analog(RIGHT_LINE)>2500)
    {
      create_drive_direct(speed*1.25,speed*.75);
    }
    else
    {
      create_drive_straight(speed);
    }
    msleep(5);
  }
  create_stop();
}

void create_forward(int dist, int speed)
{
  dist*=10;
  set_create_distance(0);
  create_drive_straight(speed);
  while(get_create_distance()<dist)
  {
    msleep(1);
  }
  create_stop();
}

void create_backward(int dist, int speed)
{
  dist*=10;
  set_create_distance(0);
  create_drive_straight(-speed);
  while(get_create_distance()>-dist)
  {
    msleep(1);
  }
  create_stop();
}

void create_left(int degrees, int speed)
{
  set_create_total_angle(0);
  create_drive_direct(-speed,speed);
  while(get_create_total_angle()<degrees)
  {
    msleep(5);
  }
  create_stop();
}

void create_right(int degrees, int speed)
{
  set_create_total_angle(0);
  create_drive_direct(speed,-speed);
  while(get_create_total_angle()>-degrees)
  {
    msleep(5);
  }
  create_stop();
}