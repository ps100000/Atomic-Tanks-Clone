#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>

#include "pic.h"
#include "config.h"
#include "world.h"

class pic;

class render{
	private:
		SDL_Window* window = NULL;
		SDL_Texture* background = NULL;
		SDL_Texture* buffer = NULL;
		
		SDL_Texture* world = NULL;
		SDL_Texture* layers = NULL;
		
		std::vector<pic*> pictures;
	protected:
		SDL_Renderer* renderer = NULL;
		void add_pic(pic* p);
		void delete_pic(pic* p);
	public:
		friend pic;
		render();
		~render();
		void update_world();
		void show();
};

extern render main_renderer;
#endif