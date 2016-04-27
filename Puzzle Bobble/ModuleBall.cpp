#include "Application.h"
#include "ModuleBall.h"
#include "ModuleSceneLevel.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"

#include <stdlib.h>

ModuleBall::ModuleBall()
{
	
}

// Destructor
ModuleBall::~ModuleBall()
{}

// Called before render is available
bool ModuleBall::Init()
{
	ballsprite_blue = { 12, 260, 16, 16 };
	ballsprite_gray = { 12, 286, 16, 16 };
	ballsprite_red = { 12, 312, 16, 16 };
	ballsprite_yellow = { 12, 338, 16, 16 };
	ballsprite_purple = { 12, 211, 16, 16 };
	ballsprite_green = { 318, 260, 16, 16 };


	return true;
}
bool ModuleBall::Start()
{

	return true;
}


update_status ModuleBall::Update()
{
	for (unsigned int i = 0; i < array.size(); i++)
	{
		
			App->render->Blit(App->scene_level->graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_blue);
			if (moving_ball != NULL)
			{
				App->render->Blit(App->scene_level->graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_gray);

				App->render->Blit(App->scene_level->graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_red);

				App->render->Blit(App->scene_level->graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_green);

				App->render->Blit(App->scene_level->graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_yellow);

				App->render->Blit(App->scene_level->graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_purple);
			}
	}
	if (moving_ball != NULL)
	{
		if (moving_ball->moving)
		{

			if (moving_ball->Move() == false)
			{
				
				p2Point <int> get_pos = GetPos(moving_ball->x,moving_ball->y);
				unsigned int index = get_pos.y * 8 + get_pos.x;
				moving_ball->x= (int)moving_ball->x / 16 * 16 + 8;//look there
				moving_ball->y=(int)moving_ball->y / 16 * 16 ;
				array.push_back(moving_ball); 
				moving_ball = NULL;

			}

		}
		if (moving_ball != NULL)
		{
			if (moving_ball->color == BLUE)
				App->render->Blit(App->scene_level->graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_blue);		
			if (moving_ball->color == GRAY)
				App->render->Blit(App->scene_level->graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_gray);
			if (moving_ball->color == RED)
				App->render->Blit(App->scene_level->graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_red);
			if (moving_ball->color == GREEN)
				App->render->Blit(App->scene_level->graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_green);
			if (moving_ball->color == YELLOW)
				App->render->Blit(App->scene_level->graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_yellow);
			if (moving_ball->color == PURPLE)
				App->render->Blit(App->scene_level->graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_purple);
		}
	}
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleBall::CleanUp()
{
	
	return true;
}

void ModuleBall::ShootBall(float shoot)
{
	if (moving_ball!=NULL)
		moving_ball->Shoot(shoot);
}

void ModuleBall::CreateBall()
{
	Color type = static_cast <Color> (rand()% 4);

	moving_ball = new Ball(162, 208, 8, type); //look
	
}
p2Point <int>  ModuleBall::GetPos(int x, int y)
{
	 
	int pos_y = y / 16;
	int pos_x = x/16;

	p2Point <int> ret = { pos_x, pos_y };
	
	return ret;
}