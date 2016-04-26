#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneLevel.h"
#include "ModuleSceneMenu.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleBall.h"
#include "Vector.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneLevel::ModuleSceneLevel()
{
	//one_ball = new Ball(316,417,16,BLUE);

	//Balls

	// foreground
	foreground.x = 8;
	foreground.y = 24;
	foreground.w = 521;
	foreground.h = 181;
	
	// Background / sky
	background.x = 0;
	background.y = 0;
	background.w = 640;
	background.h = 480;
	
	// Launcher Animation
	launcher.PushBack({ 624, 16, 32, 56 });
	launcher.PushBack({ 624, 80, 32, 56 });
	launcher.PushBack({ 624, 144, 32, 56 });
	launcher.speed = 3;

	// bub animation
	bub.PushBack({12, 442, 60, 38});
	bub.PushBack({80, 442, 60, 38});
	bub.PushBack({ 149, 442, 60, 38 });
	bub.PushBack({ 217,442, 60, 38 }); 
	bub.PushBack({285, 442, 60, 38 });
	bub.PushBack({353, 442, 60, 38 });
	bub.PushBack({422, 442, 60, 38 });
	bub.PushBack({490, 442, 60, 38 });
	
	bub.speed = 0.3f;

	//launcher animation

	launcher.PushBack({ 50, 1020, 56, 40 });
	launcher.PushBack({ 121, 2108, 111, 80 });
	launcher.PushBack({ 121, 2212, 111, 80 });
	launcher.PushBack({ 253, 2003, 111, 80 });
	launcher.PushBack({ 253, 2108, 111, 80 });
	launcher.PushBack({ 253, 2212, 111, 80 });
	launcher.PushBack({ 386, 2003, 111, 80 });
	launcher.PushBack({ 386, 2108, 111, 80 });
	launcher.PushBack({ 386, 2212, 111, 80 });
	launcher.PushBack({ 518, 2003, 111, 80 });
	launcher.PushBack({ 518, 2108, 111, 80 });
	launcher.PushBack({ 518, 2212, 111, 80 });

	launcher.speed = 0.3f;
	/*launcher.PushBack({ 50, 1020, 56, 40 });//2003
	launcher.PushBack({ 121, 2108, 111, 80 });
	launcher.PushBack({ 121, 2212, 111, 80 });
	launcher.PushBack({ 253, 2003, 111, 80 });
	launcher.PushBack({ 253, 2108, 111, 80 });
	launcher.PushBack({ 253, 2212, 111, 80 });
	launcher.PushBack({ 386, 2003, 111, 80 });
	launcher.PushBack({ 386, 2108, 111, 80 });
	launcher.PushBack({ 386, 2212, 111, 80 });
	launcher.PushBack({ 518, 2003, 111, 80 });
	launcher.PushBack({ 518, 2108, 111, 80 });
	launcher.PushBack({ 518, 2212, 111, 80 });

	launcher.speed = 0.3f;*/
	
	// for moving the foreground
	//foreground_pos = 0;
//	forward = true;
}

ModuleSceneLevel::~ModuleSceneLevel()
{
	//delete one_ball;
}


// Load assets
bool ModuleSceneLevel::Start()
{
	LOG("Loading lvl scene");
	
	graphics = App->textures->Load("Level.png");
	graphics_sprite = App->textures->Load("Spritespuzzle.png");

	App->audio->PlayMusic("level_music.ogg", 1.0f);
	
	App->player->Enable();
	
	return true;
}

// UnLoad assets
bool ModuleSceneLevel::CleanUp()
{
	LOG("Unloading lvl scene");
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneLevel::Update()
{
	// Calculate boat Y position -----------------------------
	if (foreground_pos < -6.0f)
		forward = false;
	else if (foreground_pos > 0.0f)
		forward = true;

	if (forward)
		foreground_pos -= 0.02f;
	else
		foreground_pos += 0.02f;

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background);
	App->render->Blit(graphics_sprite, 126, 160, &(launcher.GetCurrentFrame()), 0.75f); // launcher animation

	
	// Bub
	App->render->Blit(graphics_sprite, 350, 433, &(bub.GetCurrentFrame()),0.02f ); // Bub animation
		
	//	App->render->Blit(graphics, 0, (int)foreground_pos, &foreground, 0.92f);
	//	App->render->Blit(graphics, 253, (int)foreground_pos, &foreground, 0.92f);

		//App->render->Blit(graphics, 0, 170, &ground);
		
	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_DOWN)
	{
	//	App->ball_controll->GetPos( pos_x,  pos_y);
		App->render->Blit(graphics_sprite, App->ball_controll->moving_ball->x - 16, App->ball_controll->moving_ball->y - 16, &ballsprite_blue);
	//	shoot_angle;


			//one_ball->x += 1;


	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		if (App->ball_controll->moving_ball != NULL)
		{
			App->ball_controll->moving_ball->Shoot(shoot_angle);
		}


		//one_ball->x += 1;


	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT)
	{

		if (App->ball_controll->moving_ball != NULL)
		{
			App->ball_controll->moving_ball->Shoot(shoot_angle);
		}
		//one_ball->x += 1;

	
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		if (App->ball_controll->moving_ball != NULL)
		{
			App->ball_controll->ShootBall(shoot_angle);
		}
	}
	return UPDATE_CONTINUE;
}