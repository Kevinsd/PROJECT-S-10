#include "Application.h"
#include "ModuleBall.h"
//#include "Ball.h"
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

bool Ball::Move(int top)
{
	float vel_x = 0;
	float vel_y = 0;
	
	if (moving)
		
	{

		vel_y = sin(angle)*velocity;
		vel_x = cos(angle)*velocity;
		x += vel_x;
		y -= vel_y;
		
		App->ball_controll->Collision();
		collidedBall = App->ball_controll->Collision();
		if (collidedBall)
		{
			moving = false;
			return false;
		}
		if (x+rad >= 224)
		{
			x = 224 - rad;
			angle = 3.14 - angle;
			 flash = true;
		}

		if (x-rad <= 96)
		{
			x = 96 + rad;
			angle = 3.14 - angle;
			 flash = true;
		}


		if (y-rad <= top )

		{
			moving = false;
			y = top + rad;
			bool flash = true;
			return false;
		}

		//for seeing colisions
	}
	return true;
}