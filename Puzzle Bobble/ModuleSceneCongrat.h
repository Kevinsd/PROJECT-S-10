#ifndef __MODULESCENECON_H__
#define __MODULESCENECON_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"


struct SDL_Texture;

class ModuleSceneCongrat : public Module
{
public:
	ModuleSceneCongrat();
	~ModuleSceneCongrat();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	int shoot_angle = 90;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics_sprite = nullptr;
	
	SDL_Rect background;
	

	float foreground_pos;
	bool forward;
};

#endif // ModuleSceneCongrat