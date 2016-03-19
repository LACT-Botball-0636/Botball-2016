#include <kipr/botball.h>
#include "camera.h"

#define MIN_THRESHOLD 500

int blob_largest(int channel)
{
  return get_object_area(channel,0);
}
int blob_sum(int channel)
{
  int blobsize = 0;
  int i;
  for(i = 0; i < get_object_count(channel); i++)
    blobsize += get_object_area(channel, i);
  return blobsize;
}
struct Location sum_center(int channel)
{

  //printf("%d",curr_time());
  camera_update();
  int i;
  int leftMost = 0;
  int topMost = 0;
  int rightMost = 0;
  int bottomMost = 0;
  if(get_object_count(channel)>0)
  {
    if(get_object_area(channel, 0) > MIN_THRESHOLD)
    {
      leftMost = get_object_center_x(channel, 0);
      rightMost = get_object_center_x(channel, 0);
      topMost = get_object_center_y(channel, 0);
      bottomMost = get_object_center_y(channel, 0);
    }
  }
  int xPos = leftMost;
  int yPos = rightMost;
  for(i = 0; i < get_object_count(channel); i++)
  {
    if(get_object_area(channel, i)>MIN_THRESHOLD)
    {
      xPos = get_object_center_x(channel, i);
      yPos = get_object_center_y(channel, i);
      if(leftMost > xPos)
        leftMost = xPos;
      if(rightMost < xPos)
        rightMost = xPos;
      if(topMost > yPos)
        topMost = yPos;
      if(bottomMost < yPos)
        bottomMost = yPos;
    }
  }
  struct Location l;
  l.x = (leftMost + rightMost) / 2;
  l.y = (topMost + bottomMost) / 2;
  printf("x: %d, y: %d\n",l.x,l.y);
  return l;
  //printf("%d",curr_time());
}
void tempcameratestfunction()
{
  camera_open(LOW_RES);
  struct Location l;
  while(1==1) {
    l = sum_center(RED);
    msleep(1000);
  }
}