#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneCongrat.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneLevel.h"
#include "ModulePlayer.h"
//#include "ModuleAudio.h"
#include "ModuleBall.h"
#include "ModuleInput.h"



// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneCongrat::ModuleSceneCongrat()
{
	background.x = 0;
	background.y = 0;
	background.w = 320;
	background.h = 240;
}

ModuleSceneCongrat::~ModuleSceneCongrat()
{
	//delete one_ball;
}


// Load assets
bool ModuleSceneCongrat::Start()
{
	App->currentscene = this;
	LOG("Loading lvl scene");

	graphics = App->textures->Load("Sprites and sound/Congrats.png");
	graphics_sprite = App->textures->Load("Sprites and sound/spritespuzzle.png");

//	App->audio->PlayMusic("Sprites and sound/level_music.ogg", 1.0f);



	App->player->Enable();
	App->ball_controll->Enable();
	return true;
}

// UnLoad assets
bool ModuleSceneCongrat::CleanUp()
{

	LOG("Unloading lvl scene");
	App->player->Disable();
	if (App->ball_controll->IsEnabled())
		App->ball_controll->Disable();
	return true;
}

// Update: draw background
update_status ModuleSceneCongrat::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene_menu);
	}
	return UPDATE_CONTINUE;
}