#include <kipr/botball.h>
#include "camera.h"

/*
int blob_largest(int channel)
{
  int blobsize = 0;
  return get_object_area(channel,0);
}
*/
int blob_sum(int channel)
{
  int blobsize = 0;
  int i;
  for(i = 0; i < get_object_count(channel); i++)
    blobsize += get_object_area(channel, i);
  return blobsize;
}
/*
Location sum_center(int channel)
{
  int i;
  int leftmost;
  for(i = 0; i < get_object_count(); i++)
    i++;
  struct Location l;
  return l;
}
*/
void tempcameratestfunction()
{
  camera_open(LOW_RES);
  while(1==1) {
    camera_update();
    if(blob_sum(RED) > 500)
      printf("sees red");
    else
      printf("sees none");
  }
}