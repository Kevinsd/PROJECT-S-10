#include "Application.h"
#include "ModuleBall.h"
#include "ModuleSceneLevel.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "Globals.h"
#include <stdlib.h>
#include "ModuleFadeToBlack.h"

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
				//iPoint dstTile = GetTile(moving_ball->x, moving_ball->y); look there!
				iPoint dstTile = CheckClosestEmpty(moving_ball->collidedBall, moving_ball);
				p2Point <int> get_pos = GetPos(dstTile.x, dstTile.y);

				//CheckTile(get_tile.x, get_tile.y);
				moving_ball->x = get_pos.x;
				moving_ball->y= get_pos.y;
				if (moving_ball->y >= 180) // lOSE CONDITION
				{
					moving_ball = NULL;
					App->fade->FadeToBlack(App->scene_level, (Module*)App->scene_menu);
					return UPDATE_CONTINUE;
				}
				  
				//TMP FIX
				if (CheckTile(dstTile.x, dstTile.y))
				{
					delete moving_ball;
				}

				else 
				{
					array.push_back(moving_ball);

					Check_Pop(moving_ball);
					if (moving_ball)
						moving_ball = NULL;
				}
				CreateBall();
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
	for (unsigned int i = 0; i< array.size(); i++)
	{
		delete array[i];

	}
	array.clear();
	/*if (moving_ball)
		delete moving_ball;*/
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

void ModuleBall::AddBall(int tile_x, int tile_y, Color color)
{
	iPoint pos = GetPos(tile_x, tile_y);
	if (!CheckTile(tile_x, tile_y))
	{
		Ball* newBall = new Ball(pos.x, pos.y, 8, color);
		array.push_back(newBall);
	}
}

p2Point<int> ModuleBall::CheckClosestEmpty(Ball* collided, Ball* toMove)
{
	iPoint ret = { 0, 0 };

	if (collided)
	{
		iPoint colTile = GetTile(collided->x, collided->y);
		int lowerDst = 5000;
		if (!CheckTile(colTile.x + 1, colTile.y))
		{
			iPoint pos = GetPos(colTile.x + 1, colTile.y);
			float dstX = pos.x - toMove->x;
			float dstY = pos.y - toMove->y;
			lowerDst = sqrt(dstX*dstX + dstY * dstY);
			ret = { colTile.x + 1, colTile.y };
		}

		if (!CheckTile(colTile.x - 1, colTile.y))
		{
			iPoint pos = GetPos(colTile.x - 1, colTile.y);
			float dstX = pos.x - toMove->x;
			float dstY = pos.y - toMove->y;
			if (sqrt(dstX*dstX + dstY * dstY) < lowerDst)
			{
				lowerDst = sqrt(dstX*dstX + dstY * dstY);
				ret = { colTile.x - 1, colTile.y };
			}
		}

		if (!CheckTile(colTile.x, colTile.y - 1))
		{
			iPoint pos = GetPos(colTile.x, colTile.y - 1);
			float dstX = pos.x - toMove->x;
			float dstY = pos.y - toMove->y;
			if (sqrt(dstX*dstX + dstY * dstY) < lowerDst)
			{
				lowerDst = sqrt(dstX*dstX + dstY * dstY);
				ret = { colTile.x, colTile.y - 1 };
			}
		}

		if (!CheckTile(colTile.x, colTile.y + 1))
		{
			iPoint pos = GetPos(colTile.x, colTile.y + 1);
			float dstX = pos.x - toMove->x;
			float dstY = pos.y - toMove->y;
			if (sqrt(dstX*dstX + dstY * dstY) < lowerDst)
			{
				lowerDst = sqrt(dstX*dstX + dstY * dstY);
				ret = { colTile.x, colTile.y + 1 };
			}
		}

		if (!CheckTile(colTile.x + 1, colTile.y + 1))
		{
			iPoint pos = GetPos(colTile.x + 1, colTile.y + 1);
			float dstX = pos.x - toMove->x;
			float dstY = pos.y - toMove->y; 
			if (sqrt(dstX*dstX + dstY * dstY) < lowerDst)
			{
				lowerDst = sqrt(dstX*dstX + dstY * dstY);
				ret = { colTile.x + 1, colTile.y + 1 };
			}
		}
		if (!CheckTile(colTile.x + 1, colTile.y - 1))
		{
			iPoint pos = GetPos(colTile.x + 1, colTile.y - 1);
			float dstX = pos.x - toMove->x;
			float dstY = pos.y - toMove->y;
			if (sqrt(dstX*dstX + dstY * dstY) < lowerDst)
			{
				lowerDst = sqrt(dstX*dstX + dstY * dstY);
				ret = { colTile.x + 1, colTile.y - 1 };
			}
		}
	}
	else
	{
		ret = GetTile(toMove->x, toMove->y);
	}
	return ret;
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
	if (x < 0)
		return true;
	if (x > 7 && y % 2 == 0)
		return true;
	if (x > 6 && y % 2 != 0)
		return true;
	p2Point <int> pos = GetPos(x, y);

	for (unsigned int i = 0; i < array.size(); i++)
	{
		
		if (array[i]->x  == pos.x && array[i]->y  == pos.y)
			{
				LOG(" casilla col ");
				return true;	
			}
	}
	return false;
}

