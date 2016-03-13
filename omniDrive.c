#include <kipr/botball.h>
#include "omniDrive.h"

//Drives forward dist in cm, towards direction degrees starting at 12:00 going clockwise
//Split into 3 segments. 1st segment sets up constants and flips 
void move(float dist, int direction) {
  //Stop movement and clear positions
  ao();
  clear_all_positions();
  //Constants and stuff
  int leftGoal = 0;
  int rightGoal = 0;
  int frontGoal = 0;
  direction = (direction + 360)%360;
  if(direction < 0)
    direction *= -1;
  
  //Imagine this as a huge if else statement where condition is direction == case. Target and initial speeds set here.
  switch(direction) {
    //Forward
    case 0:
  	  mav(MOT_LEFT, MOT_LEFT_SPEED);
      mav(MOT_RIGHT, MOT_RIGHT_SPEED);
      leftGoal = dist * CMtoBEMF * ANGLEADJUST;
      rightGoal = dist * CMtoBEMF * ANGLEADJUST;
    break;
    //Backward
    case 180:
      mav(MOT_LEFT, -MOT_LEFT_SPEED);
      mav(MOT_RIGHT, -MOT_RIGHT_SPEED);
      leftGoal = dist * CMtoBEMF * ANGLEADJUST;
      rightGoal = dist * CMtoBEMF * ANGLEADJUST;
    break;
    //Weak BackRight
    case 120:
      mav(MOT_FRONT, MOT_FRONT_SPEED);
      mav(MOT_LEFT, -MOT_LEFT_SPEED);
      frontGoal = dist * CMtoBEMF * ANGLEADJUST;
      leftGoal = dist * CMtoBEMF * ANGLEADJUST;
    break;
    //Reverse Weak BackRight
    case 300:
      mav(MOT_FRONT, -MOT_FRONT_SPEED);
      mav(MOT_LEFT, MOT_LEFT_SPEED);
      frontGoal = dist * CMtoBEMF * ANGLEADJUST;
      leftGoal = dist * CMtoBEMF * ANGLEADJUST;
    break;
    //Weak BackLeft
    case 240:
      mav(MOT_FRONT, -MOT_FRONT_SPEED);
      mav(MOT_RIGHT, -MOT_RIGHT_SPEED);
      frontGoal = dist * CMtoBEMF * ANGLEADJUST;
      rightGoal = dist * CMtoBEMF * ANGLEADJUST;
    break;
    //Weak Reverse BackLeft
    case 60:
      mav(MOT_FRONT, MOT_FRONT_SPEED);
      mav(MOT_RIGHT, MOT_RIGHT_SPEED);
      frontGoal = dist * CMtoBEMF * ANGLEADJUST;
      rightGoal = dist * CMtoBEMF * ANGLEADJUST;
    break;
    //Right
    case 90:
      mav(MOT_FRONT, MOT_FRONT_SPEED);
      mav(MOT_LEFT, -MOT_LEFT_SPEED);
      mav(MOT_RIGHT, MOT_RIGHT_SPEED);
      frontGoal = dist * CMtoBEMF;
      leftGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      rightGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
    break;
    //Left
    case 270:
      mav(MOT_FRONT, -MOT_FRONT_SPEED);
      mav(MOT_LEFT, MOT_LEFT_SPEED);
      mav(MOT_RIGHT, -MOT_RIGHT_SPEED);
      frontGoal = dist * CMtoBEMF;
      leftGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      rightGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
    break;
    //ForwardRight
    case 30:
      mav(MOT_FRONT, MOT_FRONT_SPEED);
      mav(MOT_LEFT, MOT_LEFT_SPEED);
      mav(MOT_RIGHT, MOT_RIGHT_SPEED);
      frontGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      leftGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      rightGoal = dist * CMtoBEMF;
    break;
    //Reverse ForwardRight
    case 210:
      mav(MOT_FRONT, -MOT_FRONT_SPEED);
      mav(MOT_LEFT, -MOT_LEFT_SPEED);
      mav(MOT_RIGHT, -MOT_RIGHT_SPEED);
      frontGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      leftGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      rightGoal = dist * CMtoBEMF;
    break;
    //ForwardLeft
    case 330:
      mav(MOT_FRONT, -MOT_FRONT_SPEED);
      mav(MOT_LEFT, MOT_LEFT_SPEED);
      mav(MOT_RIGHT, MOT_RIGHT_SPEED);
      frontGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      leftGoal = dist * CMtoBEMF;
      rightGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
    break;
    //Reverse ForwardLeft
    case 150:
      mav(MOT_FRONT, MOT_FRONT_SPEED);
      mav(MOT_LEFT, -MOT_LEFT_SPEED);
      mav(MOT_RIGHT, -MOT_RIGHT_SPEED);
      frontGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      leftGoal = dist * CMtoBEMF;
      rightGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
    break;
    default:
      printf("Trying to turn an unsupported direction");
    break;
  }
  
  //Wait until conditions met
  while(abs(gmpc(MOT_LEFT)) < abs(leftGoal) || abs(gmpc(MOT_RIGHT)) < abs(rightGoal) || abs(gmpc(MOT_FRONT)) < abs(frontGoal)) {
    if(abs(gmpc(MOT_LEFT)) >= abs(leftGoal)) {
      off(MOT_LEFT);
    }
    if(abs(gmpc(MOT_RIGHT)) >= abs(rightGoal)) {
      off(MOT_RIGHT);
    }
    if(abs(gmpc(MOT_FRONT)) >= abs(frontGoal)) {
      off(MOT_FRONT);
    }
  }
  ao();
}

