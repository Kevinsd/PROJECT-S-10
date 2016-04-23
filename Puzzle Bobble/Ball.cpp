#include "Ball.h"


Ball::Ball(int pos_x, int pos_y, int radius, Color supercolor):x(pos_x), y(pos_y), rad(radius), color (supercolor)
{ 

}

Ball::~Ball()
{

}


void Ball::Move()
{
	int tmp = 0;
	

	if (moving_right)
	{
		x += 1;
		tmp = x;
		moving_right = false;
	}

	if (moving_left)
	{
		x -= 1;
		tmp = x;
		moving_left = false;
	}
	if (moving)
	{
		y -= velocity;
		x += tmp;
		//	if
		if (y <= 64)

		{
			moving = false;
			y = 64;
		}
	}
}