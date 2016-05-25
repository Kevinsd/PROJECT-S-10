#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevel.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMenu.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneMenu::ModuleSceneMenu()
{
	// ground
	//ground = {8, 376, 848, 64};

	// roof


	// foreground


	// Background / sky
	background = {0, 0, 320, 240};


}

ModuleSceneMenu::~ModuleSceneMenu()
{}

// Load assets
bool ModuleSceneMenu::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Sprites and sound/Menu2.png");

	App->audio->PlayMusic("Sprites and sound/intro_music.ogg", 1.0f);

	go_level = App->audio->Load_effects("Sprites and sound/Go_level.wav");

	App->player->Enable();

	return ret;
}

// Load assets
bool ModuleSceneMenu::CleanUp()
{
	LOG("Unloading stage");
	App->player->Disable();
	return true;
}

// Update: draw background
update_status ModuleSceneMenu::Update()
{
	// Draw everything --------------------------------------	
	//App->render->Blit(graphics, 0, 0, &ground);
	App->render->Blit(graphics, 0, 0, &background); 
	
	
	
	// back of the room
	/*
	App->render->Blit(graphics, 280, 125, &foreground);
	App->render->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation
	App->render->Blit(graphics, 0, -16, &roof, 0.75f);*/

	// TODO 3: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_menu,App->scene_level, 1.0f);
		Mix_PlayChannel(-1, go_level, 0);
	}
	return UPDATE_CONTINUE;
	
}