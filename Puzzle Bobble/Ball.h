#ifndef _BALL_H_
#define _BALL_H _



enum Color { BLUE, RED, GREEN, YELLOW };

class Ball

{
private:

public:

	float x = 0;
	float y = 0;
	int rad = 0;
	float angle = 0;
	float velocity = 9;
	bool moving = false;
	Color color;

	Ball();
	Ball(float x, float y, int rad, Color color);
	void Shoot(float);
	bool Move();


	~Ball();



};





#endif