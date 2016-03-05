#include <kipr/botball.h>
#include "omniDrive.h"

//Drives forward dist in cm, towards direction degrees starting at 12:00 going clockwise
//Split into 3 segments. 1st segment sets up constants and flips 
void forward(float dist, int direction) {
  //Stop movement and clear positions
  ao();
  clear_all_positions();
  //Constants and stuff
  int leftPos = gmpc(MOT_LEFT);
  int rightPos = gmpc(MOT_RIGHT);
  int frontPos = gmpc(MOT_FRONT);
  int leftGoal = 0;
  int rightGoal = 0;
  int frontGoal = 0;
  int reversed = 1;
  direction = (direction + 360)%360;
  if(direction < 0) {
    reversed = -1;
    direction *= -1;
  }
  
  //Imagine this as a huge if else statement where condition is direction == case. Target and initial speeds set here.
  switch(direction) {
    case FORWARD:
  	  mav(MOT_LEFT, MOT_LEFT_SPEED);
      mav(MOT_RIGHT, MOT_RIGHT_SPEED);
      leftGoal = dist * CMtoBEMF * ANGLEADJUST;
      rightGoal = dist * CMtoBEMF * ANGLEADJUST;
    case 120:
    
    case 240:
      
    case 30:
      
    case 60:
      
    case 90: 
      
    default:
      
  }
  
  //Wait until conditions met
  while(abs(gmpc(MOT_LEFT))) < abs(leftGoal) || abs(gmpc(MOT_RIGHT))) < abs(rightGoal) || abs(gmpc(MOT_FRONT))) < abs(frontGoal)) {
    
  }
}

//In place turn for degrees amount of degrees. Negative values turn left.
void right(float degrees) {
  float dist = degrees*ROBOTRADIUS*M_PI/180;
  //turn motor by turn_wheel_deg degrees
  float turn_wheel_deg = degrees*ROBOTRADIUS/WHEELRADIUS
  mav(MOT_FRONT, 200);
  mav(MOT_RIGHT, 200);
  mav(MOT_LEFT, 200);
}

//In place turn for degrees amount of degrees. Negative values turn right.
void left(float degrees) {
  
}

//Does forward but backward.
void backward(float dist, int direction) {
  
}

//Clears positions from all motors.
void clear_all_positions() {
  cmpc(MOT_LEFT);
  cmpc(MOT_RIGHT);
  cmpc(MOT_FRONT);
}