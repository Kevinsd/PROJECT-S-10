#ifndef __ModuleBall_H__
#define __ModuleBall_H__

//#include "Globals.h"
#include "Module.h"
#include "Vector.h"
#include "Ball.h"
#include "SDL\include\SDL.h"
#include "p2Point.h"


class ModuleBall : public Module
{
public:

	ModuleBall();
	~ModuleBall();

	bool Init();
	bool Start();
	update_status Update ();
	bool CleanUp();
	void ShootBall(float);
	void CreateBall();
	p2Point <int> GetPos(int,int);

	Ball* moving_ball = nullptr;
	Vector<Ball*> array;
	SDL_Rect ballsprite_blue;


private:


};

#endif // __ModuleAudio_H__