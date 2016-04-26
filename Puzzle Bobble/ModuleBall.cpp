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
	ballsprite_blue = { 20, 516, 32, 32 };

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
		App->render->Blit(App->scene_level->graphics_sprite, array[i]->x - 16, array[i]->y - 16, &ballsprite_blue);
	}
	if (moving_ball != NULL)
	{
		if (moving_ball->moving)
		{

			if (moving_ball->Move() == false)
			{
				
				p2Point <int> get_pos = GetPos(moving_ball->x,moving_ball->y);
				unsigned int index = get_pos.y * 8 + get_pos.x;
				moving_ball->x= (int)moving_ball->x / 32 * 32 + 16;//look there
				moving_ball->y=(int)moving_ball->y / 32 * 32 ;
				array.push_back(moving_ball); 
				moving_ball = NULL;

			}

		}
		if (moving_ball!=NULL)
		App->render->Blit(App->scene_level->graphics_sprite, moving_ball->x - 16, moving_ball->y - 16, &ballsprite_blue);
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
	Color type = static_cast <Color> (rand()% 3);

	App->ball_controll->moving_ball = new Ball(150, 205, 16, type); //look
}
p2Point <int>  ModuleBall::GetPos(int x, int y)
{
	 
	int pos_y = y / 16;
	int pos_x = x/16;

	p2Point <int> ret = { pos_x, pos_y };
	
	return ret;
}