#include <kipr/botball.h>
#include "omniDrive.h"

int main()
{
    forward(80.645, FORWARD);
	right(180);
	forward(62.23, FORWARD);
  	//servo code to lift the box up here
  	right(90);
  	forward(45.72, FORWARD);
  	right(116);
  	forward(49.53, FORWARD);
  	left(125);
  	forward(50.8, FORWARD);
    right(74);
  	forward(60, FORWARD);
    return 0;
}