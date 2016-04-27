#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"
#include "SDL\include\SDL.h"
#include "Globals.h"

struct SDL_Renderer;
struct SDL_Texture;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PostUpdate();
	update_status Update();
	update_status PreUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f, float angle = 0, int piv_x = INT_MAX, int piv_y = INT_MAX, SDL_RendererFlip = SDL_FLIP_NONE);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
};

#endif //__ModuleRenderer_H__