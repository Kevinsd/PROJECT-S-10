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
	Ball* Collision();
	bool CheckTile(int,int);
	void Check_Pop(Ball* ball);
	void CheckSoroundings(Ball*, Vector<Ball*>&, Vector<Ball*>&);
	Ball* GetBallFromTile(int x, int y);
	bool IsChecked(Ball* ball, Vector<Ball*>& toCheck, Vector<Ball*>& checked);
	void ShootBall(float);
	void CreateBall();
	void AddBall(int tile_x, int tile_y, Color color);
	void DeleteFlying();
	p2Point<int> CheckClosestEmpty(Ball* collided, Ball* toMove);

	p2Point <int> GetTile(int,int);
	p2Point <int> GetPos(int x, int y);

	Ball* recharge_ball = nullptr;
	Ball* moving_ball = nullptr;
	Vector<Ball*> array;
	SDL_Rect ballsprite_blue;
	SDL_Rect ballsprite_green;
	SDL_Rect ballsprite_yellow;
	SDL_Rect ballsprite_red;
	SDL_Rect ballsprite_gray;
	SDL_Rect ballsprite_purple;
	SDL_Rect ballsprite_black;
	SDL_Rect ballsprite_orange;
private:


};

#endif // __ModuleAudio_H__