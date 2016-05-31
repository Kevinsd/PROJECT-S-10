#ifndef __MODULESCENELEVEL9_H__
#define __MODULESCENELEVEL9_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleSceneLevel9 : public Module
{
public:
	ModuleSceneLevel9();
	~ModuleSceneLevel9();

	bool Start();
	update_status Update();
	bool CleanUp();


public:

	int shoot_angle = 90;
	SDL_Texture* graphics_sprite = nullptr;
	SDL_Texture* graphics_sprite_launcher = nullptr;
	SDL_Texture* graphics = nullptr;
	//	SDL_Rect launcher2;
	SDL_Rect bag;
	SDL_Rect wheel;
	SDL_Rect ballsprite_blue;
	SDL_Rect ballsprite_red;
	SDL_Rect ballsprite_yellow;
	SDL_Rect ballsprite_orange;
	SDL_Rect ballsprite_grease;
	SDL_Rect ballsprite_purple;
	SDL_Rect arrowRect;
	SDL_Rect foreground;
	SDL_Rect background;
	Animation pipe;
	Animation left_bub;
	//	Animation pipe2;
	Animation bub;
	Animation bub2;
	Animation bub_static;
	Animation launcher;
	//  Throw sound
	Mix_Chunk* throw_effect = nullptr;

	
	float foreground_pos;
	bool forward;
};

#endif // __MODULESCENELEVEL_H__