void move_at_speed(float dist, int direction, int speed) {
  //Stop movement and clear positions
  ao();
  clear_all_positions();
  //Constants and stuff
  int leftGoal = 0;
  int rightGoal = 0;
  int frontGoal = 0;
  direction = (direction + 360)%360;
  if(direction < 0)
    direction *= -1;
  
  //Imagine this as a huge if else statement where condition is direction == case. Target and initial speeds set here.
  switch(direction) {
    //Forward
    case 0:
  	  mav(MOT_LEFT, speed);
      mav(MOT_RIGHT, speed);
      leftGoal = dist * CMtoBEMF * ANGLEADJUST;
      rightGoal = dist * CMtoBEMF * ANGLEADJUST;
    break;
    //Backward
    case 180:
      mav(MOT_LEFT, -speed);
      mav(MOT_RIGHT, -speed);
      leftGoal = dist * CMtoBEMF * ANGLEADJUST;
      rightGoal = dist * CMtoBEMF * ANGLEADJUST;
    break;
    //Weak BackRight
    case 120:
      mav(MOT_FRONT, speed);
      mav(MOT_LEFT, -speed);
      frontGoal = dist * CMtoBEMF * ANGLEADJUST;
      leftGoal = dist * CMtoBEMF * ANGLEADJUST;
    break;
    //Reverse Weak BackRight
    case 300:
      mav(MOT_FRONT, -speed);
      mav(MOT_LEFT, speed);
      frontGoal = dist * CMtoBEMF * ANGLEADJUST;
      leftGoal = dist * CMtoBEMF * ANGLEADJUST;
    break;
    //Weak BackLeft
    case 240:
      mav(MOT_FRONT, -speed);
      mav(MOT_RIGHT, -speed);
      frontGoal = dist * CMtoBEMF * ANGLEADJUST;
      rightGoal = dist * CMtoBEMF * ANGLEADJUST;
    break;
    //Weak Reverse BackLeft
    case 60:
      mav(MOT_FRONT, speed);
      mav(MOT_RIGHT, speed);
      frontGoal = dist * CMtoBEMF * ANGLEADJUST;
      rightGoal = dist * CMtoBEMF * ANGLEADJUST;
    break;
    //Right
    case 90:
      mav(MOT_FRONT, speed);
      mav(MOT_LEFT, -speed);
      mav(MOT_RIGHT, speed);
      frontGoal = dist * CMtoBEMF;
      leftGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      rightGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
    break;
    //Left
    case 270:
      mav(MOT_FRONT, -speed);
      mav(MOT_LEFT, speed);
      mav(MOT_RIGHT, -speed);
      frontGoal = dist * CMtoBEMF;
      leftGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      rightGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
    break;
    //ForwardRight
    case 30:
      mav(MOT_FRONT, speed);
      mav(MOT_LEFT, speed);
      mav(MOT_RIGHT, speed);
      frontGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      leftGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      rightGoal = dist * CMtoBEMF;
    break;
    //Reverse ForwardRight
    case 210:
      mav(MOT_FRONT, -speed);
      mav(MOT_LEFT, -speed);
      mav(MOT_RIGHT, -speed);
      frontGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      leftGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      rightGoal = dist * CMtoBEMF;
    break;
    //ForwardLeft
    case 330:
      mav(MOT_FRONT, -speed);
      mav(MOT_LEFT, speed);
      mav(MOT_RIGHT, speed);
      frontGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      leftGoal = dist * CMtoBEMF;
      rightGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
    break;
    //Reverse ForwardLeft
    case 150:
      mav(MOT_FRONT, speed);
      mav(MOT_LEFT, -speed);
      mav(MOT_RIGHT, -speed);
      frontGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
      leftGoal = dist * CMtoBEMF;
      rightGoal = dist * CMtoBEMF * LARGEANGLEADJUST;
    break;
    default:
      printf("Trying to turn an unsupported direction");
    break;
  }
  
  //Wait until conditions met
  while(abs(gmpc(MOT_LEFT)) < abs(leftGoal) || abs(gmpc(MOT_RIGHT)) < abs(rightGoal) || abs(gmpc(MOT_FRONT)) < abs(frontGoal)) {
    if(abs(gmpc(MOT_LEFT)) >= abs(leftGoal)) {
      off(MOT_LEFT);
    }
    if(abs(gmpc(MOT_RIGHT)) >= abs(rightGoal)) {
      off(MOT_RIGHT);
    }
    if(abs(gmpc(MOT_FRONT)) >= abs(frontGoal)) {
      off(MOT_FRONT);
    }
  }
  ao();
}


