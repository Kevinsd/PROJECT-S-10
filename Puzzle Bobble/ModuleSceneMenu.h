#ifndef __MODULESCENEHONDA_H__
#define __MODULESCENEHONDA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneMenu : public Module
{
public:
	ModuleSceneMenu();
	~ModuleSceneMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect roof;
	SDL_Rect foreground;
	SDL_Rect background;
	Animation water;
	uint fx = 0;

	//go level effect
	Mix_Chunk* go_level = nullptr;
};

#endif // __MODULESCENEHONDA_H__