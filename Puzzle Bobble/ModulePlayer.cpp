#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	/*position.x = 100;
	position.y = 220;*/

	

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	//graphics = App->textures->Load("ryu.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{


/*	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &forward;
		position.x += speed;
	}*/

	// Draw everything --------------------------------------


	//App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}