//In place turn for degrees amount of degrees. Negative values turn left.
void right(float degrees) {
  ao();
  
  int turnGoal = 0;
  int turnLeft = 1;
  
  if(degrees < 0) {
    degrees *= -1;
    turnLeft = -1;
  }
  
  float dist = ROBOTRADIUS*(M_PI/180)*degrees;
  //turn motor by turn_wheel_deg degrees
  //float turn_wheel_deg = degrees*ROBOTRADIUS/WHEELRADIUS
  clear_all_positions();
  
  turnGoal = dist*CMtoBEMF;
  
  mav(MOT_FRONT, turnLeft * MOT_FRONT_SPEED);
  mav(MOT_RIGHT, turnLeft * -MOT_RIGHT_SPEED);
  mav(MOT_LEFT, turnLeft * MOT_LEFT_SPEED);
  
  while(abs(gmpc(MOT_FRONT)) < abs(turnGoal) || abs(gmpc(MOT_RIGHT)) < abs(turnGoal) || abs(gmpc(MOT_LEFT)) < abs(turnGoal)) {
    if(abs(gmpc(MOT_LEFT)) >= abs(turnGoal)) {
      off(MOT_LEFT);
    }
    if(abs(gmpc(MOT_RIGHT)) >= abs(turnGoal)) {
      off(MOT_RIGHT);
    }
    if(abs(gmpc(MOT_FRONT)) >= abs(turnGoal)) {
      off(MOT_FRONT);
    }
  }
  ao();
}

//In place turn for degrees amount of degrees. Negative values turn right.
void left(float degrees) {
  right(-degrees);
}

//Clears positions from all motors.
void clear_all_positions() {
  cmpc(MOT_LEFT);
  cmpc(MOT_RIGHT);
  cmpc(MOT_FRONT);
}