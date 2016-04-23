#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneLevel.h"
#include "ModuleSceneMenu.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneLevel::ModuleSceneLevel()
{
	one_ball = new Ball(320,300,16,BLUE);

	//Balls

	ballsprite = { 20, 516, 32, 32 };

	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;



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

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// Girl Animation
	girl.PushBack({624, 16, 32, 56});
	girl.PushBack({624, 80, 32, 56});
	girl.PushBack({624, 144, 32, 56});
	girl.speed = 0.05f;

	// for moving the foreground
	foreground_pos = 0;
	forward = true;
}

ModuleSceneLevel::~ModuleSceneLevel()
{
	delete one_ball;
}


// Load assets
bool ModuleSceneLevel::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("Level.png");
	graphics_ball = App->textures->Load("spritesbuenos.png");
	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	
	return true;
}

// UnLoad assets
bool ModuleSceneLevel::CleanUp()
{
	LOG("Unloading ken scene");
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
	App->render->Blit(graphics_ball, one_ball->x - 16, one_ball->y - 16, &ballsprite);
	// sea and sky
	/*	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

		App->render->Blit(graphics, 0, (int)foreground_pos, &foreground, 0.92f);
		App->render->Blit(graphics, 192, 104 + (int)foreground_pos, &(girl.GetCurrentFrame()), 0.92f); // girl animation

		App->render->Blit(graphics, 0, 170, &ground);
		*/
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT)
	{

		one_ball->moving_left = true;

		if (one_ball->moving_left)

			one_ball->Move();


		//one_ball->x += 1;


	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT)
	{

		one_ball->moving_right = true;
	
		if (one_ball->moving_right)
			
			one_ball->Move();
		

		//one_ball->x += 1;

	
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		one_ball->moving = true;
	}
	if (one_ball->moving)
		
		one_ball->Move();


	return UPDATE_CONTINUE;
}