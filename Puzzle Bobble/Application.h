#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 13

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleAudio;
class ModuleSceneLevel;
class ModuleSceneMenu;
class ModulePlayer;
class ModuleFadeToBlack;
class Module;
class ModuleBall;
class ModuleSceneCongrat;
class ModuleSceneLevel8;
class ModuleSceneLevel9;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneLevel* scene_level;
	ModuleSceneLevel8* scene_level8;
	ModuleSceneLevel9* scene_level9;
	ModuleSceneMenu* scene_menu;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleBall* ball_controll;
	ModuleSceneCongrat* scene_congrat;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__