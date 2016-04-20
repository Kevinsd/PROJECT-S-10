#include "Ball.h"


Ball::Ball(int pos_x, int pos_y, int radius, Color supercolor) :x(pos_x), y(pos_y), rad(radius), color (supercolor)
{ 

}

Ball::~Ball()
{

}


void Ball::Move()
{

	
	
		y -= velocity;
	
	if (y <= 64)
	
	{
		moving = false;
		y = 64;
	}
}