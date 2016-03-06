#include <math.h>

//Motor constants
#define MOT_FRONT 0
#define MOT_FRONT_SPEED 80*10
#define MOT_LEFT 1
#define MOT_LEFT_SPEED 80*10
#define MOT_RIGHT 2
#define MOT_RIGHT_SPEED 80*10

//Direction constants
//sqrt(3/4) speed values: 0, 60, 120, 180, 240, 300, 360
//full speed values: 90, ,270
#define FORWARD 0
#define RIGHT 90
#define BACKWARD 180
#define LEFT 270

//Physical constants
#define WHEELDIAMETER 5
#define WHEELRADIUS 2.5
#define ROBOTRADIUS 14 

//Miscellaneous constants
#define CMtoBEMF (1400/(M_PI*WHEELDIAMETER))
#define ANGLEADJUST 1.1547

void move(float dist, int direction); 

void right(float degrees);

void left(float degrees);

void clear_all_positions();