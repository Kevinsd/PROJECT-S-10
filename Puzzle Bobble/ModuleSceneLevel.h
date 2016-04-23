#ifndef __MODULESCENELEVEL_H__
#define __MODULESCENELEVEL_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Ball.h"
struct SDL_Texture;

class ModuleSceneLevel : public Module
{
public:
	ModuleSceneLevel();
	~ModuleSceneLevel();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	Ball* one_ball=nullptr;
	SDL_Texture* graphics_ball = nullptr;
	SDL_Texture* graphics = nullptr;
	SDL_Rect ballsprite;
	SDL_Rect ground;
	SDL_Rect foreground;
	SDL_Rect background;
	Animation flag;
	Animation girl;

	float foreground_pos;
	bool forward;
};

#endif // __MODULESCENELEVEL_H__