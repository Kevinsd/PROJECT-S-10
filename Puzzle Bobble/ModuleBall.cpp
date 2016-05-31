#include "Application.h"
#include "ModuleBall.h"
#include "ModuleSceneLevel.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "Globals.h"
#include <stdlib.h>
#include "ModuleFadeToBlack.h"
#include "ModuleSceneCongrat.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"

ModuleBall::ModuleBall()
{
	
}

// Destructor
ModuleBall::~ModuleBall()
{}

// Called before render is available
bool ModuleBall::Init()
{
	ballsprite_blue = { 32, 260, 16, 16 };
	ballsprite_gray = { 32, 286, 16, 16 };
	ballsprite_red = { 12, 312, 16, 16 };
	ballsprite_yellow = { 32, 338, 16, 16 };
	ballsprite_purple = { 338, 338, 16, 16 };
	ballsprite_green = { 338, 260, 16, 16 };
	ballsprite_black = { 338, 286, 16, 16 };
	ballsprite_orange = { 338, 312, 16, 16 };

	top =  { 119, 134, 129, 15 };
	top1 = { 119, 201, 129, 30 };
	top2 = { 119, 282, 129, 46 };
	top3 = { 119, 377, 129, 62 };
	top4 = { 119, 486, 129, 78 };
	top5 = { 119, 609, 129, 94 };
	top6 = { 119, 746, 129, 110 };
	top7 = { 119, 897, 129, 126 };
	top8 = { 119, 1062, 129, 141 };
	top9 = { 119, 1434, 129, 157 };

	graphics_sprite = App->textures->Load("Sprites and sound/spritespuzzle.png");
	graphics_top = App->textures->Load("Sprites and sound/roof_sprites_def.png");
	return true;
}
bool ModuleBall::Start()
{
	startingY = 24;
	shotsNum = 0;
	return true;
}


