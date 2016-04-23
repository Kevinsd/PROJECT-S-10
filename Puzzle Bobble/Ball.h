#ifndef _BALL_H_
#define _BALL_H _



enum Color { BLUE, RED, GREEN,YELLOW };

class Ball

{
private:

public:

	int x= 0;
	int y=0;
	int rad = 0;
	float velocity = 1;
	bool moving = false;
	bool moving_right = false;
	bool moving_left = false;
	Color color;
	
	Ball();
	Ball(int x, int y, int rad, Color color);

	void Move();
	

	~Ball();



};





#endif