Ball* ModuleBall::GetBallFromTile(int x, int y)
{
	iPoint pos = GetPos(x, y);
	for (unsigned int i = 0; i < array.size(); i++)
	{
		int ballPos_x = array[i]->x;
		int ballPos_y = array[i]->y;
		if (ballPos_x == pos.x && ballPos_y == pos.y)
			return array[i];
	}
	return NULL;
}

Ball* ModuleBall::Collision()
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
			return array[i];
		}
	}
	return NULL;
}
void ModuleBall::Check_Pop(Ball* ball)
{
	Vector<Ball*> toCheck;
	Vector<Ball*> checked;
	
	toCheck.push_back(ball);

	while (toCheck.size() != 0)
	{
		uint i = 0;
		CheckSoroundings(toCheck[i], toCheck, checked);
	}

	if (checked.size() >= 3)
	{
		for (uint i = 0; i < checked.size(); i++)
		{
			for (uint j = 0; j < array.size(); j++)
			{
				if (array[j] == checked[i])
				{
					array.Pick(j);
					break;
				}
			}
			delete checked[i];
		}
		checked.clear();
	}
	checked.clear();
}

void ModuleBall::CheckSoroundings(Ball* ball, Vector<Ball*>& toCheck, Vector<Ball*>& checked)
 {
	iPoint tile = GetTile(ball->x, ball->y);
	Ball* checking = NULL;

	checking = GetBallFromTile(tile.x + 1, tile.y);
	if (checking && checking->color == ball->color)
	{
		if (!IsChecked(checking, toCheck, checked))
		{
			toCheck.push_back(checking);
		}
	}
	checking = NULL;
	checking = GetBallFromTile(tile.x - 1, tile.y);
	if (checking && checking->color == ball->color)
	{
		if (!IsChecked(checking, toCheck, checked))
		{
			toCheck.push_back(checking);
		}
	}
	checking = NULL;
	checking = GetBallFromTile(tile.x, tile.y - 1);
	if (checking && checking->color == ball->color)
	{
		if (!IsChecked(checking, toCheck, checked))
		{
			toCheck.push_back(checking);
		}
	}
	checking = NULL;
	checking = GetBallFromTile(tile.x, tile.y + 1);
	if (checking && checking->color == ball->color)
	{
		if (!IsChecked(checking, toCheck, checked))
		{
			toCheck.push_back(checking);
		}
	}
	checking = NULL;
	checking = GetBallFromTile(tile.x + 1, tile.y + 1);
	if (checking && checking->color == ball->color)
	{
		if (!IsChecked(checking, toCheck, checked))
		{
			toCheck.push_back(checking);
		}
	}
	checking = NULL;
	checking = GetBallFromTile(tile.x + 1, tile.y - 1);
	if (checking && checking->color == ball->color)
	{
		if (!IsChecked(checking, toCheck, checked))
		{
			toCheck.push_back(checking);
		}
	}

	bool inArray = false;
	int pos = 0;
	for (uint i = 0; i < array.size(); i++)
	{
		if (toCheck[i] == ball)
		{
			inArray = true;
			pos = i;
			break;
		}
	}
	if (inArray)
	{
		toCheck.Pick(pos);
	}

	checked.push_back(ball);
}

bool ModuleBall::IsChecked(Ball* ball, Vector<Ball*>& toCheck, Vector<Ball*>& checked)
{
	for (uint i = 0; i < toCheck.size(); i++)
	{
		if (toCheck[i] == ball)
			return true;
	}
	for (uint j = 0; j < checked.size(); j++)
	{
		if (checked[j] == ball)
			return true;
	}
	return false;
}