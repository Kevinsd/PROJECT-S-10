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

	// Pipe

	pipe.PushBack({338,1087,13,11});
	pipe.PushBack({ 354, 1081, 13, 18 });
	pipe.speed = 0.0f;
	// Background / sky
	background.x = 0;
	background.y = 0;
	background.w = 320;
	background.h = 240;
	
	// Launcher Animation


	// bub animation
	bub.PushBack({8, 220, 27, 19});
	bub.PushBack({42, 220, 28, 19});
	bub.PushBack({ 76, 220, 31, 19 });
	bub.PushBack({ 110,220, 31, 19 }); 
	bub.PushBack({144, 220, 29, 19 });
	bub.PushBack({178, 220, 28, 19 });
	bub.PushBack({212, 220, 26, 19 });
	bub.PushBack({246, 220, 26, 19 });
	
	bub.speed = 0.3f;

	//launcher 
/*	launcher2.x = 50;
	launcher2.y = 1020;
	launcher2.w = 56;
	launcher2.h=40 ;
	*/
	//Bag
	bag.x = 358;
	bag.y = 833;
	bag.w = 56;
	bag.h = 24;

	//launcher animation
	launcher.PushBack({ 50, 1020, 56, 40 });
	launcher.PushBack({ 50, 1077, 56, 40 });
	launcher.PushBack({ 50, 1131, 56, 40 });
	launcher.PushBack({ 116, 1020, 56, 40 });
	launcher.PushBack({ 116, 1077, 56, 40 });
	launcher.PushBack({ 116, 1131, 56, 40 });
	launcher.PushBack({ 182, 1020, 56, 40 });
	launcher.PushBack({ 182, 1077, 56, 40 });
	launcher.PushBack({ 182, 1131, 56, 40 });
	launcher.PushBack({ 248, 1020, 56, 40 });
	launcher.PushBack({ 248, 1077, 56, 40 });
	launcher.PushBack({ 248, 1131, 56, 40 });

	launcher.speed = 0.0f;
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
	
	graphics = App->textures->Load("Level1.png");
	graphics_sprite = App->textures->Load("spritespuzzle.png");

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
	
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background);


	// Bub
	
	
	launcher.speed = 0.0f;
	App->render->Blit(graphics_sprite, 130, 192, &(launcher.GetCurrentFrame()), 0.75f); // launcher 
	pipe.speed = 0.0f;
	App->render->Blit(graphics_sprite, 154, 215, &(pipe.GetCurrentFrame()), 0.75f);

	//	App->render->Blit(graphics, 0, (int)foreground_pos, &foreground, 0.92f);
	//	App->render->Blit(graphics, 253, (int)foreground_pos, &foreground, 0.92f);

		//App->render->Blit(graphics, 0, 170, &ground);
		

	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_DOWN)
	{
	//	App->ball_controll->GetPos( pos_x,  pos_y);

		if (App->ball_controll->moving_ball == NULL)

		{
			App->ball_controll->CreateBall();
		}
			


	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT)
	{	
		if (shoot_angle <= 170){
			launcher.speed = 0.3f;
			App->render->Blit(graphics_sprite, 130, 192, &(launcher.GetCurrentFrame()), 0.75f); // launcher animation

			App->render->Blit(graphics_sprite, 172, 213, &(bub.GetCurrentFrame()), 0.02f); // Bub animation
			shoot_angle += 1;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT)
	{	
		if (shoot_angle >= 10)
		{
			launcher.speed = 0.3f;
			App->render->Blit(graphics_sprite, 130, 192, &(launcher.GetCurrentFrame()), 0.75f); // launcher animation

			App->render->Blit(graphics_sprite, 174, 213, &(bub.GetCurrentFrame()), 0.02f); // Bub animation

			shoot_angle -= 1;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		if (App->ball_controll->moving_ball != NULL)
		{
			App->ball_controll->ShootBall(shoot_angle);
			pipe.speed = 0.02f;
			App->render->Blit(graphics_sprite, 154, 215, &(pipe.GetCurrentFrame()), 0.75f);
		}
	}

	App->render->Blit(graphics_sprite, 86, 209, &bag, 0.75f); // Bag 

	return UPDATE_CONTINUE;
}