update_status ModuleBall::Update()
{
	if (debug == true)
	{
		SDL_Rect left = { 0, 0, 96, SCREEN_HEIGHT };
		App->render->DrawQuad(left, 255, 0, 0, 100, true);

		SDL_Rect right = { 224, 0, SCREEN_WIDTH - 224, SCREEN_HEIGHT};
		App->render->DrawQuad(right, 255, 0, 0, 100, true);

		SDL_Rect up = { 96, 0, (SCREEN_WIDTH - 96 - (SCREEN_WIDTH - 224)), startingY };
		App->render->DrawQuad(up, 255, 0, 0, 100, true);
	}

	if (startingY == 24 + 16)
	{
		App->render->Blit(graphics_top, 95, 25, &top);
	}
	if (startingY == 24 + 32)
	{
		App->render->Blit(graphics_top, 95, 25, &top1);
	}
	if (startingY == 24 + 48)
	{
		App->render->Blit(graphics_top, 95, 25, &top2);
	}
	if (startingY == 24 + 64)
	{
		App->render->Blit(graphics_top, 95, 25, &top3);
	}
	if (startingY == 24 + 80)
	{
		App->render->Blit(graphics_top, 95, 25, &top4);
	}
	if (startingY == 24 + 96)
	{
		App->render->Blit(graphics_top, 95, 25, &top5);
	}
	if (startingY == 24 + 112)
	{
		App->render->Blit(graphics_top, 95, 25, &top6);
	}
	if (startingY == 24 + 128)
	{
		App->render->Blit(graphics_top, 95, 25, &top7);
	}
	if (startingY == 24 + 146)
	{
		App->render->Blit(graphics_top, 95, 25, &top8);
	}
	if (startingY == 24 + 146)
	{
		App->render->Blit(graphics_top, 95, 25, &top9);
	}

	for (unsigned int i = 0; i < array.size(); i++)
	{
		if (array[i]->color == BLUE)
		App->render->Blit(graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_blue);
		else if (array[i]->color == GRAY)
		App->render->Blit(graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_gray);
		else if (array[i]->color == RED)
		App->render->Blit(graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_red);
		else if (array[i]->color == GREEN)
		App->render->Blit(graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_green);
		else if (array[i]->color == YELLOW)
		App->render->Blit(graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_yellow);
		else if (array[i]->color == PURPLE)
		App->render->Blit(graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_purple);
		else if (array[i]->color == BLACK)
			App->render->Blit(graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_black);
		else if (array[i]->color == ORANGE)
			App->render->Blit(graphics_sprite, array[i]->x - 8, array[i]->y - 8, &ballsprite_orange);

		if (debug == true)
		{
			App->render->DrawCircle(array[i]->x, array[i]->y, array[i]->rad, 255, 0, 0, 255);
		}

	}


	//Debug mode
	//Push balls down
	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_DOWN)
	{
		if (PushDown() == false)
		{
			App->fade->FadeToBlack(App->currentscene, (Module*)App->scene_menu);
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_0] == KEY_DOWN)
	{
		
			App->fade->FadeToBlack(App->currentscene, (Module*)App->scene_menu);
		
	}

	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
	{
		debug = !debug;
	}

	//Change ball color ( <- )
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_DOWN)
	{
		int colorNum = static_cast<int>(moving_ball->color);
		colorNum--;
		if (colorNum < 0)
			colorNum = 7;

		moving_ball->color = static_cast<Color>(colorNum);
	}

	//Change ball color ( -> )
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_DOWN)
	{
		int colorNum = static_cast<int>(moving_ball->color);
		colorNum++;
		if (colorNum > 7)
			colorNum = 0;

		moving_ball->color = static_cast<Color>(colorNum);
	}

	for (unsigned int i = 0; i < falling.size(); i++)
	{
		falling[i]->Move(0);
		/*if (falling[i]->collidedBall)
		{
			delete falling[i];
		}*/

		if (falling[i]->color == BLUE)
			App->render->Blit(graphics_sprite, falling[i]->x - 8, falling[i]->y - 8, &ballsprite_blue);
		else if (falling[i]->color == GRAY)
			App->render->Blit(graphics_sprite, falling[i]->x - 8, falling[i]->y - 8, &ballsprite_gray);
		else if (falling[i]->color == RED)
			App->render->Blit(graphics_sprite, falling[i]->x - 8, falling[i]->y - 8, &ballsprite_red);
		else if (falling[i]->color == GREEN)
			App->render->Blit(graphics_sprite, falling[i]->x - 8, falling[i]->y - 8, &ballsprite_green);
		else if (falling[i]->color == YELLOW)
			App->render->Blit(graphics_sprite, falling[i]->x - 8, falling[i]->y - 8, &ballsprite_yellow);
		else if (falling[i]->color == PURPLE)
			App->render->Blit(graphics_sprite, falling[i]->x - 8, falling[i]->y - 8, &ballsprite_purple);
		else if (falling[i]->color == BLACK)
			App->render->Blit(graphics_sprite, falling[i]->x - 8, falling[i]->y - 8, &ballsprite_black);
		else if (falling[i]->color == ORANGE)
			App->render->Blit(graphics_sprite, falling[i]->x - 8, falling[i]->y - 8, &ballsprite_orange);

	}

	if (moving_ball != NULL)
	{
		if (moving_ball->moving)
		{
			if (moving_ball->Move(startingY) == false)
			{
				if (shotsNum == 9)
				{
					shotsNum = 0;
					if (PushDown() == false)
					{
						App->fade->FadeToBlack(App->currentscene, (Module*)App->scene_menu);
					}
				}

				//iPoint dstTile = GetTile(moving_ball->x, moving_ball->y); look there!
				iPoint dstTile = CheckClosestEmpty(moving_ball->collidedBall, moving_ball);
				p2Point <int> get_pos = GetPos(dstTile.x, dstTile.y);

				//CheckTile(get_tile.x, get_tile.y);
				moving_ball->x = get_pos.x;
				moving_ball->y= get_pos.y;
				if (moving_ball->y >= 180) // lOSE CONDITION
				{
					moving_ball = NULL;
					App->fade->FadeToBlack(App->currentscene, (Module*)App->scene_menu);
					return UPDATE_CONTINUE;
				}
				  
				//TMP FIX
				if (CheckTile(dstTile.x, dstTile.y, true))
				{
					delete moving_ball;
					moving_ball = NULL;
				}

				else 
				{
					array.push_back(moving_ball);

					Check_Pop(moving_ball);
					DeleteFlying();
					if (moving_ball)
						moving_ball = NULL;
				}
				CreateBall();
				
			}

		}
		if (moving_ball != NULL)
		{
			if (moving_ball->color == BLUE)
				App->render->Blit(graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_blue);
			if (moving_ball->color == GRAY)
				App->render->Blit(graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_gray);
			if (moving_ball->color == RED)
				App->render->Blit(graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_red);
			if (moving_ball->color == GREEN)
				App->render->Blit(graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_green);
			if (moving_ball->color == YELLOW)
				App->render->Blit(graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_yellow);
			if (moving_ball->color == PURPLE)
				App->render->Blit(graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_purple);
			if (moving_ball->color == BLACK)
				App->render->Blit(graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_black);
			if (moving_ball->color == ORANGE)
				App->render->Blit(graphics_sprite, moving_ball->x - 8, moving_ball->y - 8, &ballsprite_orange);

			if (debug == true)
			{
				App->render->DrawCircle(moving_ball->x, moving_ball->y, moving_ball->rad, 255, 0, 0, 255);
			}

		}
	}
	if (recharge_ball != NULL)
	{
		if (recharge_ball->color == BLUE)
			App->render->Blit(graphics_sprite, recharge_ball->x - 8, recharge_ball->y - 8, &ballsprite_blue);
		if (recharge_ball->color == GRAY)
			App->render->Blit(graphics_sprite, recharge_ball->x - 8, recharge_ball->y - 8, &ballsprite_gray);
		if (recharge_ball->color == RED)
			App->render->Blit(graphics_sprite, recharge_ball->x - 8, recharge_ball->y - 8, &ballsprite_red);
		if (recharge_ball->color == GREEN)
			App->render->Blit(graphics_sprite, recharge_ball->x - 8, recharge_ball->y - 8, &ballsprite_green);
		if (recharge_ball->color == YELLOW)
			App->render->Blit(graphics_sprite, recharge_ball->x - 8, recharge_ball->y - 8, &ballsprite_yellow);
		if (recharge_ball->color == PURPLE)
			App->render->Blit(graphics_sprite, recharge_ball->x - 8, recharge_ball->y - 8, &ballsprite_purple);
		if (recharge_ball->color == BLACK)
			App->render->Blit(graphics_sprite, recharge_ball->x - 8, recharge_ball->y - 8, &ballsprite_black);
		if (recharge_ball->color == ORANGE)
			App->render->Blit(graphics_sprite, recharge_ball->x - 8, recharge_ball->y - 8, &ballsprite_orange);

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
	if (moving_ball != NULL)
	{
		shotsNum++;
		moving_ball->Shoot(shoot);
	}

}

