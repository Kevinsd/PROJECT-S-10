#include "Ball.h"
#include <math.h>

Ball::Ball(float pos_x, float pos_y, int radius, Color supercolor) :x(pos_x), y(pos_y), rad(radius), color(supercolor)
{

}

Ball::~Ball()
{

}

void Ball::Shoot(float shoot_ang)
{
	shoot_ang =( shoot_ang * 2 * 3.14) / 360;
	angle = shoot_ang;
	moving = true;
}

bool Ball::Move()
{
	float vel_x = 0;
	float vel_y = 0;
	if (moving)
	{

		vel_y = sin(angle)*velocity;
		vel_x = cos(angle)*velocity;
		x += vel_x;
		y -= vel_y;

		if (x >= 432)
		{
			x = 432;
			angle = 3.14 - angle;
		}

		if (x <= 208)
		{
			x = 208;
			angle = 3.14 - angle;
		}


		if (y <= 64)

		{
			moving = false;
			y = 64;
			return false;
		}

		//for seeing colisions
	}
	return true;
}