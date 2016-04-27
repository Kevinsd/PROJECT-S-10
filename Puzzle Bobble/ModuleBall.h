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
	bool Collision();
	bool CheckTile(int,int);
	void ShootBall(float);
	void CreateBall();
	
	p2Point <int> GetTile(int,int);
	p2Point <int> GetPos(int x, int y);

	Ball* moving_ball = nullptr;
	Vector<Ball*> array;
	SDL_Rect ballsprite_blue;
	SDL_Rect ballsprite_green;
	SDL_Rect ballsprite_yellow;
	SDL_Rect ballsprite_red;
	SDL_Rect ballsprite_gray;
	SDL_Rect ballsprite_purple;
private:


};

#endif // __ModuleAudio_H__