void ModuleBall::CreateBall()
{
	Vector<Color> vector;
	for (uint i = 0; i < array.size(); i++)
	{
		bool found = false;
		for (uint c = 0; c < vector.size(); c++)
		{
			if (vector[c] == array[i]->color)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			vector.push_back(array[i]->color);
		}
	}
	Color type;
	if (vector.size())
	{
		uint index = rand() % vector.size();
		type = vector[index];
	}
	else
		type = static_cast<Color>(rand() % 3);

	if (recharge_ball == NULL)
	{
		Color type2;
		if (vector.size())
		{
			uint index = rand() % vector.size();
			type2 = vector[index];
		}
		else
			type2 = static_cast<Color>(rand() % 3);
		recharge_ball = new Ball(129, 244, 8, type);
	}
	moving_ball = recharge_ball;
	moving_ball->x = 162;
	moving_ball->y = 208;

	recharge_ball = new Ball(129, 224, 8, type); //look (162, 208, 8, type)

}

void ModuleBall::AddBall(int tile_x, int tile_y, Color color)
{
	iPoint pos = GetPos(tile_x, tile_y);
	if (!CheckTile(tile_x, tile_y, true))
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
		if (!CheckTile(colTile.x + 1, colTile.y, true))
		{
			iPoint pos = GetPos(colTile.x + 1, colTile.y);
			float dstX = pos.x - toMove->x;
			float dstY = pos.y - toMove->y;
			lowerDst = sqrt(dstX*dstX + dstY * dstY);
			ret = { colTile.x + 1, colTile.y };
		}

		if (!CheckTile(colTile.x - 1, colTile.y, true))
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

		if (!CheckTile(colTile.x, colTile.y - 1, true))
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

		if (!CheckTile(colTile.x, colTile.y + 1, true))
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

		if (colTile.y % 2 != 0)
		{
			if (!CheckTile(colTile.x + 1, colTile.y + 1, true))
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
			if (!CheckTile(colTile.x + 1, colTile.y - 1, true))
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
			if (!CheckTile(colTile.x - 1, colTile.y + 1, true))
			{
				iPoint pos = GetPos(colTile.x - 1, colTile.y + 1);
				float dstX = pos.x - toMove->x;
				float dstY = pos.y - toMove->y;
				if (sqrt(dstX*dstX + dstY * dstY) < lowerDst)
				{
					lowerDst = sqrt(dstX*dstX + dstY * dstY);
					ret = { colTile.x - 1, colTile.y + 1 };
				}
			}
			if (!CheckTile(colTile.x - 1, colTile.y - 1, true))
			{
				iPoint pos = GetPos(colTile.x - 1, colTile.y - 1);
				float dstX = pos.x - toMove->x;
				float dstY = pos.y - toMove->y;
				if (sqrt(dstX*dstX + dstY * dstY) < lowerDst)
				{
					lowerDst = sqrt(dstX*dstX + dstY * dstY);
					ret = { colTile.x - 1, colTile.y - 1 };
				}
			}
		}

	}
	else
	{
		ret = GetTile(toMove->x, toMove->y);
	}
	return ret;
}

