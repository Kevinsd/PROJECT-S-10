#include "Application.h"
#include "ModuleBall.h"
#include "ModuleSceneLevel.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "Globals.h"
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
		if (array[i]->color == BLUE)
		App->render->Blit(App->scene_level->graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_blue);
		else if (array[i]->color == GRAY)
		App->render->Blit(App->scene_level->graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_gray);
		else if (array[i]->color == RED)
		App->render->Blit(App->scene_level->graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_red);
		else if (array[i]->color == GREEN)
		App->render->Blit(App->scene_level->graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_green);
		else if (array[i]->color == YELLOW)
		App->render->Blit(App->scene_level->graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_yellow);
		else if (array[i]->color == PURPLE)
		App->render->Blit(App->scene_level->graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_purple);
		
	}
	if (moving_ball != NULL)
	{
		if (moving_ball->moving)
		{

			if (moving_ball->Move() == false)
			{
				
				p2Point <int> get_tile = GetTile(moving_ball->x,moving_ball->y);
				p2Point <int> get_pos = GetPos(get_tile.x, get_tile.y);

				CheckTile(get_tile.x, get_tile.y);
				moving_ball->x= get_pos.x;//look there
				moving_ball->y= get_pos.y;
				
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
p2Point <int>  ModuleBall::GetTile(int x, int y)
{
	x = x - 96 - 8;
	y = y - 24 - 8;	
	int pos_y = 0;
	int pos_x = 0;
	pos_y = y  / 16;
	
	if (pos_y % 2 != 0)
	{
		x += 8;
		pos_x = x / 16;		
	}
	else
	{

		pos_x = x / 16 ;
		if (pos_x != 0)
		{
			pos_x += 1;
		}
	}
	LOG("x:%i,y;%i", pos_x, pos_y);
	p2Point <int> ret = { pos_x, pos_y };
	
	return ret;
}

p2Point <int> ModuleBall::GetPos(int x , int y)
{
	p2Point <int> ret;
	ret.y = y * 16 + 24 + 8;
	if (y % 2 != 0)
	{
		ret.x = x * 16 + 96 + 16;
	}
	else
	{
		ret.x = x * 16 + 96 + 8;
	}
	return ret;
}
bool ModuleBall::CheckTile(int x, int y)
{
	p2Point <int> pos = GetPos(x, y);

	for (unsigned int i = 0; i < array.size(); i++)
	{
		
		if (array[i]->x  == pos.x && array[i]->y  == pos.y)
			{
				LOG(" casilla col ");
				return true;	
			}
	}
}
bool ModuleBall::Collision()
{
	for (unsigned int i = 0; i < array.size(); i++)
	{
		int dist_x = moving_ball->x - array[i]->x;
		int dist_y = moving_ball->y - array[i]->y;
		dist_x = dist_x*dist_x;
		dist_y = dist_y*dist_y;
		int dist_final = sqrt((float)dist_x + (float)dist_y);
		if (moving_ball->rad + array[i]->rad >= dist_final)
		{
			return true;
		}
	}
	return false;
}