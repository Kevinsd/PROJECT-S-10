#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneLevel.h"
#include "ModuleSceneMenu.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBall.h"
#include "ModuleSceneCongrat.h"
#include "ModuleSceneLevel8.h"
#include "ModuleSceneLevel9.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = scene_menu = new ModuleSceneMenu();
	modules[5] = scene_level = new ModuleSceneLevel();
	modules[6] = scene_level8 = new ModuleSceneLevel8();
	modules[7] = scene_level9 = new ModuleSceneLevel9();
	modules[8] = player = new ModulePlayer();
	modules[9] = fade = new ModuleFadeToBlack();
	modules[10] = audio = new ModuleAudio();
	modules[11] = ball_controll = new ModuleBall();
	modules[12] = scene_congrat = new ModuleSceneCongrat();
	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Player will be enabled on the first update of a new scene
	player->Disable();
	// Disable the map that you do not start with
	//scene_menu->Disable();
	scene_level->Disable();
	scene_level8->Disable();
	scene_level9->Disable();
	scene_congrat->Disable();
	ball_controll->Disable();
	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}


update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	
	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}