bool ModuleBall::IsBallConnected(Ball* ball)
{
	iPoint tile = GetTile(ball->x, ball->y);
	bool upLleft = false, upRight = false, left = false, right = false;
	Ball* checking = NULL;

	if (tile.y == 0)
	{
		return true;
	}

	if (tile.y % 2 != 0)
	{
		//Upper left ball
		checking = GetBallFromTile(tile.x, tile.y - 1);
		if (checking && checking->isConnected)
		{
			return true;
		}
		//Upper right ball
		checking = GetBallFromTile(tile.x + 1, tile.y - 1);
		if (checking && checking->isConnected)
		{
			return true;
		}
	}
	else
	{
		//Upper left ball
		checking = GetBallFromTile(tile.x, tile.y - 1);
		if (checking && checking->isConnected)
		{
			return true;
		}
		//Upper right ball
		checking = GetBallFromTile(tile.x - 1, tile.y - 1);
		if (checking && checking->isConnected)
		{
			return true;
		}
	}
	//Right ball
	checking = GetBallFromTile(tile.x + 1, tile.y);
	if (checking && checking->isConnected)
	{
		return true;
	}

	//Left ball
	checking = GetBallFromTile(tile.x - 1, tile.y);
	if (checking && checking->isConnected)
	{
		return true;
	}
	return false;
}

void ModuleBall::DeleteFlying()
{
	//Setting all connected to 0
	for (uint i = 0; i < array.size(); i++)
	{
		array[i]->isConnected = false;
	}

	//Getting al conected balls
	bool connectedChange = true;
	while (connectedChange)
	{
		connectedChange = false;

		for (uint i = 0; i < array.size(); i++)
		{
			if (array[i]->isConnected == false)
			{
				if (IsBallConnected(array[i]) == true)
				{
					array[i]->isConnected = true;
					connectedChange = true;
				}
			}
		}
	}

	//Deleting all non-connected balls
	for (uint i = 0; i < array.size(); i++)
	{
		if (array[i]->isConnected == false)
		{
			Ball* tmp = *array.Pick(i);
			falling.push_back(tmp);

			tmp->Shoot(90);
			tmp->velocity = -7;
			//score + 20
		/*if (tmp->y >= (SCREEN_HEIGHT + tmp->rad))
			{
				delete falling[i];
				
			}*/
	//	if (tmp->y >= (SCREEN_HEIGHT + tmp->rad)
			i--;
				
			

		}
	}
}

bool ModuleBall::PushDown()
{
	startingY += 16;
	bool ret = true;

	


	//Moving all balls down
	for (unsigned int i = 0; i < array.size(); i++)
	{
		array[i]->y += 16;
		if (array[i]->y >= 180)
			ret = false;
	}
	return ret;
}

p2Point <int>  ModuleBall::GetTile(int x, int y)
{
	x = x - 96 - 8;
	y = y - startingY - 8;	
	int pos_y = 0;
	int pos_x = 0;
	pos_y = y  / 16;
	
	if (pos_y % 2 != 0)
	{
		x -= 8;
		pos_x = x / 16;		
	}
	else
	{
		pos_x = x / 16 ;
	}
	LOG("x:%i,y;%i", pos_x, pos_y);
	p2Point <int> ret = { pos_x, pos_y };
	
	return ret;
}

p2Point <int> ModuleBall::GetPos(int x , int y)
{
	p2Point <int> ret;
	ret.y = y * 16 + startingY + 8;
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

bool ModuleBall::CheckTile(int x, int y, bool default)
{
	if (x < 0)
		return default;
	if (x > 7 && y % 2 == 0)
		return default;
	if (x > 6 && y % 2 != 0)
		return default;
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
		if (moving_ball != NULL)
		{
				float dist_x = moving_ball->x - array[i]->x;
				float dist_y = moving_ball->y - array[i]->y;
				dist_x = dist_x*dist_x;
				dist_y = dist_y*dist_y;
				int dist_final = sqrt((float)dist_x + (float)dist_y);
				if (moving_ball->rad + array[i]->rad >= dist_final)
				{
					return array[i];
				}
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
					//Score + 10
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
	if (tile.y % 2 != 0)
	{
		checking = GetBallFromTile(tile.x + 1, tile.y + 1);
	}
	else
	{
		checking = GetBallFromTile(tile.x - 1, tile.y + 1);
	}

	if (checking && checking->color == ball->color)
	{
		if (!IsChecked(checking, toCheck, checked))
		{
			toCheck.push_back(checking);
		}
	}
	checking = NULL;
	if (tile.y % 2 != 0)
	{
		checking = GetBallFromTile(tile.x + 1, tile.y - 1);
	}
	else
	{
		checking = GetBallFromTile(tile.x - 1, tile.y - 1);
	}
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