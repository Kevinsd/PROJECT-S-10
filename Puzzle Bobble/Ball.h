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
	float velocity = 9;
	bool moving = false;
	Color color;

	Ball();
	Ball(int x, int y, int rad, Color color);

	void Move();
	

	~Ball();



};





#endif